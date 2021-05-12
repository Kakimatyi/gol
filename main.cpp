#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include <math.h>
#include <stdlib.h>
#include<iostream>
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
int main(int argc, char *argv[]) {
	/* SDL inicializálása és ablak megnyitása */
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
		exit(1);
	}
	
	SDL_Window *window = SDL_CreateWindow("SDL peldaprogram", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 440, 360, 0);
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
	SDL_RenderPresent(renderer);

	/* varunk a kilepesre */
	/*SDL_Event ev;
	while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
	}*/

	/* ablak bezarasa */
	SDL_Quit();
///////////////////////////////////////////////////////////////////////////////////


	grid tabla;

	vector<cell> cells;

	tabla.glider(cells,3,3);
	tabla.printcells(cells,10,10);
	return 0;
}