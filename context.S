.global context_switch_to
context_switch_to:
	mov sp, r0
	ldmfd sp!, {r1}
	msr cpsr, r1
	ldm sp!, {r0-r12, lr, pc}

