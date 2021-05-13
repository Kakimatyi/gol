#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include <math.h>
#include <stdlib.h>
#include<iostream>
#include <windows.h>
#include<vector>
#include "cell.h"
#include"evol.h"
#include"grid.h"

using namespace std;

/*//////////////
game of life rules

	Any live cell with two or three live neighbours survives.
Any dead cell with three live neighbours becomes a live cell.
Cells with less than two or more than 3 neighbours die
	All other live cells die in the next generation.Similarly, all other dead cells stay dead.


/////////////*/

//SDL fuggvenyek kifejtese

void drawGrid(SDL_Renderer *r, int SCREEN_WIDTH, int SCREEN_HEIGHT, int CELL_SIZE) {
	// Draw vertical grid lines

	

	for (int v = CELL_SIZE; v < SCREEN_WIDTH; v += CELL_SIZE) {
		// Set draw colour to grey
		SDL_SetRenderDrawColor(r, 110, 110, 110, 110);

		// Draw vertical line
		SDL_RenderDrawLine(r, v, 0, v, SCREEN_HEIGHT);
	}

	// Draw horizontal grid lines
	for (int h = CELL_SIZE; h < SCREEN_HEIGHT; h += CELL_SIZE) {
		// Set draw colour to grey
		SDL_SetRenderDrawColor(r, 110, 110, 110, 110);

		// Draw horizontal line
		SDL_RenderDrawLine(r, 0, h, SCREEN_WIDTH, h);
	}
}

void drawCells(SDL_Renderer *r, cell **table, int height, int width, int CELL_SIZE) {
	// Define cell width/height
	SDL_Rect cell;
	cell.w =  + 1; // egy meretu a racs
	cell.h = CELL_SIZE + 1;

	// Draw living cells
	int cx, cy;
	for (cy = 0; cy < height; cy++) {
		for (cx = 0; cx < width; cx++) {
			if (table[cy][cx].getstate()) {
				// Set cell x/y pos
				cell.x = cx * CELL_SIZE;
				cell.y = cy * CELL_SIZE;

				SDL_SetRenderDrawColor(r, 255, 255, 255, 1);
				SDL_RenderFillRect(r, &cell);
			}
		}
	}
}




int main(int argc, char *argv[]) {
	/* SDL inicializálása és ablak megnyitása */
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
		exit(1);
	}
	
	SDL_Window *window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 420, 360, 0);
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

	

	/* rajzok */
	/*int x, y, r;
	r = 50;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
	SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
	SDL_RenderDrawLine(renderer, 340, 240, 320, 200);
	SDL_RenderDrawLine(renderer, 0, 100, 200, 200);
	

	SDL_Point point;
	point = {1,2};
	SDL_RenderDrawPoint(renderer, 300, 10);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect rectangle;

	rectangle.x = 0;
	rectangle.y = 0;
	rectangle.w = 50;
	rectangle.h = 50;
	SDL_RenderFillRect(renderer, &rectangle);
	SDL_RenderPresent(renderer);
	*/

	/* az elvegzett rajzolasok a kepernyore */

	drawGrid(renderer, 500, 500, 10);

	grid table(20, 20);
	cell** board = table.gettable();

	while (1==2) {
		drawCells(renderer, table.gettable(), 20, 20, 10);
		SDL_RenderPresent(renderer);
		table.evol();

		/* varunk a kilepesre */
		/*SDL_Event ev;
		while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
		}
		SDL_Delay(500);
		SDL_RenderClear(renderer);*/
	}

	/* ablak bezarasa */
	SDL_Quit();
///////////////////////////////////////////////////////////////////////////////////

	int a, b;
	cin >> a >> b;
	grid tabla(a,b);
	
	while (1) {
		tabla.print();
		tabla.evol();
		Sleep(500);
		system("CLS");
	}

	return 0;
}