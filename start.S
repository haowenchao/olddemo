#define WTCON 0x53000000
#define INTMSK 0x4a000008
#define STACKTOP 0x34000000
#define FIQ_SIZE 0x100000
#define IRQ_SIZE 0x100000
#define SVC_SIZE 0x100000
#define ABT_SIZE 0x100000
#define SYS_SIZE 0x100000
#define UND_SIZE 0x100000
#define USR_SIZE 0x100000

.text
.global _start
_start:
	// exception vector
	b reset
	ldr pc, halt_loop
	ldr pc, swi
	ldr pc, abort_prefetch
	ldr pc, abort_data
	nop
	ldr pc, irq
	ldr pc, fiq

swi:
	.word _swi

abort_prefetch:
	.word _abort_prefetch

abort_data:
	.word _abort_data

irq:
	.word _irq

fiq:
	.word _fiq

reset:
	//set cpu to svc mode
	mrs	r0, cpsr
	bic	r0, r0, #0x1f
	orr	r0, r0, #0xd3
	msr	cpsr_c, r0

	//disable watchdog
	ldr r0, =WTCON
	mov r1, #0x0                     
	str r1, [r0]

	//mask all the interrupts 
	mov	r1, #0xffffffff
	ldr	r0, =INTMSK
	str	r1, [r0]

	//set clock
	ldr r0, =0x4C000000
	ldr r1, =0xFFFFFFFF
	str r1, [r0]

	ldr r0, =0x4C000014
	ldr r1, =0x5
	str r1, [r0]	//UCLK=FCLK/2 HCLK=FCLK PCLK=FLK/2

	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0xc0000000
	mcr p15,0,r0,c1,c0,0

	//MPLL=(2*m*Fin)/(p*2^s)
	//m=MDIV+8
	//p=PDIV+2
	//s=SDIV
	//MDIV	[19:12]
	//PDIV	[9:4]
	//SDIV	[0:1]
	//(2*100*12MHz)/(3*2) = 400MHz
	//MDIV=100-8
	//PDIV=3-2
	//SDIV=1
	ldr r0, =0x4C000004
	ldr r1, =(92<<12)|(1<<4)|(1<<0)
	str r1, [r0]

	//set stack
	ldr sp, =4096

	//init sdram
	bl sdram_init

	//init nand
	bl nand_init

	//copy to ram
	bl copy2ram

	//init stack
	bl init_stack

/******************* Stack layout ********************/
//
//			SVC_stack
//			   ||
//			   \/
//			FIQ_stack
//			   ||
//			   \/
//			IRQ_stack
//			   ||
//			   \/
//			ABT_stack
//			   ||
//			   \/
//			SYS_stack
//			   ||
//			   \/
//			UND_stack

init_stack:
	//set svc stack
	ldr sp, =STACKTOP
	mov r0, sp
	sub r0, r0, #SVC_SIZE

	//set fiq stack
	mrs r1, cpsr
	bic r1, r1, #0x1f
	orr r1, r1, #0x11
	msr cpsr_c, r1
	mov sp, r0
	sub r0, #FIQ_SIZE

	//set irq stack
	mrs r1, cpsr
	bic r1, r1, #0x1f
	orr r1, r1, #0x12
	msr cpsr_c, r1
	mov sp, r0
	sub r0, #IRQ_SIZE

	//set abt stack
	mrs r1, cpsr
	bic r1, r1, #0x1f
	orr r1, r1, #0x17
	msr cpsr_c, r1
	mov sp, r0
	sub r0, #ABT_SIZE

	//set sys stack
	mrs r1, cpsr
	orr r1, r1, #0x1f
	msr cpsr_c, r1
	mov sp, r0
	sub r0, #SYS_SIZE

	//set und stack
	mrs r1, cpsr
	bic r1, r1, #0x1f
	orr r1, r1, #0x1b
	msr cpsr_c, r1
	mov sp, r0
	sub r0, #UND_SIZE

	mrs r0, cpsr
	bic r0, r0, #0xdf
	orr r0, r0, #0x13
	msr cpsr_c, r0

	//jump to board init
	ldr pc, =board_init

_swi:
	stmfd sp!, {r0-r12, lr}

	//get interrupt id
	ldr r0, [lr, #-4]
	bic r0, r0, #0xff000000

	//set return address
	ldr lr, =_swi_irq_fiq_abt_ret

	//jump to handler
	ldr pc, =do_swi

_abort_prefetch:
	//save environment
	sub lr, lr, #4
	stmfd sp!, {r0-r12, lr}

	//set return address
	ldr lr, =_swi_irq_fiq_abt_ret

	//jump to handler
	ldr pc, =do_pabt

_abort_data:
	//save environment
	sub lr, lr, #8
	stmfd sp!, {r0-r12, lr}

	//set return address
	ldr lr, =_swi_irq_fiq_abt_ret

	//jump to handler
	ldr pc, =do_dabt

_irq:
	//save environment
	sub lr, lr, #4
	stmfd sp!, {r0-r12, lr}

	//set return address
	ldr lr, =_swi_irq_fiq_abt_ret

	//jump to handler
	ldr pc, =do_irq

_fiq:
	//save environment
	sub lr, lr, #4
	stmfd sp!, {r0-r7, lr}

	//set return address
	ldr lr, =_fiq_ret

	//jump to handler
	ldr pc, =do_fiq

_swi_irq_fiq_abt_ret:
	ldmfd sp!, {r0-r12, pc}^

_fiq_ret:
	ldmfd sp!, {r0-r7, pc}^

halt_loop:
	b halt_loop

