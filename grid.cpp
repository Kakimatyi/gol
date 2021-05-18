#include"grid.h"
#include<vector>
#include<iostream>

using namespace std;


void grid::evol() {
	
	struct coord { // a v�ltoztatott �llapot� sejtek koordin�t�inak t�rol�sa ebben a structban
		int x, y;
	}; 

	vector<coord> temp; // az eg�sz t�bl�t �jra lementeni mem�riaig�nyes lenne, �gy el�g csak a v�ltoztatottakat egy vektorba menteni

	//ez v�gigmeny a t�bla elemein szomsz�d ut�n keresve
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			
			int szomsz = 0;
			int startw=j-1, vegw=j+2; //ezekig ellenoriz vizszintesen [][j] a masodik az x koord
			
			//szelen levokre mas vonatkozik
			if (j == 0) { startw = 0; }			//ha bal szelen akkor a bal oldali szomszeddal kezd
			if (j == width - 1) { vegw = width; } //ha jobb szelen

			//felso szomszedok
			if (i > 0) {
				for (int k = startw; k < vegw; k++) {
					if (table[i - 1][k].getstate() == true) { szomsz++;}
				}
			}

			//also szomszedok
			if (i < height-1) {
				for (int k = startw; k < vegw; k++) {
						
					if (table[i + 1][k].getstate()) {  szomsz++;}
				}
					
			}

			//oldalso szomszedok
			if (j > 0 && table[i][j - 1].getstate()) { szomsz++;} 
			if(j < width - 2 && table[i][j + 1].getstate()) { szomsz++;}

				
			//szamolt szomszedok alapjan lemeti a valtoztatott allapotu sejteket
			if (szomsz == 3 && !table[i][j].getstate()) {
				
				coord c;
				c.x = j;
				c.y = i;
				temp.push_back(c); //eleg ennyi, es akkor csak az ellenkezojere valtoztatja a state-t
			}

			if ((szomsz < 2 || szomsz>3) && table[i][j].getstate()) {
				
				coord c;
				c.x = j;
				c.y = i;
				temp.push_back(c);
			}
		}
	}

	//a lementett koordin�t�k �llapot�nak felcser�l�se
	for (int i = 0; i < temp.size(); i++) {
		table[temp[i].y][temp[i].x].flipstate();
	}
}



	




