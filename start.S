#define WTCON 0x53000000
#define INTMSK 0x4a000008

.text
.global _start
_start:
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

	//init board
	bl board_init

	ldr sp, =0x30008000

	ldr pc, =main

halt_loop:
	b halt_loop

