.data
newline:.asciiz "\n"		# useful for printing commands
star:	.asciiz "*"
board1: .word 128 511 511 16 511 511 4 2 511 64 511 4 1 511 511 8 511 511 1 2 511 511 511 256 511 511 128 32 16 511 511 256 4 511 128 511 511 256 511 511 511 511 511 1 511 511 128 511 32 2 511 511 256 4 2 511 511 8 511 511 511 32 64 511 511 32 511 511 128 1 511 2 511 64 8 511 511 32 511 511 16
board2: .word 128 8 256 16 32 64 4 2 1 64 32 4 1 128 2 8 16 256 1 2 16 4 8 256 32 64 128 32 16 1 64 256 4 2 128 8 4 256 2 128 16 8 64 1 32 8 128 64 32 2 1 16 256 4 2 1 128 8 4 16 256 32 64 16 4 32 256 64 128 1 8 2 256 64 8 2 1 32 128 4 16
	
.text
# main function
main:
	sub  	$sp, $sp, 4
	sw   	$ra, 0($sp) # save $ra on stack

	# test singleton (true case)
	li	$a0, 0x010
	jal	singleton
	move	$a0, $v0
	jal	print_int_and_space
	# this should print 1

	# test singleton (false case)
	li	$a0, 0x10b
	jal	singleton
	move	$a0, $v0
	jal	print_int_and_space
	# this should print 0

	# test get_singleton 
	li	$a0, 0x010
	jal	get_singleton
	move	$a0, $v0
	jal	print_int_and_space
	# this should print 4

	# test get_singleton 
	li	$a0, 0x008
	jal	get_singleton
	move	$a0, $v0
	jal	print_int_and_space
	# this should print 3

	# test board_done (true case)
	la	$a0, board2
	jal	board_done
	move	$a0, $v0
	jal	print_int_and_space
	# this should print 1
	
	# test board_done (false case)
	la	$a0, board1
	jal	board_done
	move	$a0, $v0
	jal	print_int_and_space
	# this should print 0

	# print a newline
	li	$v0, 4
	la	$a0, newline
	syscall	

	# test print_board
	la	$a0, board1
	jal	print_board

	# should print the following:
	# 8**5**32*
	# 7*31**4**
	# 12***9**8
	# 65**93*8*
	# *9*****1*
	# *8*62**93
	# 2**4***67
	# **6**81*2
	# *74**6**5

	lw   	$ra, 0($sp) 	# restore $ra from stack
	add  	$sp, $sp, 4
	jr	$ra

print_int_and_space:
	li   	$v0, 1         	# load the syscall option for printing ints
	syscall              	# print the element

	li   	$a0, 32        	# print a black space (ASCII 32)
	li   	$v0, 11        	# load the syscall option for printing chars
	syscall              	# print the char
	
	jr      $ra          	# return to the calling procedure

print_newline:
	li	$v0, 4		# at the end of a line, print a newline char.
	la	$a0, newline
	syscall	    
	jr	$ra

print_star:
	li	$v0, 4		# print a "*"
	la	$a0, star
	syscall
	jr	$ra
	
	
# ALL your code goes below this line.
#
# We will delete EVERYTHING above the line; DO NOT delete 
# the line.
#
# ---------------------------------------------------------------------
	
## bool singleton(int value) {  // This function checks whether
##   return (value != 0) && !(value & (value - 1));
## }
singleton:
	li	$v0, 0
	beq	$a0, 0, singleton_done		# return 0 if value == 0
	sub	$a1, $a0, 1
	and	$a1, $a0, $a1
	bne	$a1, 0, singleton_done		# return 0 if (value & (value - 1)) == 0
	li	$v0, 1
singleton_done:
	jr	$ra


## int get_singleton(int value) {
##   for (int i = 0 ; i < 9 ; ++ i) {
## 	 if (value == (1<<i)) {
## 		return i;
## 	 }
##   }
##   return 0;
## }
get_singleton:
	li $v0, 0	#i
	li $t1, 1

get_singleton_loop: sll $t2, $t1, $v0	#1<<i
	beq $t2, $a0, get_singleton_done
	add $v0, $v0, 1
	blt $v0, 9, get_singleton_loop	#checking if exit condition is met (i < 9)

get_singleton_done:
	jr	$ra


## bool
## board_done(int board[GRID_SQUARED][GRID_SQUARED]) {
##   for (int i = 0 ; i < 9 ; ++ i) {
## 	 for (int j = 0 ; j < 9 ; ++ j) {
## 		if (!singleton(board[i][j])) {
## 		  return false;
## 		}
## 	 }
##   }
##   return true;
## }

board_done:
	sub $sp, $sp, 20
	sw	$ra, 0($sp)
	sw	$s0, 4($sp)	#i
	sw	$s1, 8($sp)	#j
	sw	$s2, 12($sp)	#function parameter
	sw	$s3, 16($sp)	#pointer used in calls
	move $s2, $a0
	li $s0, 0	#i
board_done_loop_1:
	li $s1, 0	#j
board_done_loop_2:	#The address of element A[i][j] is: the address of A[0][0] + (((i*N)+j)*sizeof(element)) where "N" is a constant 9
	mul $t0, $s0, 9		# i*9	$t0 = (((i*N)+j)*sizeof(element))
	add $t0, $t0, $s1	#(i*9)+j
	sll $t0, $t0, 2		#((i*9)+j)*4	sll has the effect of multiplying by 2**n, where n is the amount shifted
	add $s3, $s2, $t0	#s3 is the complete address board[i][j]
	lw $a0, 0($s3)
	jal singleton	
	beq $v0, 0, ELSE
	li $v0, 1
	 
	lw $a0, 0($s3)
	j board_done_cont
ELSE:
	li	$v0, 0
board_done_cont:
	add $s1, $s1, 1 #j++
	blt $s1, 9, board_done_loop_2	#itterating through second for loop
	add $s0, $s0, 1 	#i++
	blt $s0, 9, board_done_loop_1 	#itterating through first for loop
	lw $ra, 0($sp)		# restore registers and return
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	lw $s2, 12($sp)
	lw $s3, 16($sp)
	add $sp, $sp, 20
	jr $ra

	
## void
## print_board(int board[9][9]) {
##   for (int i = 0 ; i < 9 ; ++ i) {
## 	 for (int j = 0 ; j < 9 ; ++ j) {
## 		int value = board[i][j];
## 		char c = '*';
## 		if (singleton(value)) {
## 		  c = get_singleton(value) + '1';
## 		}
## 		printf("%c", c);
## 	 }
## 	 printf("\n");
##   }
## }

print_board:
	sub $sp, $sp, 20
	sw	$ra, 0($sp)
	sw	$s0, 4($sp)	#i
	sw	$s1, 8($sp)	#j
	sw	$s2, 12($sp)	#function parameter
	sw	$s3, 16($sp)	#pointer used in calls
	move $s2, $a0
	li $s0, 0	#i
print_board_loop_1:
	li $s1, 0	#j
print_board_loop_2:	#The address of element A[i][j] is: the address of A[0][0] + (((i*N)+j)*sizeof(element)) where "N" is a constant 9
	mul $t0, $s0, 9		# i*9	$t0 = (((i*N)+j)*sizeof(element))
	add $t0, $t0, $s1	#(i*9)+j
	sll $t0, $t0, 2		#((i*9)+j)*4	sll has the effect of multiplying by 2**n, where n is the amount shifted
	add $s3, $s2, $t0	#s3 is the complete address A[i][j]
	lw $a0, 0($s3)	#a0 = value
	jal singleton 	
	beq $v0, 0, print_board_star 	#if (singleton(value)
	lw $a0, 0($s3)
	jal get_singleton
	add $a0, $v0, 1		#c = get_singleton(value) + '1'
	li $v0, 1		    #syscall @1 is print integer in register $a0
	syscall 	
	j print_board_cont
print_board_star:
	li $v0, 4
	la $a0, star
	syscall
print_board_cont:
	add $s1, $s1, 1 #j++
	blt $s1, 9, print_board_loop_2	#itterating through second for loop
	li $v0, 4
	la $a0, newline
	syscall
	add $s0, $s0, 1 	#i++
	blt $s0, 9, print_board_loop_1 	##itterating through first for loop
	lw $ra, 0($sp)		# restore registers and return
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	lw $s2, 12($sp)
	lw $s3, 16($sp)
	add $sp, $sp, 20
	jr $ra


	

















