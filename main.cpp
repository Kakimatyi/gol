#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include<string>
#include<sstream>
//#include <math.h>
#include <stdlib.h>
#include<fstream>
#include<iostream>
//#include <windows.h>
#include "cell.h"
#include"grid.h"

//egy negyzetracs merete
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

//racsos palya rajzolasa
void drawGrid(SDL_Renderer *r, int SCREEN_WIDTH, int SCREEN_HEIGHT) {
	// Draw vertical grid lines

	for (int w = CELL_SIZE; w < SCREEN_WIDTH; w += CELL_SIZE) {
	
		SDL_SetRenderDrawColor(r, 110, 110, 110, 110);

		// Fuggoleges vonalak
		SDL_RenderDrawLine(r, w, 0, w, SCREEN_HEIGHT);
	}

	// Vizszintes vonalak
	for (int h = CELL_SIZE; h < SCREEN_HEIGHT; h += CELL_SIZE) {
	
		SDL_SetRenderDrawColor(r, 110, 110, 110, 110);

		
		SDL_RenderDrawLine(r, 0, h, SCREEN_WIDTH, h);
	}
}

//elo cellak rajzolasa
void drawCells(SDL_Renderer *r, cell **table, int height, int width) {
	// Cella meretek
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
		
		SDL_Quit();
	} // ha mar nincs elo cella, bezarja az ablakot
}

//user eventet general, hogy akkor is fusson, mikor nem nyul hozza
/*Uint32 idozit(Uint32 ms, void *param) {
	SDL_Event ev;
	ev.type = SDL_USEREVENT;
	SDL_PushEvent(&ev);
	return ms;   // ujabb varakozas 
}*/

//tabla kiiras
ostream& operator<<(ostream &os, const grid table) {
	table.operatorprint(os);
	return os;
}

//az egyedi allapot megadashoz menti ilyen tipusba a beirt koordinatakat
struct coord {
	int x;
	int y;
};

//palya meret bekeresnel hasznalja
istream& operator>>(istream &is, coord &c) {
	int szam;
	bool xjon = true;
	is >> c.x;
	is >> c.y;
	return is;
}

int tesztelo() {

	cell sejt;
	//varhato sor: def state utan 0, flipstate utan 1, setstate utan 0
	cout << endl << " sejt teszt getstate " << sejt.getstate();
	sejt.flipstate();
	cout << " flipstate " << sejt.getstate();
	sejt.setstate(0);
	cout << " setstate " << sejt.getstate();
	cout << endl;

	int a, b;
	cout << "palya meretek ket szam: ";
	cin >> a >> b;
	grid tabla;

	//konzolos kiiras az evol fv tesztelesere
	/*while (1) {
		tabla.print();
		tabla.evol();
		Sleep(200);
		system("CLS");
	}*/

	cout << "default tabla (20x20):" << endl;
	tabla.print();

	cout << endl << "meretes tabla:" << endl;
	try { grid meretestabla(a, b); meretestabla.print(); }
	catch (exception &e) { cout << stderr << " " << e.what(); return 1; }

	cout << endl << "sejt bekeres: " << endl;

	tabla.cellbeker(10, 10);
	tabla.print();

	cout << endl << "gettable teszt" << endl;
	cell** masolat = tabla.gettable();
	cout << masolat[10][10].getstate(); //ez lett 1 a cellbeker miatt 

	cout << endl << "getcellstate" << endl;
	cout << tabla.getcellstate(10, 10);

	cout << endl << "glider berakasa" << endl;
	tabla.glider();
	tabla.print();

	
	/*try { cout << optabla; }
	catch (exception &e) { cout << stderr << " " << e.what(); return 1; }*/
}


int main(int argc, char *argv[]) {
	//delay helyett idozito
	//SDL_TimerID id = SDL_AddTimer(500, idozit, NULL);

	SDL_Event ev; //mar a menu is hasznalja azert van itt

	//pályaméret, és kezdeti állapot bekérése
	char defsize, defstate, iffile;
	int height, width; // ez csak a bekeres miatt hasznalatos, utana a tabla privat valtozoit hasznlja getterekkel, igy veletlen se romolhatnak el a dimenziok 

	grid *table=NULL; // igy az ifeken belul is lehet peldanyositani
	
	//menu
	cout << "Game of Life" << endl << endl<<"Iranyitas"<<endl;
	cout << "Space - pause" << endl << "jobbra nyil (->) leptet" << endl << endl;

	do {
		cout << "Filebol beolvasott allapotbol indul? (palya.txt) (y/n)";
		cin >> iffile;
	} while (iffile != 'y' && iffile != 'n');

	if (iffile == 'y') { //filebol olvasas
		ifstream file;
		file.open("palya.txt");

		if (file.is_open()) {
			string beolvas;

			int sor = 0;
			//eloszor lemeri a palya mereteket beolvasassal
			while (!file.eof()) {
				file >> beolvas;
				sor++;
			}

			height = sor+1; width = int(beolvas.size());
			table = new grid(height, width);
			file.close();

			//most ujra vegigmegy de most be is tolti a cellakat
			sor = 0;
			file.open("palya.txt");
			while (!file.eof()) {
				file >> beolvas;

				for (int j = 0; j < width; j++) {
					if (beolvas[j]=='1') {
						 //csak az eloket rakja bele a tobbi default 0
						table->cellbeker(sor, j);
					}
				}
				sor++;
			}
			file.close();
		}
		else { cout << "palya.txt nem talalhato a program mappajaban"; }
	}
	else {

		//palyameret bekeres
		do {
			cout << "Az alapertelmezett (20x20) palyamerettel jatszik? (y/n)";
			cin >> defsize;
		} while (defsize != 'y' && defsize != 'n');

		if (defsize == 'n') {
			cout << "Adja meg a palya mereteit (legalabb 10x10)!" << endl;

			cout << "magassag: ";
			cin >> height;
			cout << "szelesseg: ";
			cin >> width;
		}
		else { height = 20; width = 20; } //habar van def constr 20x20-as tablaval, igy egyszerubb
		try { table = new grid(height, width); }
		catch (exception &e) { cout << stderr << " " << e.what(); return 1; }

		//kezdeti allapot valasztas
		do {
			cout << "Az alapertelmezett allapotbol indul? (y/n)";
			cin >> defstate;
		} while (defstate != 'y' && defstate != 'n');

		//cellak bekerese
		if (defstate == 'n') {
		
			//bekert koordinataknak, azert kell ide, mert a do-while ezt figyeli
			coord c;
			
			do {
		
				system("cls");
				//tabla rajzolasa, hogy lassa mit hova akar tenni
				for (int k = 0; k < table->getwidth(); k++) {

					if (k < 9) {
						if (k == 0) { cout << "   " << k + 1 << "  "; }
						else { cout << k + 1 << "  "; }
					}
					else {
						cout << k + 1 << " ";
					}
				}
				cout << endl;

				//fontos, hogy table[y][x] fordittot koordinatazas van
				for (int i = 0; i < table->getheight(); i++) {
					for (int j = 0; j < table->getwidth(); j++) {
						if (j == 0) { //elso oszlop
							if (i < 9) { if (table->getcellstate(i, j)) { cout << i + 1 << " |O |"; } else { cout << i + 1 << " |_ |"; } }
							else { if (table->getcellstate(i, j)) { cout << i + 1 << "|O |"; } else { cout << i + 1 << "|_ |"; } }
						}
						else {

							if (j == table->getwidth() - 1) { if (table->getcellstate(i, j)) { cout << "O |"; } else { cout << "_ |"; } }
							else { if (table->getcellstate(i, j)) { cout << "O |"; } else { cout << "_ |"; } }
						}
					}cout << endl;
				}

				cout << endl << "Irja be az eleszteni kivant sejt koordinatait (befejezes tablan kivuli koordinataval\n";

				//koord beir
				cin >> c;
				c.x = c.x - 1;
				c.y = c.y - 1;

				if (c.x >= 0 && c.y >= 0 && c.x < table->getwidth() && c.y < table->getheight()) { table->cellbeker(c.y, c.x); } // a kilepo koordinatak miatt

			} while (c.x >= 0 && c.y >= 0 && c.x < table->getwidth() && c.y < table->getheight());

			
			system("cls");
			cout << "Nezze a megjeleno ablakot!";
		}
		else { table->glider(); }
	}


	/* SDL inicializálása és ablak megnyitása */
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
		exit(1);
	}
	
	SDL_Window *window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, table->getheight() * 10, table->getwidth() * 10, 0);
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
	
	//drawGrid(renderer, table->getheight() * 10, table->getwidth() * 10);
	//SDL_RenderPresent(renderer);
	

	bool run = true; //fut-e magatol
	bool step;	//leptetes
	
	
	/* ez ketyeg, varunk a kilepesre */
	
	//main while
	while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {

		if (run) { //magatol megy 
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);
			drawGrid(renderer, table->getheight() * CELL_SIZE, table->getwidth() * CELL_SIZE);
			drawCells(renderer, table->gettable(), table->getheight(), table->getwidth());
			SDL_RenderPresent(renderer);
			table->evol();
			SDL_Delay(200);
		}

		switch (ev.type) { //pause vagy leptetes
		case SDL_USEREVENT:
		case SDL_KEYDOWN:
			switch (ev.key.keysym.sym)
			{
				case SDLK_SPACE: { //beallitja a run boolt, ha space bill lenyomva, run flipstate
					if (run) { run = false; }
					else { run = true; }
				}
				case SDLK_RIGHT: { //leptetve futtat
					if (!run) {
						SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
						SDL_RenderClear(renderer);
						drawGrid(renderer, table->getheight() * CELL_SIZE, table->getwidth() * CELL_SIZE);
						drawCells(renderer, table->gettable(), table->getheight(), table->getwidth());
						SDL_RenderPresent(renderer);
						table->evol();
						SDL_Delay(200);
					}
				}
			}
		}
	}

	/* idozito torlese */
	//SDL_RemoveTimer(id);

	/* ablak bezarasa */
	SDL_Quit();
	delete table;
	//tabla pointer torlese

	/*tesztelo();
	cout << endl << " << operator tesztelese" << endl;
	
	grid tablaki(11, 11);
	cout << tablaki;
	*/
	return 0;
}