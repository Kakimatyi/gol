#pragma once

#include<vector>
#include "cell.h"


//esetleg amugy orokolhetne a cell valtozoit de logikusan nincs ertelme
//cell classnak a friendje
//a definialast atirni a .cpp-be

class evol
{

public:
	vector<cell> temp;

// cells vektorban tárolt sejtek szomszédjainak ellenõrzése
	void evolfun(vector<cell> cells, int height, int width);
};


