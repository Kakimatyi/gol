#include "evol.h"

// cells vektorban tárolt sejtek szomszédjainak ellenõrzése
void evol::evolfun(vector<cell> cells, int height, int width) {

	vector<cell> temp; // a változtatott állapotú sejtek lementése, hogy a kör végén átírja õket

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