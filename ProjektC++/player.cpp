#include "player.h"



player::player()
{
	ilosc_potworow = 0;
	tyl_bohater = new checked[6];
	tyl_potwor = new checked[6];
}


player::~player()
{
	bohater.clear();
	potwor.clear();
	delete[] tyl_bohater;
	delete[] tyl_potwor;
}

int player::getPoint() const
{
	return pkt;
}

void player::setPoint(int a)
{
	pkt += a;
}

