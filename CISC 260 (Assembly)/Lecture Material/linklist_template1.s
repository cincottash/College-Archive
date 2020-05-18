@ read integers from a file and insert them into a linked list to get sorted
@ and print the sorted integers to the screen (stdout).

.text
main:
	@ open an input file to read integers
	ldr r0, =InFileName
	mov r1, #0
	swi 0x66		@ open file

	@ Here you should read the first integer from the file (see below for how)
	@ and creat a base node for your linked-list
	@ and save the base node address to the label MyList (which is declared in .data) for later references

    Loop:
	@ read integer from file

	mov r3, r0	@ save file header to r3
	swi 0x6c	@ read an integer put in r0
	BCS CloseF	@ branch when the end of the file is reached

	@print the integer that's just read 
	mov r1, r0	@ copy r0 to r1 for printing
	MOV r0, #1     @ Load 1 into register r0 (stdout handle) 
	SWI 0x6b       @ Print integer in register r1 to stdout

	@ print a space
	mov r0, #1
	ldr  r1,  =Space
	swi  0x69

	@ You should comment out the above code for printing
	@ Instead, you creat a new node and save the integer into the first 4 bytes of the node
	@ Put the base node address in r0, and the address of the to-be-inserted node in r1
	@ call the subroutine Insert to insert the newly created node into the linked-list
        @BL Insert     @ you should write subroutine Insert
	
	mov r0, r3	@ copy file header back to r0
	B Loop
     CloseF:
	@close infile
	mov r0, r3	@ restore file header to r0
	swi 0x68

	@ put the base node address in r0
	@BL PrintList  @ you print the integers by traversing the linked list.
	
exit:	SWI 0x11       @ Stop program execution 
		
.data
MyList: .word 0
InFileName: .asciz "list.txt"
InFileHandle: .word 0
Space: .ascii " "
