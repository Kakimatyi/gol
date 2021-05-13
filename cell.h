#ifndef CELL_H
#define CELL_H
#include<iostream>
using namespace std;


//osztaly a sejtek koordinatainak tarolasara egyedileg

class cell
{
private:
	
	bool state; //élõ vagy holt

public:
	cell() { state = 0; }
	//~cell() { }

	bool getstate()const { return state; }
	void setstate(bool newstate) { state = newstate; }
	void flipstate(){
		if (state) { setstate(0); }
		else { setstate(1); }

	}


	/*void operatorprint(ostream &os) const {
		os << state;
	}*/

}; 
#endif
/*ostream & operator<<(ostream &os, const cell c) {
	c.operatorprint(os);
	return os;
}*/



