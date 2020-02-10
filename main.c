/*Name: Cody Gonsowski & Ethan Seiber
 *Date: 02/10/2019
 *File: main.c
 *Desc: Main driver of the sudoku checker program.
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define PUZZLE_SIZE 9 //how big the puzzle is, should be square
#define THREAD_COUNT 11 //number of threads to be run

int solution [PUZZLE_SIZE][PUZZLE_SIZE] = {0}; //array for file input
int thread_checks [THREAD_COUNT] = {0}; //outcome of each thread verification

//thread information
typedef struct{
  int row;
  int column;
} parameters;

void readFile(char* file); //reads in proposed solution
void print(); //prints puzzle
parameters* threadParameters(int row, int column); //provides parameters to threads
void* checkRows(void* par);
void* checkCols(void* par);
void* checkSquare(void* par);


int main(int argc, char* argv[]){
  int goodThreads = 0; //number of threads that are OK
}
