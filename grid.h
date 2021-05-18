#ifndef GRID_H
#define GRID_H

#include"cell.h"
#include<vector>
#include<iostream>

using namespace std;

// itt vannak példányosítva a sejtek, és kapnak értéket az elején
// a tábla feltöltése értékekkel (1/0)
class grid
{

private:
	cell** table;
	int height;
	int width;

public:

	//visszaadja a tablat
	cell** gettable() const{
		return table;
	}

	//2d tomb ami a palya lesz, ebben a tombben lesznek tarolva az egyes cellak peldanyai 2d-ben
	//default constructor 20x20 palya gliderrel a felso sarokban
	grid() {
		height = 20;
		width = 20;

		//2d dinamikus tabla letrehozasa a memoriaba
		table = new cell*[width];
		for (int i = 0; i < width; i++)
			table[i] = new cell[height];

		cell nullsejt;
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				table[i][j] = nullsejt; //alapbol halott sejtet rak bele, feltolti nullakkal a tablat
			}
		}

		//glider betöltése
		int glidarr[3][3] = { 1,1,1,1,0,0,0,1,0 };

		/*for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				table[2 - i][2 - j].setstate(glidarr[i][j]);
			}
		}*/
	}

	grid(int h, int w) {
		if (h < 10 || w < 10) { throw domain_error("tul kicsiny palyameret");}
		height = h;
		width = w;

		//2d dinamikus tabla letrehozasa a memoriaba
		table = new cell*[height];
		for (int i = 0; i < height; i++)
			table[i] = new cell[width];

		cell nullsejt;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				table[i][j] = nullsejt; //alapbol halott sejtet rak bele, feltolti nullakkal a tablat
			}
		}
	}

	//glider betöltése
	void glider() {
		int glidarr[3][3] = { 1,1,1,1,0,0,0,1,0 };

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				table[2 - i][2 - j].setstate(glidarr[i][j]);
			}
		}
	}

	~grid() {
		for (int i = 0; i < width; ++i) {
			delete[] table[i];
		}
		delete[] table;
	}

	/*void gliderbonyi(vector<cell> cells, int glidx, int glidy); //a vektorba betolt egy 3x3 as cells-t glider alakban*/

	/*void printcells(vector<cell> cells, int height, int width) const {

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				for (int k = 0; k < cells.size(); k++) {
					if (cells[k].getx() == j && cells[k].gety() == i) {
						if (cells[k].getstate()) { cout << "1"; }
					}
					else cout << "0";
				}
			}
		}
	}*/

	void evolfun(vector<cell> cells, int height, int width);

	//evolfun 2d tombre
	void evol(); 

	void operatorprint(ostream &os)const{
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				os << table[i][j].getstate();
			}os << endl;
		}
	}

	void print()const {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				cout << table[i][j].getstate();
			}cout << endl;
		}
	}

	//igy nem kell egy masolatot csinalnunk rola tabla1=table.gettable()-lel, amit minden korbe le kell frissiteni az eredetirol
	bool getcellstate(int x, int y) {
		return table[x][y].getstate();
	}

	void cellbeker(int x, int y) { //felhasznalo altal megadott koordinatakon elove teszi a cellat
		table[x][y].setstate(1);
	}
};


#endif