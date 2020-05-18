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