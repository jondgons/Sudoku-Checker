--Program Information--
  Name: Cody Gonsowski
  Date: 02/12/2020
  Assignment: Assignment #2
  Program Title: Sudoku Checker
  Files required: main.c, makefile, file.txt*
  	* file.txt is any given file with a correctly formatted solution.

--Design Overview--
  This program is a sudoku checker that utilizes pthreads to expedite the process of checking the solution. It utilizes 11 threads, 1 for all rows, 1 for all columns, and 9 for all (sub)squares, 1 per square. The file format needs to be PUZZLE_SIZE (9) integers per line separated by a space, with a newline in between. Each thread will return its task result to the parent thread and indicate whether or not the solution was good or bad.
  
  If there is a bad file provided (such as non-existent or missing), the error will be output to the console.
  If there is a number not between 1 and PUZZLE_SIZE (9), the error will be output to the console.

--Known Bugs/Problems--
  - despite PUZZLE_SIZE being a variable, the number of threads accounts for a size of 9 on a 3x3 grid, not more, not less
  - -no-pie used in makefile as a workaround for -lpthread issues with linking
