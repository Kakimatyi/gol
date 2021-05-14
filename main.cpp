#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include<string>
#include<sstream>
#include <math.h>
#include <stdlib.h>
#include<iostream>
#include <windows.h>
#include<vector>
#include "cell.h"
#include"grid.h"

#define CELL_SIZE 10

using namespace std;

/*//////////////
game of life rules

	Any live cell with two or three live neighbours survives.
Any dead cell with three live neighbours becomes a live cell.
Cells with less than two or more than 3 neighbours die
	All other live cells die in the next generation.Similarly, all other dead cells stay dead.


/////////////*/

//SDL fuggvenyek kifejtese

void drawGrid(SDL_Renderer *r, int SCREEN_WIDTH, int SCREEN_HEIGHT) {
	// Draw vertical grid lines

	for (int w = CELL_SIZE; w < SCREEN_WIDTH; w += CELL_SIZE) {
		// Set draw colour to grey
		SDL_SetRenderDrawColor(r, 110, 110, 110, 110);

		// Draw vertical line
		SDL_RenderDrawLine(r, w, 0, w, SCREEN_HEIGHT);
	}

	// Draw horizontal grid lines
	for (int h = CELL_SIZE; h < SCREEN_HEIGHT; h += CELL_SIZE) {
		// Set draw colour to grey
		SDL_SetRenderDrawColor(r, 110, 110, 110, 110);

		// Draw horizontal line
		SDL_RenderDrawLine(r, 0, h, SCREEN_WIDTH, h);
	}
}

void drawCells(SDL_Renderer *r, cell **table, int height, int width) {
	// Define cell width/height
	SDL_Rect cell;
	cell.w = CELL_SIZE; 
	cell.h = CELL_SIZE;

	// elo cellak kirajzolasa
	bool hope = false; //ha nincs elo cella, akkor ne nezze tovabb

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (table[i][j].getstate()) {
				hope = true;
				// kirajzolando cella xy koord
				cell.x = j * CELL_SIZE;
				cell.y = i * CELL_SIZE;

				SDL_SetRenderDrawColor(r, 255, 255, 255, 1);
				SDL_RenderFillRect(r, &cell);
			}
		}
	}
	if (!hope) { 
		SDL_Delay(60000); 
		SDL_Quit();
	} // egy percig var utana bezarja
}

//miert ide kell
ostream& operator<<(ostream &os, const grid table) {
	table.operatorprint(os);
	return os;
}

//az egyedi allapot megadashoz menti ilyen tipusba a beirt koordinatakat
struct coord {
	int x;
	int y;
};

istream& operator>>(istream &is, coord &c) {
	int szam;
	bool xjon=true;
	is >> c.x;
	is >> c.y;
	return is;
}

int main(int argc, char *argv[]) {
	SDL_Event ev; //mar a menu is hasznalja azert van itt

	//pályaméret, és kezdeti állapot bekérése
	char defsize, defstate;
	int height, width;

	cout << "Game of Life" << endl << endl;
	cout << "Space - pause" << endl << "jobbra nyil (->) leptet";
	//palya valasztas
	do {
		cout << "Az alapertelmezett (20x20) palyamerettel jatszik? (y/n)";
		cin >> defsize;
	} while (defsize != 'y' && defsize != 'n');

	if (defsize == 'n') {
		cout << "Adja meg a palya mereteit!" << endl;

		cout << "magassag: ";
		cin >> height;
		cout << "szelesseg: ";
		cin >> width;
	}
	else { height = 10; width = 20;}

	grid table(height, width); //ha akrja ezt lehet atirni azert itt, mert itt mar tud meretet

	//kezdeti allapot valasztas
	do {
		cout << "Az alapertelmezett allapotbol indul? (y/n)";
		cin >> defstate;
	} while (defstate != 'y' && defstate != 'n');

	//cellak bekerese
	/*if (defstate == 'n') {
		system("cls");

		//a kirajzolasig ebbol abrazol
		int** table = new int*[width];
		for (int i = 0; i < width; i++) {
			table[i] = new int[height];
		}

		//tabla rajzolasa, hogy lassa mit hova akar tenni
			for (int k = 0; k < width; k++) {

				if (k < 9) {
					if (k == 0) { cout << "   " << k + 1 << "  "; }
					else { cout << k + 1 << "  "; }
				}
				else {
					cout << k + 1 << " ";
				}
			}
			cout << endl;

			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width - 1; j++) {
					if (j == 0) {
						if (i < 9) { cout << i + 1 << " |_ |"; }
						else { cout << i + 1 << "|_ |"; }
					}
					if (j == width - 1) { cout << "_ |"; }
					else { cout << "_ |"; }
				}cout << endl;
			}
			cout << endl << "Irja be az eleszteni kivant sejt koordinatait (befejezes negativ koordinataval)\n";
			coord c;
			do { 
				//koord beir
				cin >> c; 
				
			system("cls");
			//tabla rajzolasa, hogy lassa mit hova akar tenni
			for (int k = 0; k < width; k++) {

				if (k < 9) {
					if (k == 0) { cout << "   " << k + 1 << "  "; }
					else { cout << k + 1 << "  "; }
				}
				else {
					cout << k + 1 << " ";
				}
			}
			cout << endl;

			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width - 1; j++) {
					if (j == 0) {
						if (i < 9) { cout << i + 1 << " |_ |"; }
						else { cout << i + 1 << "|_ |"; }
					}
					if (j == width - 1) { cout << "_ |"; }
					else { cout << "_ |"; }
				}cout << endl;
			}
			cout << endl << "Irja be az eleszteni kivant sejt koordinatait (befejezes negativ koordinataval)\n";

			} while (c.x >= 0 && c.y>0);

			cout << "A jatek inditasahoz nyomjon barmilyen gombot!";
			while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT && ev.type!=SDL_KEYDOWN) {}

			cout << "Loading...";
			
			system("cls");
			cout << "Nezze a masik ablakot!";
	}*/


	/* SDL inicializálása és ablak megnyitása */
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
		exit(1);
	}
	
	SDL_Window *window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, height*10, width*10, 0);
	if (window == NULL) {
		SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
		exit(1);
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (renderer == NULL) {
		SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
		exit(1);
	}
	SDL_RenderClear(renderer);

	drawGrid(renderer, height*10, width*10);
	SDL_RenderPresent(renderer);
	
	bool run=true; //fut-e magatol
	bool step;	//leptetes
	
	SDL_RenderClear(renderer);
		/* ez ketyeg, varunk a kilepesre */
	 int count = 0;

	while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {

		if (run) { //magatol megy 
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);
			drawGrid(renderer, height * 10, width * 10);
			drawCells(renderer, table.gettable(), height, width);
			SDL_RenderPresent(renderer);
			table.evol();
			SDL_Delay(100);
		}

		switch (ev.type){ //pause vagy leptetes
		case SDL_KEYDOWN:
			switch (ev.key.keysym.sym)
			{
				case SDLK_SPACE: { //beallitja a futas bool, vagy valami enumot mint a snake-ban
					if (run) { run = false; }
					else { run = true; }//ha space bill lenyomva, run flipstate
				}
				case SDLK_RIGHT: {
					if (!run) {
						SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
						SDL_RenderClear(renderer);
						drawGrid(renderer, height * 10, width * 10);
						drawCells(renderer, table.gettable(), height, width);
						SDL_RenderPresent(renderer);
						table.evol();
						SDL_Delay(100);
					}
				}
			}
		}		
	}

		//ez simán fut
		/*while(1){
			// Set screen colour to white
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

			// Render white to screen (clear screen)
			SDL_RenderClear(renderer);
			
			drawGrid(renderer, height*10, width*10);
			drawCells(renderer, table.gettable(), height, width);
			SDL_RenderPresent(renderer);
			table.evol();
			SDL_Delay(80);
		}*/
		
	/* ablak bezarasa */
	SDL_Quit();
/////////////////////////////////////////////////////////////////////////////////// konzolos kiírás


	/*int a, b;
	cin >> a >> b;
	grid tabla;
	
	while (1) {
		tabla.print();
		tabla.evol();
		Sleep(200);
		system("CLS");
	}*/


	return 0;
}