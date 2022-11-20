#pragma once
#include <SFML/Graphics.hpp>

class checked: public sf::RectangleShape
{
public:
	checked();
	virtual ~checked();
	void setChecked(int a);
	int getChecked() const;
	void setGame_checked(int a);
	int getGame_checked() const;
	void setPlayer(int a);
	int getPlayer() const;
	friend class background;
	int priorytet;
	int is_mouse;
	int press;
	int back;
	int click;
	friend class kraina;

	int drukuj_ksztalt;
	int kliknieto_bohatera;
	int przesunieto_bohatera;
	int kliknieto_potwora;
	int przesunieto_potwora;
	friend class game;

private:
	int checked_on;
	int game_checked;
	int player;
	int player_id;

	int sila;
	int ability;
	int pkt;
	int noc;

	int first_place;
	int second_place;
	int third_place;
	int ilosc_boh;
	int ilosc_stwor;
	int ilosc_skarb;

};

