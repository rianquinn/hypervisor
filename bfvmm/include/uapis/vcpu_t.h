#define VCPU_IMPL_T_HEADER "../implementation/vcpu_dummy.h"

#ifndef VCPU_IMPL_T_HEADER
#include "../implementation/arch/intel_x64/vcpu.h"
using vcpu_t = bfvmm::implementation::intel_x64::vcpu;
#else
#include VCPU_IMPL_T_HEADER
#endif
