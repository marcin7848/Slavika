#pragma once
#include "controller_window.h"
#include <queue>
#include "player.h"
#include "kraina.h"
#include <thread>

class game
{

public:
	game();
	~game();
	void set_game(background &TLO, controller_window & Window, sf::Vector2f& worldPos);
	void Drukuj(sf::RenderWindow * app, background &TLO);
	void Event_scan(sf::RenderWindow* app, background &TLO, sf::Event Event, sf::Vector2f worldPos);
	friend class mainEvent;

private:
	int ilosc_graczy;
	int ilosc_human;
	int ilosc_krain;
	int scale_div;
	void Create_Deck(background *TLO);
	checked *talia;
	checked *tmp;
	bool Rand_check(int liczba, int tab[], int ile);
	int Rand(int max);
	queue < checked > deck;
	checked *skarby;
	checked *tmp2;
	void Create_Skarby(background *TLO);
	queue < checked > skarb;
	player *player1;
	void setPlayer(background &TLO);
	int *tab_human;
	int *tab_comp;
	int tab_human_ilosc;
	int tab_comp_ilosc;
	sf::String *names;
	void SetPlayer_Skin(background &TLO, int n, sf::String &name);

	checked proba;

	float stand_x;
	float stand_y;
	checked draw_vip;
	int is_draw_vip;
	int is_mouse;
	sf::Vector2f tmp_pos;

	void Set_Potwor(int pos, background &TLO);

	kraina *krainy;
	void setKrainy(background &TLO);
	checked* tyl_skarb;

	int kliknieto_bohatera;
	int kliknieto_potwora;
	void click_boh(player &players);
	void draw_players(sf::RenderWindow* app, player &players);
	void draw_krainy(sf::RenderWindow* app, kraina &krains);
	void setKrainy2(background &TLO, kraina &krainy, int only_setpos = 0);
	void is_mouse_Exist();
	int is_mouse_def(kraina &krainy);
	int is_mouse_def(player &players);
	void Event_Player(background &TLO, player &players, sf::Vector2f worldPos, int player_idd, int actual_id_player);
	void Event_Krainy(background &TLO, kraina &krains, sf::Vector2f worldPos);

	void dynamic_position(checked obrazek, sf::Vector2f pkt1, sf::Vector2f pkt2);
	int dynamic_pos_drukuj;
	checked dynamic_pos_ob;

	int pomoc_active;

	int player_id;
	int draw_accept;
	int tura_pos;

	int ilosc_boh_do_wstawienia;
	int ilosc_pot_do_wstawienia;
	int pick_boh;
	int pick_pot;
	void set_tura_pos(int a);

	int walka;
	int ilosc_nocy;
	void changeKrainy(background & TLO, int id_kraina);
	int koniec;

};

