#pragma once
#include"cell.h"
#include"evol.h"
#include<vector>
#include<iostream>

using namespace std;

// itt vannak példányosítva a sejtek, és kapnak értéket az elején
// a tábla feltöltése értékekkel (1/0)
class grid
{

public:

	//glider jobb alsó sarkának kezdeti pozi megadása
	// ehhez lehet kivételkezelést írni
	void glider(vector<cell> cells, int glidx, int glidy); //a vektorba betolt egy 3x3 as cells-t glider alakban

	void printcells(vector<cell> cells, int height, int width) const {

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
	}

	void evolfun(vector<cell> cells, int height, int width);


};