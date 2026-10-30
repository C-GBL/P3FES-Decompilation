; Stack switch for the kernel's fibers (fiber.h). Win64 ABI.
;
; void p3fes_fiber_switch(FiberCtx* save /* rcx */, const FiberCtx* load /* rdx */)
;   FiberCtx: +0 rsp, +8 TEB StackBase, +16 TEB StackLimit, +24 TEB DeallocationStack.
;   Pushes the callee-saved GPRs, stores xmm6-xmm15, MXCSR and the x87 control word below them (240 bytes with
;   the return address), saves rsp and the three TEB fields into *save, loads *load's and unwinds the same frame
;   from the other stack. A new fiber's stack is laid out by fiber_prepare (scheduler.cpp) so that this unwind
;   "returns" into p3fes_fiber_start with rbx = entry, rsi = argument.
;
; void p3fes_fiber_start()
;   First code of a new fiber: entry(argument) on a 16-byte aligned stack with home space; entry never returns.
;   The word above its stack pointer is 0, which ends host stack walks there.

.code

p3fes_fiber_switch PROC
    push    rbx
    push    rbp
    push    rdi
    push    rsi
    push    r12
    push    r13
    push    r14
    push    r15
    sub     rsp, 168
    movaps  xmmword ptr [rsp + 0], xmm6
    movaps  xmmword ptr [rsp + 16], xmm7
    movaps  xmmword ptr [rsp + 32], xmm8
    movaps  xmmword ptr [rsp + 48], xmm9
    movaps  xmmword ptr [rsp + 64], xmm10
    movaps  xmmword ptr [rsp + 80], xmm11
    movaps  xmmword ptr [rsp + 96], xmm12
    movaps  xmmword ptr [rsp + 112], xmm13
    movaps  xmmword ptr [rsp + 128], xmm14
    movaps  xmmword ptr [rsp + 144], xmm15
    stmxcsr dword ptr [rsp + 160]
    fnstcw  word ptr [rsp + 164]

    mov     rax, qword ptr gs:[8]
    mov     qword ptr [rcx + 8], rax
    mov     rax, qword ptr gs:[16]
    mov     qword ptr [rcx + 16], rax
    mov     rax, qword ptr gs:[1478h]
    mov     qword ptr [rcx + 24], rax
    mov     qword ptr [rcx], rsp

    mov     rsp, qword ptr [rdx]
    mov     rax, qword ptr [rdx + 8]
    mov     qword ptr gs:[8], rax
    mov     rax, qword ptr [rdx + 16]
    mov     qword ptr gs:[16], rax
    mov     rax, qword ptr [rdx + 24]
    mov     qword ptr gs:[1478h], rax

    movaps  xmm6, xmmword ptr [rsp + 0]
    movaps  xmm7, xmmword ptr [rsp + 16]
    movaps  xmm8, xmmword ptr [rsp + 32]
    movaps  xmm9, xmmword ptr [rsp + 48]
    movaps  xmm10, xmmword ptr [rsp + 64]
    movaps  xmm11, xmmword ptr [rsp + 80]
    movaps  xmm12, xmmword ptr [rsp + 96]
    movaps  xmm13, xmmword ptr [rsp + 112]
    movaps  xmm14, xmmword ptr [rsp + 128]
    movaps  xmm15, xmmword ptr [rsp + 144]
    ldmxcsr dword ptr [rsp + 160]
    fldcw   word ptr [rsp + 164]
    add     rsp, 168
    pop     r15
    pop     r14
    pop     r13
    pop     r12
    pop     rsi
    pop     rdi
    pop     rbp
    pop     rbx
    ret
p3fes_fiber_switch ENDP

; Entered by the `ret` above with rsp 16-byte aligned and [rsp] = 0 (fiber_prepare): its unwind data makes a
; host stack walk read that 0 as the return address and stop.
p3fes_fiber_start PROC FRAME
    sub     rsp, 32
    .allocstack 32
    .endprolog
    mov     rcx, rsi
    call    rbx
    int     3
p3fes_fiber_start ENDP

END
