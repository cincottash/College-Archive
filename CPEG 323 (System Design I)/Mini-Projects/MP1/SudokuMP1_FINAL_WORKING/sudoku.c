/*
 * Author: Shane Cincotta
 * Last Edited: 9/20/18
 */
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
const int GRIDSIZE = 3;
const int GRID_SQUARED = 9;
const int ALL_VALUES = (1<<9)-1;

int board[9][9];

char *easy_board_init[9] =
{													"******3**",
													"*8***3**9",
													"*24*7**86",
													"9****54*8",
													"***4*2***",
													"1*69****5",
													"56**3*14*",
													"4**5***9*",
													"**7******"
};

char *hard_board_init[9] =
{													"*94******",
													"1**79****",
													"**3*86**1",
													"92*****3*",
													"****7****",
													"*8*****25",
													"4**52*9**",
													"****61**3",
													"******64*"
};

int bit_count(int value);
int get_nth_set_bit(int value, int index);
bool singleton(int value);
int get_singleton(int value);
bool rule2();

// Use the "board_init" variable to initialize the bitmasks for each square.
void
init_board(char *board_init[GRID_SQUARED]) {
  for (int i = 0 ; i < GRID_SQUARED ; ++ i) {
	 for (int j = 0 ; j < GRID_SQUARED ; ++ j) {
		char c = board_init[i][j];
		if (c == '*') {
		  board[i][j] = ALL_VALUES;
		} else {
		  board[i][j] = 1 << (c - '0' - 1);  //  DO YOU UNDERSTAND WHAT THIS DOES?  YOU SHOULD.
		}
	 }
  }
}

// A board is done if all squares are singletons.
bool
board_done(int board[GRID_SQUARED][GRID_SQUARED]) {
  for (int i = 0 ; i < GRID_SQUARED ; ++ i) {
	 for (int j = 0 ; j < GRID_SQUARED ; ++ j) {
		if (!singleton(board[i][j])) {
		  return false;
		}
	 }
  }
  return true;
}

// Print the board with one value per square.
void
print_board(int board[GRID_SQUARED][GRID_SQUARED]) {
  for (int i = 0 ; i < GRID_SQUARED ; ++ i) {
	 for (int j = 0 ; j < GRID_SQUARED ; ++ j) {
		int value = board[i][j];
		char c = '*';
		if (singleton(value)) {
		  c = get_singleton(value) + '1';
		}
		printf("%c", c);
	 }
	 printf("\n");
  }
}

// Print the board with up to 9 values per square, based on what
// the possibilities are.
void
print_board_verbose() {
  for (int i = 0 ; i < GRID_SQUARED ; ++ i) {
	 for (int j = 0 ; j < GRID_SQUARED ; ++ j) {
		int value = board[i][j];
		char c = ' ';
		if (singleton(value)) {
		  c = '*';
		}
		for (int k = 0 ; k < GRID_SQUARED ; ++ k) {
		  char cc = (value & (1<<k)) ? ('1'+k) : c;
		  printf("%c", cc);
		}
		printf("%c", (j == (GRID_SQUARED-1)) ? '\n' : '|');
	 }
  }
}

int
get_square_begin(int index) {
  return (index/GRIDSIZE) * GRIDSIZE;
}

bool
rule1() {
  bool changed = false;
  for (int i = 0 ; i < GRID_SQUARED ; ++ i) {  
	 for (int j = 0 ; j < GRID_SQUARED ; ++ j) {
		// for every square, if the value is a singleton, remove it from the row, column, and square.
		int value = board[i][j];
		if (singleton(value)) {
		  for (int k = 0 ; k < GRID_SQUARED ; ++ k) {
			 // eliminate from row
			 if (k != j) {
				if (board[i][k] & value) {
				  changed = true;
				}
				board[i][k] &= ~value;
			 }
			 // eliminate from column
			 if (k != i) {
				if (board[k][j] & value) {
				  changed = true;
				}
				board[k][j] &= ~value;
			 }
		  }

		  // elimnate from square
		  int ii = get_square_begin(i);
		  int jj = get_square_begin(j);
		  for (int k = ii ; k < ii + GRIDSIZE ; ++ k) {
		  	 for (int l = jj ; l < jj + GRIDSIZE ; ++ l) {
		  		if ((k == i) && (l == j)) {
		  		  continue;
		  		}
				if (board[k][l] & value) {
				  changed = true;
				}
		  		board[k][l] &= ~value;
		  	 }
		  }
		}
	 }
  }
  return changed;
}

bool
solve(char *board_init[GRID_SQUARED]) {
  init_board(board_init);
  bool changed;
  do {
	 changed = rule1();
	 changed |= rule2();
  } while (changed);
  if (board_done(board)) {
	 printf("SUCCESS!\n");
	 print_board(board);
	 printf("\n");
	 return true;
  } else {
	 printf("FAILED!\n");
	 print_board_verbose();
	 printf("\n");
	 return false;
  }
}

int
main() {
  printf("bit_count(0x34) = %d\n", bit_count(0x34));
  printf("get_nth_set_bit(0x34, 1) = %d\n", get_nth_set_bit(0x34, 1));
  printf("singleton(0x40) = %s\n", singleton(0x40) ? "TRUE" : "FALSE");
  printf("get_singleton(0x40) = %d\n\n", get_singleton(0x40));

  printf("EASY BOARD:\n");
  bool solved = solve(easy_board_init);
  if (solved) {
	 printf("HARD BOARD:\n");
	 solve(hard_board_init);
  }
  return 0;
}//main

// ALL your code goes below this line.
// 
// ---------------------------------------------------------------------

int bit_count(int value){
	int bits_set=0;

	while(value != 0){
		if(value & 1){
			bits_set += 1;
		}//if
		value = value >> 1;
	}//while
	return(bits_set);
}//bit_count

int get_nth_set_bit(int value, int index){ //Counting set bits until we get to the nth set bit (index)
	int position = 0;
	int bits_set = 0;

	while(bits_set <= index){
		if(value & 1){
			bits_set += 1;
		}//if

		position += 1;
		value = value >> 1;
	}//while

	return(position-1);
}//get_nth_set_bit

_Bool singleton(int value){
	    if (value == 0){
	        return false;
	    }//if

	    _Bool truth = value & (value-1);

	    if (truth == 0){
	        return true;
	    }//if

	    else{
	        return false;
	    }//else
}//singleton

int get_singleton(int value){

	int position=0;
	_Bool isFound = false;

	while(!isFound){
		isFound= 1 & value;
		position += 1;
		value = value >> 1;
	}//while

	return(position-1);
}//get_singleton

bool rule2(){

    bool isChanged = false;
    int sumidx1=0, sumidx2=0, sumidx3=0;

    for (int idx1 = 0 ; idx1 < GRID_SQUARED ; ++ idx1){

        for (int idx2 = 0 ; idx2 < GRID_SQUARED ; ++ idx2){

            int value = board[idx1][idx2];

            if (!singleton(value)){

                for (int idx3 = 0 ; idx3 < GRID_SQUARED ; ++ idx3){

                    if (idx3 != idx1)
                        sumidx1 |= board[idx3][idx2];
                }//for

                if (sumidx1 != ALL_VALUES){

                    board[idx1][idx2] = sumidx1 ^ ALL_VALUES;
                    isChanged = true;
                }//if

                for (int idx3 = 0 ; idx3 < GRID_SQUARED ; ++ idx3){

                    if (idx3 != idx2)

                        sumidx2 |= board[idx1][idx3];
                }//for

                if (sumidx2 != ALL_VALUES){

                    board[idx1][idx2] = sumidx2 ^ ALL_VALUES;
                    isChanged = true;
                }//if

                int ii = get_square_begin(idx1);
                int jj = get_square_begin(idx2);

                //Loop
                for (int idx3 = ii ; idx3 < ii + GRIDSIZE ; ++ idx3){

                    //Loop
                    for (int l = jj ; l < jj + GRIDSIZE ; ++ l){

                        if ((idx3 == idx1) && (l == idx2)){

                            continue;
                        }//if

                        sumidx3 |= board[idx3][l];
                    }//for
                }//for

                if (sumidx3 != ALL_VALUES){

                    //Update
                    board[idx1][idx2] = sumidx3 ^ ALL_VALUES;
                    isChanged = true;
                }//if
            }//if
        }//for
    }//for

    return isChanged;
}//rule2

