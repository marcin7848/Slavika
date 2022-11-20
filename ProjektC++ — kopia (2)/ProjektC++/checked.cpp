#include "checked.h"



checked::checked()
{
	checked_on = 0;
	game_checked = 0;
	player = 1; 
	priorytet = 0;
	is_mouse = 0;
	press = 0;
	back = 0;
	click = 0;
	drukuj_ksztalt = 0;
	przesunieto_bohatera = 0;
	przesunieto_potwora = 0;
	player_id = -1;
}


checked::~checked()
{
}

void checked::setChecked(int a)
{
	checked_on = a;
}

int checked::getChecked() const
{
	return checked_on;
}

void checked::setGame_checked(int a)
{
	game_checked = a;
}

int checked::getGame_checked() const
{
	return game_checked;
}
void checked::setPlayer(int a)
{
	player = a;
}

int checked::getPlayer() const
{
	return player;
}
