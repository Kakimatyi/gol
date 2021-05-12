#pragma once
#include"cell.h"
#include"evol.h"
#include<vector>
#include<iostream>

using namespace std;

// itt vannak p�ld�nyos�tva a sejtek, �s kapnak �rt�ket az elej�n
// a t�bla felt�lt�se �rt�kekkel (1/0)
class grid
{

public:

	//glider jobb als� sark�nak kezdeti pozi megad�sa
	// ehhez lehet kiv�telkezel�st �rni
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