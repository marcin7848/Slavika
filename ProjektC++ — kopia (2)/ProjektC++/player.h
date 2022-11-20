#pragma once
#include "checked.h"
#include <list>

using namespace std;

class player
{
public:
	player();
	virtual ~player();
	friend class game;

private:
	int id;
	int human;
	sf::String name;
	int pkt;
	list < checked >  bohater;
	list < checked >  potwor;
	checked *tyl_bohater;
	checked *tyl_potwor;
	int ilosc_potworow;
	int id_text_pkt;

};

