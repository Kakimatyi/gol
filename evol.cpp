#include "evol.h"

// cells vektorban t�rolt sejtek szomsz�djainak ellen�rz�se
void evol::evolfun(vector<cell> cells, int height, int width) {

	vector<cell> temp; // a v�ltoztatott �llapot� sejtek lement�se, hogy a k�r v�g�n �t�rja �ket

	for (int i = 0; i < cells.size(); i++) {
		int szomsz = 0;

		int x = cells[i].getx(); int y = cells[i].gety(); //egyszerubb kezeles

		//v�gigmegy a t�bbi sejten, hogy szomsz�dok-e 
		for (int j = 0; j < cells.size(); j++) {
			if (j != i) {

				//relat�v poz meghat�roz�sa 
				if (abs(cells[j].gety() - y) == 1) { //felett vagy alatt
					if (abs(cells[j].getx() - x) <= 1) { szomsz++; }
				}
				if (cells[j].gety() - y == 0) { //egy sorban van vele
					if (abs(cells[j].getx() - x) == 1) { szomsz++; }
				}

			}

			//szamolt szomszedok alapjan lemeti a v�ltoztatott �llapot� sejteket ///////////////////////////
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