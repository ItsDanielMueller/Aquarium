#include "fishcmd.h"



int main(int argc,char* argv[]) {
	

	//Variablen initialisieren.
	int numFish, height, width, frames;

	//Hier wird der Userinput auf fehler überprüft und in integer umgewandelt.
	inputHandling(argc, argv, &numFish, &height, &width, &frames);


	//Hier wird Userinput behandelt um die Anzahl der Fische zu bestimmen.
	struct fish* fishes = createFish(numFish, height,width);

	
	//Animationsloop
	while (1) {
		drawboard(fishes, numFish,height,width);
		moveFishes(fishes, numFish,width);
		Sleep(frames);
		system("cls");
		
	}

return 0;
}