#pragma once

#include"evol.h"
#include"grid.h"
#include<vector>
#include<iostream>

using namespace std;

void grid::glider(vector<cell> cells, int glidx, int glidy) {

	int gx = glidx, gy = glidy; //glider jobb also sarkanak koordinatai								//001
																									//101    ez egy glider
	int glidarr[3][3] = { 1,1,1,1,0,0,0,1,0 }; //allapotok jobb alsobol oszloponkent visszafele		//011    

	for (int i = 0; i < 3; i++) { //peldanyositas koord és állapot megadás
		for (int j = 0; j < 3; j++) {
			cell c;
			c.setx(gx - i); c.sety(gy - j); c.setstate(glidarr[i][j]);
			cells.push_back(c);

		}
	}
	for (int i = 0; i < cells.size(); i++) {
		cout << cells[i].getx() <<" "<< cells[i].gety()<<endl;
	}
}

void grid::evolfun(vector<cell> cells, int height, int width) {

	vector<cell> temp; // a változtatott állapotú sejtek lementése ide, hogy a kör végén átírja õket

	for (int i = 0; i < cells.size(); i++) {
		int szomsz = 0;

		int x = cells[i].getx(); int y = cells[i].gety(); //egyszerubb kezeles

		//végigmegy a többi sejten, hogy szomszédok-e 
		for (int j = 0; j < cells.size(); j++) {
			if (j != i) {

				//relatív poz meghatározása 
				if (abs(cells[j].gety() - y) == 1) { //felett vagy alatt
					if (abs(cells[j].getx() - x) <= 1) { szomsz++; }
				}
				if (cells[j].gety() - y == 0) { //egy sorban van vele
					if (abs(cells[j].getx() - x) == 1) { szomsz++; }
				}

			}

			//szamolt szomszedok alapjan lemeti a változtatott állapotú sejteket ///////////////////////////
			if (szomsz == 3 && !cells[i].getstate()) {
				cell c;
				c.setx(x); c.sety(y); c.setstate(1);
				temp.push_back(c);
			}

			if ((szomsz < 2 || szomsz>3) && cells[i].getstate()) {
				cell c;
				c.setx(x); c.sety(y); //constr-ban state alapbol false
				temp.push_back(c);
			}
		}
	}
}

