#pragma once

#include"evol.h"
#include"grid.h"
#include<vector>
#include<iostream>

using namespace std;

void grid::gliderbonyi(vector<cell> cells, int glidx, int glidy) {

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
		//cout << cells[i].getx() <<" "<< cells[i].gety()<<endl;
	}
}

/*void grid::evolfun(vector<cell> cells, int height, int width) {

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
}*/

void grid::evol() {
	//cout << "i= " << width << " j=" << height<<endl;
	struct coord { // a változtatott állapotú sejtek koordinátáinak tárolása ebben a structban
		int x, y;
	}; 

	vector<coord> temp; // az egész táblát újra lementeni memóriaigényes lenne, így elég csak a változtatottakat egy vektorba menteni

	//ez végigmeny a tábla elemein szomszéd után keresve
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			
			int szomsz = 0;

				int startw=j-1, vegw=j+2; //ezekig ellenoriz vizszintesen [][j] a masodik az x koord
			

				//szelen levokre mas vonatkozik
				if (j == 0) { startw = 0; }			//ha bal szelen
				if (j == width - 1) { vegw = width; } //ha jobb szelen
				

				//felso szomszedok
				if (i > 0) {
					for (int k = startw; k < vegw; k++) {
						if (table[i - 1][k].getstate() == true) { szomsz++; /*cout << "szk:" << i + 1 << "," << k << " ";*/ }
					}
									}

				//also szomszedok
				if (i < height-1) {
					for (int k = startw; k < vegw; k++) {
						
						if (table[i + 1][k].getstate()) {  szomsz++; /*cout << "szk:" << i + 1 << "," << k << " ";*/ }
					}
					
				}

				//oldalso szomszedok
				//if (table[i - 1][j].getstate() || table[i + 1][j].getstate()) szomsz++;
				if (j > 0 && table[i][j - 1].getstate()) { szomsz++;} 
				if(j < width - 2 && table[i][j + 1].getstate()) { szomsz++;}

				
			//szamolt szomszedok alapjan lemeti a változtatott állapotú sejteket ///////////////////////////
			if (szomsz == 3 && !table[i][j].getstate()) {
				
				coord c;
				c.x = j;
				c.y = i;
				temp.push_back(c); //elég ennyi, és akkor csak az ellenkezõjére változtatja a state-t
			}

			if ((szomsz < 2 || szomsz>3) && table[i][j].getstate()) {
				
				coord c;
				c.x = j;
				c.y = i;
				temp.push_back(c);
			}
			//cout <<" "<< j <<" "<<i<<" sz:"<<szomsz<<endl;
		}
	}

	

	/*for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << "(" << j << ";" << i << ")" << "s:" << table[i][j].getstate()<<"  ";
		}cout << endl;
	}*/

	for (int i = 0; i < temp.size(); i++) {
		table[temp[i].y][temp[i].x].flipstate();
	}
}



	




