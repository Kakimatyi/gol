#pragma once
#include<iostream>
using namespace std;

//osztaly a sejtek koordinatainak tarolasara egyedileg

class cell
{
private:
	int x; //koordináták
	int y;
	bool state; //élõ vagy holt

public:
	cell() { state = 0; }
	//~cell() { delete x; delete y; }

	int getx()const { return x; }
	int gety()const { return y; }
	bool getstate()const { return state; }
	void setx(int xcoord) { x = xcoord; }
	void sety(int ycoord) { y = ycoord; }
	void setstate(bool newstate) { state = newstate; }
	void flipstate(){
		if (state) { setstate(0); }
		else { setstate(1); }

	}

	//temprol atiro fv ide


	/*void operatorprint(ostream &os) const {
		os << x;
	}*/

};

/*ostream & operator<<(ostream &os, const cell &c) {
	c.operatorprint(os);
	return os;
}*/


