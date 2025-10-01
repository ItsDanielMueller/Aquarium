#ifndef FISHCMD_H
#define FISHCMD_H
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <string.h>

struct fish {
	int x;
	int y;
	char symbol[8];
	int direction;
};
int moveFishes(struct fish fisharray[], int numFish, int boardwidth);

int drawboard(struct fish fisharray[], int numFish,int height,int witdh);

struct fish* createFish(int numFish, int boardheight,int boardwidth);

int inputHandling(int argc, char* argv[], int *numFish, int *height, int *width, int *frames);



#endif