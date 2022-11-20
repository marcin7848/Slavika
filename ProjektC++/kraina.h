#pragma once
#include "checked.h"
#include <list>

using namespace std;

class kraina
{
public:
	kraina();
	virtual ~kraina();
	void setKraina(checked &kr, checked & kr2);
	friend class game;

private:
	int ability;
	int first_place;
	int second_place;
	int third_place;

	int ilosc_boh;
	int ilosc_stwor;
	int ilosc_skarb;

	int max_ilosc_boh;
	int max_ilosc_stwor;
	int max_ilosc_skarb;

	int sterujaca_kraina;
	checked img;

	list < checked >  bohater;
	list < checked >  potwor;
	list < checked >  skarb;


};

