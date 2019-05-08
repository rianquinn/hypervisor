Set CR4.OSFXSR[bit 9] = 1. Setting this flag implies that the operating system provides facilities for saving
and restoring SSE state using FXSAVE and FXRSTOR instructions. These instructions may be used to save the
SSE state during task switches and when invoking the SIMD floating-point exception (#XM) handler (see
Section 13.1.5, “Providing a Handler for the SIMD Floating-Point Exception (#XM)”).
If the processor does not support the FXSAVE and FXRSTOR instructions, attempting to set the OSFXSR flag
causes a general-protection exception (#GP) to be generated.
13-2 Vol. 3ASYSTEM PROGRAMMING FOR INSTRUCTION SET EXTENSIONS AND PROCESSOR EXTENDED STATES
2. Set CR4.OSXMMEXCPT[bit 10] = 1. Setting this flag implies that the operating system provides a SIMD
floating-point exception (#XM) handler (see Section 13.1.5, “Providing a Handler for the SIMD Floating-Point
Exception (#XM)”).
NOTE
The OSFXSR and OSXMMEXCPT bits in control register CR4 must be set by the operating system.
The processor has no other way of detecting operating-system support for the FXSAVE and
FXRSTOR instructions or for handling SIMD floating-point exceptions.
3. Clear CR0.EM[bit 2] = 0. This action disables emulation of the x87 FPU, which is required when executing SSE
instructions (see Section 2.5, “Control Registers”).
4. Set CR0.MP[bit 1] = 1. This setting is required for Intel 64 and IA-32 processors that support the SSE
extensions (see Section 9.2.1, “Configuring the x87 FPU Environment”).
