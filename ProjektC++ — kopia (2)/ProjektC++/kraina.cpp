#include "kraina.h"



kraina::kraina()
{
	ability = 0;
	first_place = 0;
	second_place = 0;
	third_place = 0;
	ilosc_boh = 0;
	ilosc_stwor = 0;
	ilosc_skarb = 0;
	max_ilosc_boh = 0;
	max_ilosc_stwor = 0;
	max_ilosc_skarb = 0;
	sterujaca_kraina = 0;
}


kraina::~kraina()
{
	bohater.clear();
	potwor.clear();
	skarb.clear();
}

void kraina::setKraina(checked & kr, checked & kr2)
{
	if (sterujaca_kraina == 0)
	{
		ilosc_boh = 0;
		ilosc_stwor = 0;
		ilosc_skarb = 0;
		img = kr;
		max_ilosc_boh = kr.ilosc_boh;
		max_ilosc_skarb = kr.ilosc_skarb;
		max_ilosc_stwor = kr.ilosc_stwor;
		ability = kr.ability;
		first_place = kr.first_place;
		second_place = kr.second_place;
		third_place = kr.third_place;
		sterujaca_kraina = 1;
	}
	else
	{
		ilosc_boh = 0;
		ilosc_stwor = 0;
		ilosc_skarb = 0;
		img = kr2;
		max_ilosc_boh = kr2.ilosc_boh;
		max_ilosc_skarb = kr2.ilosc_skarb;
		max_ilosc_stwor = kr2.ilosc_stwor;
		ability = kr2.ability;
		first_place = kr2.first_place;
		second_place = kr2.second_place;
		third_place = kr2.third_place;
		sterujaca_kraina = 0;
	}
}