#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



struct fish {
	int x;
	int y;
	char symbol[10];
	int direction;
};


void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}


void shuffle(int* array, int n) {
	//Fisher-Yates Shuffle. Tausch zufällige zahlen in einem vorhandenen Array.
	for (int i = n - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		swap(&array[i], &array[j]);
	}
}


int drawboard(struct fish fisharray[],int numFish,int height,int width) {

	//Array dynamisch allociert.
	char** board = malloc(height * sizeof(char*));
	//Error catch falls kein Speicher frei ist.
	if (!board) {
		printf("Fehler: Konnte Board nicht allokieren!\n");
		return -1;
	}


	//Speichert das Aquarium in dem Array
	for (int x = 0; x < height; x++) {
		board[x] = malloc(width * sizeof(char)); //Weil ich den array num dynamisch allokiere ????

		for (int y = 0; y < width; y++) {
			if (y == 0 || y == width-1) {
				board[x][y] = '|';
			}
			else if (x == 0 || x == height-1) {
				board[x][y] = '-';
			}
			else {
				board[x][y]=' ';
			}

		}

	}

	//Fische eintragen ins array.
	for (int f = 0; f < numFish; f++) {
		int len = strlen(fisharray[f].symbol); //Holt alle Fische ein und speichert sie in len.
		for (int k = 0; k < len; k++) { 
			int positionY = fisharray[f].y + k; //Da sich die Fische nur in Y bewegen brauche ich auch nur eine Variable zum speichern der y position. +k springt dann auf den nächsten index im array des Fisches.
			if (fisharray[f].x > 0 && fisharray[f].x < height && positionY > 0 && positionY < width) { //Checkt ob der Fisch auch im Array ist sonst gibts error!
				board[fisharray[f].x][positionY] = fisharray[f].symbol[k]; //Speichert die Zeichen von jedem Fisch in das Array. Da K positionY und auch symbol vom Fisch inkrementiert zeichnet diese loop den Fisch.
			}
		}
	}
	//Gibt das array aus um das Aquarium und die Fische anzuzeigen.
	for (int x = 0; x < height; x++) {

		for (int y = 0; y < width; y++) {

			if (y == 0 || y == width - 1) {
				printf("%c", board[x][y]);
			}
			else if (x == 0 || x == height - 1) {
				printf("%c", board[x][y]);
			}
			else {
				printf("%c",board[x][y]);
			}

		}
		printf("\n");
	}
	for (int x = 0; x < height; x++) free(board[x]);
	free(board);
	
	return 0;
}


int moveFishes(struct fish fisharray[], int numFish,int boardwidth) {

	//Scannt nach jedem Fisch.
	for (int f = 0; f < numFish; f++) {
		if (fisharray[f].y == boardwidth-7) {  //Sobald der Fisch width-7 erreicht hat wird er mit dem umgedrehten Fisch ersetzt und die Schwimmrichtung wird angepasst.
			strcpy_s(fisharray[f].symbol, sizeof(fisharray[f].symbol), "<)))><"); //strcpy_s braucht die größe des Arrays.
			fisharray[f].direction = -1;
		}
		else if (fisharray[f].y == boardwidth - boardwidth+1) { //Sobald der Fisch width-width+1 (y=1) erreicht hat wird er mit dem umgedrehten Fisch ersetzt und die Schwimmrichtung wird angepasst.
			strcpy_s(fisharray[f].symbol, sizeof(fisharray[f].symbol), "><)))>"); 
			fisharray[f].direction = 1;
		}
		fisharray[f].y += fisharray[f].direction; //Danach wird es ins Array übertragen.
	}

	return 0;

	
}


struct fish* createFish(int numFish,int boardheight,int boardwidth) {
	
	srand((unsigned int)time(NULL)); //Seed für random number generation.

	int* randNumbers = malloc(boardheight * sizeof(int));
	if (randNumbers == NULL) {      
		printf("Memory allocation failed.\n");
		exit(1);               
	}

	struct fish* fishes = (struct fish*)malloc(numFish * sizeof(*fishes)); 

	//Überprüft ob speicher freigegeben wurde.
	if (fishes == NULL) {
		printf("\nMemory allocation failed.\n");
		return NULL;
	}

	//Füllt ein Array an das später geshuffled wird. Dies garantiert zufällige Zahlen die sich nicht wiederholen.
	for (int i = 1; i < boardheight; i++) {
		randNumbers[i] = i;
	}

	shuffle(randNumbers,boardheight-1);

	for (int i = 0; i < numFish; i++) {
		fishes[i].x = randNumbers[i];
		fishes[i].y = rand() % (boardwidth-7);
		if (rand() % 2 == 0) {
			fishes[i].direction = -1;
			strcpy_s(fishes[i].symbol, sizeof(fishes[i].symbol), "<)))><"); //Hier wird der sprite des Fisches angepasst an die richtung in die er Schwimmt.
		}
		else {
			fishes[i].direction = 1;
			strcpy_s(fishes[i].symbol, sizeof(fishes[i].symbol), "><(((>"); //Hier wird der sprite des Fisches angepasst an die richtung in die er Schwimmt.
		}		
		fishes[i].symbol[sizeof(fishes[i].symbol) - 1] = '\0'; //Hier wird \0 gelöscht.
	}

	return fishes;
}


int inputHandling(int argc,char *argv[], int *numFish, int *height, int *width, int *frames) {

	int startIndex = 1;   //Startindex wird gesetzt um den Befehl nicht als Int zu lesen.
	int numCount = argc - startIndex; 
	long int numbers[5];
	
	if (argc < 2) {
		printf("\nArguements missing. Please refer to --help.\n");
		exit(1);
	}

	if (argc != 5) {			//Hier wird geprüft ob die Anzahl der Argumente stimmt.
		printf("\nThis function needs 4 arguements. Please refer to --help.\n");
		exit(1);
	}

	//Hier wird help definiert.
	if (strcmp(argv[1], "--help") == 0) {
		printf("\n=== Please use whole numbers. ===\n");
		printf("\n[Number of Fish] [Height of board] [Width of board] [Refreshrate in ms]\n");
		printf("\nNumbers are capped because of cmd limitations.\n");
		printf("\nNumber of Fish max = 68 | Height max = 70 | Width max = 275 and min = 9\n");
		printf("\nMaximize cmd window. For best experience use height of 70 and 100ms refreshrate.\n");
		exit(1);
	}

	


	//Hier wird alles nach Startindex geprüft und in einem int array gespeichert. Diese Methode scannt gleich alle eingaben auf einmal.
	for (int i = 0; i < numCount; i++) {
		char* endptr;
		argv[startIndex + i][strcspn(argv[startIndex + i], "\r\n\t ")] = '\0'; //Dies sorgt dafür das jedes argv einzeln gespeichert wird und nicht zusammengefügt wird.
		numbers[i] = strtol(argv[startIndex + i], &endptr,10);

		//Sucht im Userinput nach fehleingaben
		if (*endptr != '\0') {
			printf("Invalid: %s. Please refer to --help\n", argv[startIndex + i]);
			exit(1);
		}

	}
	
	if (numbers[0] > 68 || numbers[1] > 70 || numbers[2] > 275 || numbers[2] < 9) {
		printf("\nPlease stay within the set limit.\n");
		printf("\nNumber of Fish max = 68 | Height max = 70 | Width max = 275 and min = 9\n");
		exit(1);
	}


	*numFish = numbers[0];
	*height = numbers[1];
	*width = numbers[2];
	*frames = numbers[3];


	return 0;

}