#Name: Cody Gonsowski & Ethan Seiber
#File: makefile
#Desc: makefile for assignment #2

CC=gcc

DEBUG=-g

TARGET=sudoku

CFLAGS=-c -Wall $(DEBUG)

all: $(TARGET)

$(TARGET): main.o 
	$(CC) -o $(TARGET) main.o

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm *.o *~ $(TARGET)
