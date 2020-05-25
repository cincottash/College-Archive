#include <stdio.h>
#include <stdlib.h>

//these values are used to in the function selector
#define ADD 0
#define SUB 1
#define LI 2
#define COMPARE 3
#define PRINT 4

int rd, rs, rt, choice, PC, immediate;
rd=rs=rt=immediate=0;

char reg[4];	//creating 4 registers
reg[0] = immediate;
reg[1] = rt;
reg[2] = rs;
reg[3] = rd;

char opcode[8]; //creating our 8-bit opcode

int instruction();
void exception();
void clear_reg();
void add();
void sub();
void li();
void compare();
void print();

int main(int argc, char *argv[]){
	clear_reg();
	switch(instruction()){
		case ADD:
			add();
			break
		case SUB:
			sub();
			break;
		case LI:
			li();
			break;
		case COMPARE:
			compare();
			break;
		case PRINT:
			print();
			break;

	}



	return 0;
}


void clear_reg(){
	for(int i =0; i <4; i++){
		reg[i] = 0;
	}
}

void exception(){
	printf("exception occured")
	exit(0);
}

//chooses which instruction should be ran by comparing the opcode
int instruction(){
	if(opcode[0] == 0 && opcode[1] == 0){
		return 0;
		break;
	}//ADD

	else if(opcode[0] == 1 && opcode[1] == 0){
		return 1;
		break;
	}//SUB

	else if(opcode[0] == 0 && opcode[1] == 1){
		return 2;
		break;
	}//LI

	else if(opcode[0] == 1 && opcode[1] == 1){
		return 3;
		break;
	}//COMPARE

	else if(opcode[0] == 1 && opcode[1] == 0 && opcode[2] == 0) && opcode[3] == 0 && opcode[4] == 0 && opcode[5] == 0{
		return 4;
		break;
	}//PRINT

	else{
		exception();
	}
}

void add(){
	//checking the opcode bits which contains our register rs value
	if(opcode[3] == 0 && opcode[2] == 0){
		rs = 0;
	}

	else if(opcode[3] == 0 && opcode[2] == 1){
		rs = 1;
	}

	else if(opcode[3] == 1 && opcode[2] == 0){
		rs = 2;
	}

	else if(opcode[3] == 1 && opcode[2] == 1){
		rs = 3;
	}

	else {
		exception(); //cant have more than a 2 bit number in our register
	}


	// checking the opcode bits which contains our register rt value
	if(opcode[1] == 0 && opcode[0] == 0){
		rt = 0;
	}

	else if(opcode[1] == 0 && opcode[0] == 1){
		rt = 1;
	}

	else if(opcode[1] == 1 && opcode[0] == 0){
		rt = 2;
	}

	else if(opcode[1] == 1 && opcode[0] == 1){
		rt = 3;
	}

	else {
		exception(); //cant have more than a 2 bit number in our register
	}

	//checking for overflow
	if( rt + rs > 3){ 
		exception();
		exit(0);
	}
	else{
		rd = rs + rt;

	}

}

void sub(){
	//checking the opcode bits which contains our register rs value
	if(opcode[3] == 0 && opcode[2] == 0){
		rs = 0;
	}

	else if(opcode[3] == 0 && opcode[2] == 1){
		rs = 1;
	}

	else if(opcode[3] == 1 && opcode[2] == 0){
		rs = 2;
	}

	else if(opcode[3] == 1 && opcode[2] == 1){
		rs = 3;
	}

	else {
		exception(); //cant have more than a 2 bit number in our register
	}

	 // checking the opcode bits which contains our register rt value
	if(opcode[1] == 0 && opcode[0] == 0){
		rt = 0;
	}

	else if(opcode[1] == 0 && opcode[0] == 1){
		rt = 1;
	}

	else if(opcode[1] == 1 && opcode[0] == 0){
		rt = 2;
	}

	else if(opcode[1] == 1 && opcode[0] == 1){
		rt = 3;
	}

	else {
		exception(); //cant have more than a 2 bit number in our register
	}

	//checking for overflow
	if(rs - rt > 3 || rs-rt < -3 ){
		exception();
		exit(0);
	}

	else{
		rd = rs - rt;
	}
}

void li(){

	//find the immediate value
	if(opcode[3] == 0 && opcode[2] == 0 && opcode[1] == 0 && opcode[0] == 0){
		immediate = 0;
	}

	else if(opcode[3] == 0 && opcode[2] == 0 && opcode[1] == 0 && opcode[0] == 1){
		immediate = 1;
	}

	else if(opcode[3] == 0 && opcode[2] == 0 && opcode[1] == 1 && opcode[0] == 0){
		immediate = 2;
	}

	else if(opcode[3] == 0 && opcode[2] == 1 && opcode[1] == 0 && opcode[0] == 1){
		immediate = 3;
	}

	else if(opcode[3] == 1 && opcode[2] == 1 && opcode[1] == 0 && opcode[0] == 0){
		immediate = 4;
	}

	else if(opcode[3] == 0 && opcode[2] == 1 && opcode[1] == 0 && opcode[0] == 1){
		immediate = 5;
	}

	else if(opcode[3] == 0 && opcode[2] == 1 && opcode[1] == 1 && opcode[0] == 0){
		immediate = 6;
	}

	else if(opcode[3] == 0 && opcode[2] == 1 && opcode[1] == 1 && opcode[0] == 1){
		immediate = 7;
	}

	else if(opcode[3] == 1 && opcode[2] == 0 && opcode[1] == 0 && opcode[0] == 0){
		immediate = 8;
	}

	else if(opcode[3] == 1 && opcode[2] == 0 && opcode[1] == 0 && opcode[0] == 1){
		immediate = 9;
	}

	else if(opcode[3] == 1 && opcode[2] == 0 && opcode[1] == 1 && opcode[0] == 0){
		immediate = 10;
	}

	else if(opcode[3] == 1 && opcode[2] == 0 && opcode[1] == 1 && opcode[0] == 1){
		immediate = 11;
	}

	else if(opcode[3] == 1 && opcode[2] == 1 && opcode[1] == 0 && opcode[0] == 0){
		immediate = 12;
	}

	else if(opcode[3] == 1 && opcode[2] == 1 && opcode[1] == 0 && opcode[0] == 1){
		immediate = 13;
	}

	else if(opcode[3] == 1 && opcode[2] == 1 && opcode[1] == 1 && opcode[0] == 0){
		immediate = 14;
	}

	else if(opcode[3] == 1 && opcode[2] == 1 && opcode[1] == 1 && opcode[0] == 1){
		immediate = 15;
	}
	//cant have a value which is more than 0d15
 	else {
		exception();
		exit(0);
	}



	//checking for overflow
	if(immediate + rd > 15){
		exception();
		exit(0);
	}
	else{
		rd = rd + immediate;
	}
}


void compare(){
	if(opcode[3] == 0 && opcode[2] == 0){
		rs = 0;
	}

	else if(opcode[3] == 0 && opcode[2] == 1){
		rs = 1;
	}

	else if(opcode[3] == 1 && opcode[2] == 0){
		rs = 2;
	}

	else if(opcode[3] == 1 && opcode[2] == 1){
		rs = 3;
	}

	else {
		exception(); //cant have more than a 2 bit number as our reg
	}

	 // checking the opcode bits which contains our register rt value
	if(opcode[1] == 0 && opcode[0] == 0){
		rt = 0;
	}

	else if(opcode[1] == 0 && opcode[0] == 1){
		rt = 1;
	}

	else if(opcode[1] == 1 && opcode[0] == 0){
		rt = 2;
	}

	else if(opcode[1] == 1 && opcode[0] == 1){
		rt = 3;
	}

	else {
		exception(); //cant have more than a 2 bit number as our reg
	}

	if(rt == rs){
		printf("Execute next 1 or next 2 instructions? 1/0 /n");
		scanf("%d", choice);
		if(choice = 1){
			PC+=4;
		}
		else{
			PC+=8;
		}
		rd = 1;

	}
	else{
		PC+=4;
		rd = 0;
}


void print(){
	if(opcode[1] == 0 && opcode[0] == 0){
		rd = 0;
		printf("%d", rd);
	}

	else if(opcode[1] == 0 && opcode[0] == 1){
		rd = 1;
		printf("%d", rd);
	}

	else if(opcode[1] == 1 && opcode[0] == 0){
		rd = 2;
		printf("%d", rd);
	}

	else if(opcode[1] == 1 && opcode[0] == 1){
		rd = 3;
		printf("%d", rd);
	}
	else{
		exception();
	}


}