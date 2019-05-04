/*
 * Copyright (C) 2019 Assured Information Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <linux/fs.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/kallsyms.h>
#include <linux/notifier.h>
#include <linux/reboot.h>
#include <linux/suspend.h>

#include <common.h>

#include <bfdebug.h>
#include <bftypes.h>
#include <bfplatform.h>
#include <bfconstants.h>
#include <bfdriverinterface.h>

uint64_t _vmcall(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4);

/* -------------------------------------------------------------------------- */
/* Status                                                                     */
/* -------------------------------------------------------------------------- */

static int g_status = 0;

#define STATUS_STOPPED 0
#define STATUS_RUNNING 1
#define STATUS_SUSPEND 2

DEFINE_MUTEX(g_status_mutex);

/* -------------------------------------------------------------------------- */
/* Misc Device                                                                */
/* -------------------------------------------------------------------------- */

static int
dev_open(struct inode *inode, struct file *file)
{ return 0; }

static int
dev_release(struct inode *inode, struct file *file)
{ return 0; }

static long
ioctl_unload_vmm(void)
{
    int64_t ret;

    ret = common_unload_vmm();
    if (ret != BFSUCCESS) {
        return BFFAILURE;
    }

    return BFSUCCESS;
}

static long
ioctl_load_vmm(const struct ioctl_load_args_t *args)
{
    int64_t ret;
    char *file;
    struct ioctl_load_args_t _args;

    ret = copy_from_user(&_args, args, sizeof(struct ioctl_load_args_t));
    if (ret != 0) {
        return BFFAILURE;
    }

    file = (char *)platform_alloc_rw(_args.file_size);
    if (file == NULL) {
        return BFFAILURE;
    }

    ret = copy_from_user(file, (char *)_args.file_addr, _args.file_size);
    if (ret != 0) {
        goto failure;
    }

    ret = common_load_vmm(file, _args.file_size, _args.mem);
    if (ret != BFSUCCESS) {
        goto failure;
    }

    platform_free_rw(file, _args.file_size);
    return BFSUCCESS;

failure:

    platform_free_rw(file, _args.file_size);
    return BFFAILURE;
}

static long
ioctl_stop_vmm(void)
{
    int64_t ret;
    mutex_lock(&g_status_mutex);

    ret = common_stop_vmm();
    if (ret != BFSUCCESS) {
        goto failure;
    }

    g_status = STATUS_STOPPED;

    mutex_unlock(&g_status_mutex);
    return BFSUCCESS;

failure:

    mutex_unlock(&g_status_mutex);
    return BFFAILURE;
}

static long
ioctl_start_vmm(void)
{
    int64_t ret;
    mutex_lock(&g_status_mutex);

    ret = common_start_vmm();
    if (ret != BFSUCCESS) {
        goto failure;
    }

    g_status = STATUS_RUNNING;

    mutex_unlock(&g_status_mutex);
    return BFSUCCESS;

failure:

    common_stop_vmm();

    mutex_unlock(&g_status_mutex);
    return BFFAILURE;
}

static long
ioctl_dump_vmm(struct debug_ring_resources_t *drr)
{
    int64_t ret;
    struct debug_ring_resources_t *_drr = 0;

    ret = common_dump_vmm(&_drr);
    if (ret != BFSUCCESS) {
        return BFFAILURE;
    }

    ret = copy_to_user(drr, _drr, sizeof(struct debug_ring_resources_t));
    if (ret != 0) {
        return BFFAILURE;
    }

    return BFSUCCESS;
}

static long
ioctl_vmm_status(int64_t *status)
{
    int64_t ret;
    int64_t _status = common_vmm_status();

    if (status == 0) {
        return BFFAILURE;
    }

    ret = copy_to_user(status, &_status, sizeof(int64_t));
    if (ret != 0) {
        return BFFAILURE;
    }

    return BFSUCCESS;
}

static long
ioctl_vmcall(struct ioctl_vmcall_args_t *args)
{
    int64_t ret;
    struct ioctl_vmcall_args_t _args;

    if (args == 0) {
        return BFFAILURE;
    }

    ret = copy_from_user(&_args, args, sizeof(struct ioctl_vmcall_args_t));
    if (ret != 0) {
        return BFFAILURE;
    }

    mutex_lock(&g_status_mutex);

    switch (g_status) {
        case STATUS_RUNNING:
            _args.reg1 = _vmcall(_args.reg1, _args.reg2, _args.reg3, _args.reg4);
            break;

        case STATUS_SUSPEND:
            _args.reg1 = BFFAILURE_SUSPEND;
            break;

        default:
            _args.reg1 = BFFAILURE;
            break;
    };

    mutex_unlock(&g_status_mutex);

    _args.reg2 = 0;
    _args.reg3 = 0;
    _args.reg4 = 0;

    ret = copy_to_user(args, &_args, sizeof(struct ioctl_vmcall_args_t));
    if (ret != 0) {
        return BFFAILURE;
    }

    return BFSUCCESS;
}

static long
dev_unlocked_ioctl(
    struct file *file, unsigned int cmd, unsigned long arg)
{
    switch (cmd) {
        case IOCTL_LOAD_VMM:
            return ioctl_load_vmm((const struct ioctl_load_args_t *)arg);

        case IOCTL_UNLOAD_VMM:
            return ioctl_unload_vmm();

        case IOCTL_START_VMM:
            return ioctl_start_vmm();

        case IOCTL_STOP_VMM:
            return ioctl_stop_vmm();

        case IOCTL_DUMP_VMM:
            return ioctl_dump_vmm((struct debug_ring_resources_t *)arg);

        case IOCTL_VMM_STATUS:
            return ioctl_vmm_status((int64_t *)arg);

        case IOCTL_VMCALL:
            return ioctl_vmcall((struct ioctl_vmcall_args_t *)arg);

        default:
            return -EINVAL;
    }
}

static struct file_operations fops = {
    .open = dev_open,
    .release = dev_release,
    .unlocked_ioctl = dev_unlocked_ioctl,
};

static struct miscdevice bareflank_dev = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = BAREFLANK_NAME,
    .fops = &fops,
    .mode = 0666
};

/* -------------------------------------------------------------------------- */
/* Entry / Exit                                                               */
/* -------------------------------------------------------------------------- */

int
dev_reboot(
    struct notifier_block *nb, unsigned long code, void *unused)
{
    mutex_lock(&g_status_mutex);

    common_fini();
    g_status = STATUS_STOPPED;

    mutex_unlock(&g_status_mutex);
    return NOTIFY_DONE;
}

static int
resume(void)
{
    mutex_lock(&g_status_mutex);

    if (g_status != STATUS_SUSPEND) {
        mutex_unlock(&g_status_mutex);
        return NOTIFY_DONE;
    }

    if (common_start_vmm() != BFSUCCESS) {

        common_fini();
        g_status = STATUS_STOPPED;

        mutex_unlock(&g_status_mutex);
        return -EPERM;
    }

    g_status = STATUS_RUNNING;

    mutex_unlock(&g_status_mutex);
    return NOTIFY_DONE;
}

static int
suspend(void)
{
    mutex_lock(&g_status_mutex);

    if (g_status != STATUS_RUNNING) {
        mutex_unlock(&g_status_mutex);
        return NOTIFY_DONE;
    }

    if (common_stop_vmm() != BFSUCCESS) {

        common_fini();
        g_status = STATUS_STOPPED;

        mutex_unlock(&g_status_mutex);
        return -EPERM;
    }

    g_status = STATUS_SUSPEND;

    mutex_unlock(&g_status_mutex);
    return NOTIFY_DONE;
}

int
dev_pm(
    struct notifier_block *nb, unsigned long code, void *unused)
{
    switch (code) {
        case PM_SUSPEND_PREPARE:
        case PM_HIBERNATION_PREPARE:
        case PM_RESTORE_PREPARE:
            return suspend();

        case PM_POST_SUSPEND:
        case PM_POST_HIBERNATION:
        case PM_POST_RESTORE:
            return resume();

        default:
            break;
    }

    return NOTIFY_DONE;
}

static struct notifier_block reboot_notifier_block = {
    .notifier_call = dev_reboot
};

static struct notifier_block pm_notifier_block = {
    .notifier_call = dev_pm
};

int
dev_init(void)
{
    register_reboot_notifier(&reboot_notifier_block);
    register_pm_notifier(&pm_notifier_block);

    if (misc_register(&bareflank_dev) != 0) {
        goto INIT_FAILURE;
    }

    if (common_init() != 0) {
        goto INIT_FAILURE;
    }

    g_status = STATUS_STOPPED;
    mutex_init(&g_status_mutex);

    return 0;

INIT_FAILURE:

    return -EPERM;
}

void
dev_exit(void)
{
    mutex_lock(&g_status_mutex);

    common_fini();
    g_status = STATUS_STOPPED;

    misc_deregister(&bareflank_dev);
    unregister_pm_notifier(&pm_notifier_block);
    unregister_reboot_notifier(&reboot_notifier_block);

    mutex_unlock(&g_status_mutex);
    return;
}

module_init(dev_init);
module_exit(dev_exit);

MODULE_LICENSE("GPL");
