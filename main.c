/*Name: Cody Gonsowski & Ethan Seiber
 *Date: 02/12/2019
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
  int col;
  int id; //id of each thread for storing results in thread_checks
} parameters;

void readFile(char* file);
/*
  Desc:
   Populates global array 'solution' with data from a given file.
  Input:
   char* file
    char array indicating file to be read from.
  Result:
   'solution' should be populated with data from char* file. Indicates error if file is invalid or numbers are invalid.
*/
void print();
/*
  Desc:
   Prints given solution (for demonstration of correct reading).
  Result:
   Proposed solution is output for user to view.
*/
parameters* threadParameters(int row, int col, int id);
/*
  Desc:
   Prepares pthreads for processing by providing them the necessary information.
  Inputs:
   int row
    Position of row that 
*/
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
  pthread_create(&threads[10], NULL, checkSquare, threadParameters(6,6,10));
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


void readFile(char* file){
  FILE * fin = fopen(file, "r"); //open file to read

  //reports error if file opening failed
  if(fin == NULL){
    fprintf(stderr, "ERROR: file opening failure!\n");
    exit(1);
  }

  //reads in file to solution for processing
  for(int i = 0; i < PUZZLE_SIZE; i++){
    for(int j = 0; j < PUZZLE_SIZE; j++){
      fscanf(fin, "%d", &solution[i][j]);
      if(solution[i][j] < 1 || solution[i][j] > 9){
	fprintf(stderr, "ERROR: numbers must be between 1 and 9!\n");
	exit(1);
      }
    }
  }

  fclose(fin); //closes file
}

void print(){
  for(int i = 0; i < PUZZLE_SIZE; i++){
    for(int j = 0; j < PUZZLE_SIZE; j++){
      printf("%d", solution[i][j]);
    }
  }
  printf("\n");
}

parameters* threadParameters(int row, int col, int id){
  parameters* data = (parameters*) malloc(sizeof(parameters));
  
  //assign data values to thread
  data->row = row;
  data->col = col;
  data->id = id;

  return data;
}

void* checkRows(void* par){
  parameters* rowData = (parameters*) par;
  int num_counter[PUZZLE_SIZE] = {0}; //array for making sure 1-9 are there
  int goodRows = 0; //counter for amount of good rows

  for(int i = rowData->row; i < PUZZLE_SIZE; i++){
    int num_total = 0; //amount of numbers present

    //reset num_counter for each row
    for(int j = 0; j < PUZZLE_SIZE; j++){
      num_counter[j] = 0;
    }

    for(int j = 0; j < PUZZLE_SIZE; j++){
      int n = solution[i][j]; //ease of access
      
      if(n >= 1 || n <= 9){
	num_counter[n - 1]++; //update num_counter for each number; 1 is good
      }
    }

    //making sure 1-9 are present
    for(int j = 0; j < PUZZLE_SIZE; j++){
      if(num_counter == 1){
	num_total++;
      }
    }

    //all numbers present means row is good
    if(num_total == PUZZLE_SIZE){
      goodRows++;
    }
  }

  //all rows good, so thread completion needs to be indicated in thread_checks
  if(goodRows == PUZZLE_SIZE){
    thread_checks[rowData->id] = 1;
  }
}

void* checkCols(void* par){
  parameters* colData = (parameters*) par;
  int num_counter[PUZZLE_SIZE] = {0}; //array for making sure 1-9 are there
  int goodCols = 0; //counter for amount of good columns

  for(int i = colData->col; i < PUZZLE_SIZE; i++){
    int num_total = 0; //amount of numbers present

    //reset num_counter for each column
    for(int j = 0; j < PUZZLE_SIZE; j++){
      num_counter[j] = 0;
    }

    for(int j = 0; j < PUZZLE_SIZE; j++){
      int n = solution[j][i]; //ease of access
      
      if(n >= 1 || n <= 9){
	num_counter[n - 1]++; //update num_counter for each number; 1 is good
      }
    }

    //making sure 1-9 are present
    for(int j = 0; j < PUZZLE_SIZE; j++){
      if(num_counter[j] == 1){
	num_total++;
      }
    }

    //all numbers present means column is good
    if(num_total == PUZZLE_SIZE){
      goodCols++;
    }
  }

  //all columns good, so thread completion needs to be indicated in thread_checks
  if(goodCols == PUZZLE_SIZE){
    thread_checks[colData->id] = 1;
  }
}

void* checkSquare(void* par){
  parameters* squareData = (parameters*) par;
  int num_counter[PUZZLE_SIZE] = {0}; //array for making sure 1-9 are there
  int num_total = 0; //amount of numbers present

  for(int i = squareData->row; i < squareData->row + 3; i++){
    for(int j = squareData->col; j < squareData->col + 3; j++){
      int n = solution[i][j]; //ease of access

      if(n >= 1 || n <= 9){
	num_counter[n - 1]++; //update num_counter for each number; 1 is good
      }
    }
  }

  //making sure 1-9 are present
  for(int i = 0; i < PUZZLE_SIZE; i++){
    if(num_counter[i] == 1){
      num_total++;
    }
  }
  
  //square is good, so thread completion needs to be indicated in thread_checks
  if(num_total == PUZZLE_SIZE){
    thread_checks[squareData->id] = 1;
  }
}
