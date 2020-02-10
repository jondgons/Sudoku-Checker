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
  int id; //id of each thread for storing results in thread_checks
} parameters;

void readFile(char* file); //reads in proposed solution
void print(); //prints puzzle
parameters* threadParameters(int row, int column); //provides parameters to threads
void* checkRows(void* par);
void* checkCols(void* par);
void* checkSquare(void* par);


int main(int argc, char* argv[]){
  int goodThreads = 0; //number of threads that are OK
  char* file = argv[1]; //setting file from user for readFile

  readFile(file); //read in file for solution array
  print(); //print puzzle to show correct read-in

  //thread initialization
  pthread_t threads[THREAD_COUNT];
  pthread_create(&threads[0], NULL, checkRows, threadParameters(0,0,0));
  pthread_create(&threads[1], NULL, checkCols, threadParameters(0,0,1));
  pthread_create(&threads[2], NULL, checkSquare, threadParameters(0,0,2));
  pthread_create(&threads[3], NULL, checkSquare, threadParameters(0,3,3));
  pthread_create(&threads[4], NULL, checkSquare, threadParameters(0,6,4));
  pthread_create(&threads[5], NULL, checkSquare, threadParameters(3,0,5));
  pthread_create(&threads[6], NULL, checkSquare, threadParameters(3,3,6));
  pthread_create(&threads[7], NULL, checkSquare, threadParameters(3,6,7));
  pthread_create(&threads[8], NULL, checkSquare, threadParameters(6,0,8));
  pthread_create(&threads[9], NULL, checkSquare, threadParameters(6,3,9));
  pthread_create(&threads[10],NULL, checkSquare, threadParameters(6,6,10));
  //threads[2] checks the first top left square
  //threads[3] checks the middle left square
  //and so forth...

  //join threads so they don't stop early
  for(int i = 0; i < THREAD_COUNT; i++){
    pthread_join(threads[i], NULL);
  }

  //ensure all threads returned OK
  for(int i = 0; i < THREAD_COUNT; i++){
    if(thread_checks[i] != 0){
      goodThreads++;
    }
  }

  //reporting result of solution to user
  if(goodThreads == THREAD_COUNT){
    printf("Solution works! Good job!\n");
  } else {
    printf("Bad solution! Try again!\n");
  }
  
}
