  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
  
  
.data
  
.text

# Written by Ali Sahibi
.global hexasc
hexasc:
	li $t0, 0x0000000f
	and $t1, $a0, $t0 # we mask every bit except the 4 last
	
	addi $t3, $0, 9
	
	#ble $t1, 9, else # if $t1 <= 9 then branch to else otherwise run code directly below
	slt $t4, $t3, $t1
	beq $t4, $0, else
	nop
	
	addi $t1, $t1, -10 # we subtract the value with 10
	addi $t2, $t1, 0x41 # we add the rest with 0x41 ascii for 'A'
	j jump # jump to label jump, skipping the else statement
	nop
		
else:
	addi $t2, $t1, 0x30	
jump:
	add $v0, $t2, $0 # store value in return register
	jr $ra # return to caller
	nop



# delay function. parameter: $a0(time in ms)	
.global delay			
delay:	
	addi $t0, $0, 0 # variable used as counter in the loop
	addi $t1, $0, 4411 # DELAY CONSTANT
while:
	# ble instruction below, if $a0 > 0 then in whileloop, if $a0 <= 0 then end whileloop
	slt $t2, $0, $a0
	beq $t2, $0, WhileDone
	nop
	addi $a0, $a0, -1 # decrement $a0
	
loop:
	beq $t0, $t1, LoopDone # if $t0 = "IMMEDIATE_VALUE" then brach to LoopDone, else run code below
	nop
	addi $t0, $t0, 1 # increment $t0
	j loop # jumps back to loop
	nop
	
LoopDone:
	addi $t0, $0, 0
	j while # jumps back to while
	nop
	
WhileDone:
	jr $ra # return to caller
	nop	
	
	
	# time2string, parameters: $a0(memory location), $a1(data)
.global time2string
time2string:
	PUSH $ra # very important part! Put the return adress on the stack
	PUSH $s0 # push $s0 into the stack
	move $s0, $a0 # we use $s0 for memory adress location
	
	srl $a0, $a1, 12  # first digit of minute put at 4 Least significant bits in $a0
	jal hexasc # call function hexasc
	nop
	sb $v0, 0($s0) # store the ASCII encoded char value in an array starting with base adress in $a0
	
	
	srl $a0, $a1, 8  # second digit of minute put at 4 Least significant bits in $a0
	jal hexasc
	nop
	sb $v0, 1($s0)
	
	addi $t0, $0, 0x3a # adding the character ":" to the array
	sb $t0, 2($s0)
	
	
	srl $a0, $a1, 4  # first digit of second put at 4 Least significant bits in $a0
	jal hexasc
	nop
	sb $v0, 3($s0)
	
	addi $s0, $s0, 4 # moving over to the next 32-bit memory adress
	
	add $a0, $a1, $0 # last digit of seconds is already in 4 LSBits, no operation needed
	jal hexasc
	nop
	sb $v0, 0($s0)
	
	addi $t0, $0, 0x00 # adding NULL byte, signifying the end of the char array
	sb $t0, 1($s0)	
	
	
	POP $s0 # poping out $s0 so it remains unchanged for the caller
	POP $ra # poping out the return adress for time2string so it jumps back to the caller in main
	jr $ra # return to caller
	nop

    .global enable_interrupt
    enable_interrupt:
        ei
        jr $ra
        nop