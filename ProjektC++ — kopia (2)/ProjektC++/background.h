#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Windows.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "checked.h"
#include <chrono>

using namespace std;

#define CONFIG "config.txt"
#define TLO1 "img/background.png"
#define TLO2 "img/slavika.png"
#define TLO3 "img/background1.png"
#define BUTTON "img/button.png"
#define CHECKBOX_CHECKED "img/checkbox_checked.png"
#define CHECKBOX_NOCHECKED "img/checkbox_nochecked.png"

#define SZARY_TYL "img/players/szary_tyl.png"
#define NIEBIESKI_TYL "img/players/niebieski_tyl.png"
#define ROZOWY_TYL "img/players/rozowy_tyl.png"
#define ZIELONY_TYL "img/players/zielony_tyl.png"

#define SZARY_1 "img/players/szary1.png"
#define SZARY_2 "img/players/szary2.png"
#define SZARY_3 "img/players/szary3.png"
#define SZARY_4 "img/players/szary4.png"
#define SZARY_5 "img/players/szary5.png"
#define SZARY_6 "img/players/szary6.png"

#define NIEBIESKI_1 "img/players/niebieski1.png"
#define NIEBIESKI_2 "img/players/niebieski2.png"
#define NIEBIESKI_3 "img/players/niebieski3.png"
#define NIEBIESKI_4 "img/players/niebieski4.png"
#define NIEBIESKI_5 "img/players/niebieski5.png"
#define NIEBIESKI_6 "img/players/niebieski6.png"

#define ROZOWY_1 "img/players/rozowy1.png"
#define ROZOWY_2 "img/players/rozowy2.png"
#define ROZOWY_3 "img/players/rozowy3.png"
#define ROZOWY_4 "img/players/rozowy4.png"
#define ROZOWY_5 "img/players/rozowy5.png"
#define ROZOWY_6 "img/players/rozowy6.png"

#define ZIELONY_1 "img/players/zielony1.png"
#define ZIELONY_2 "img/players/zielony2.png"
#define ZIELONY_3 "img/players/zielony3.png"
#define ZIELONY_4 "img/players/zielony4.png"
#define ZIELONY_5 "img/players/zielony5.png"
#define ZIELONY_6 "img/players/zielony6.png"

#define STWOR_TYL "img/potwory/stwor_tyl.png"
#define STWOR_1 "img/potwory/stwor1.png"
#define STWOR_2 "img/potwory/stwor2.png"
#define STWOR_3 "img/potwory/stwor3.png"
#define STWOR_4 "img/potwory/stwor4.png"
#define STWOR_5 "img/potwory/stwor5.png"
#define STWOR_6 "img/potwory/stwor6.png"
#define STWOR_7 "img/potwory/stwor7.png"
#define STWOR_8 "img/potwory/stwor8.png"
#define STWOR_9 "img/potwory/stwor9.png"
#define STWOR_10 "img/potwory/stwor10.png"
#define STWOR_11 "img/potwory/stwor11.png"
#define STWOR_12 "img/potwory/stwor12.png"
#define STWOR_13 "img/potwory/stwor13.png"

#define NOC_1 "img/skarby/noc1.png"
#define NOC_2 "img/skarby/noc2.png"
#define NOC_3 "img/skarby/noc3.png"
#define NOC_4 "img/skarby/noc4.png"
#define NOC_5 "img/skarby/noc5.png"

#define SKARB_TYL "img/skarby/skarb_tyl.png"
#define SKARB_2 "img/skarby/skarb2.png"
#define SKARB_3 "img/skarby/skarb3.png"
#define SKARB_4 "img/skarby/skarb4.png"

#define KRAINA_1 "img/krainy/kraina1.png"
#define KRAINA_2 "img/krainy/kraina2.png"
#define KRAINA_3 "img/krainy/kraina3.png"
#define KRAINA_4 "img/krainy/kraina4.png"
#define KRAINA_5 "img/krainy/kraina5.png"
#define KRAINA_6 "img/krainy/kraina6.png"
#define KRAINA_7 "img/krainy/kraina7.png"
#define KRAINA_8 "img/krainy/kraina8.png"
#define KRAINA_9 "img/krainy/kraina9.png"
#define KRAINA_10 "img/krainy/kraina10.png"
#define KRAINA_11 "img/krainy/kraina11.png"
#define KRAINA_12 "img/krainy/kraina12.png"

class background
{
private:
	sf::RenderWindow window;
	int stand_x_tlo;
	int stand_y_tlo;
	int stand_x_kr;
	int stand_y_kr;
	int window_x;
	int window_y;
	ifstream plik;
	string text;
	string text2;
	string line;
	string line2;
	ofstream plik2;

public:
	background();
	virtual ~background();
	int load_page();
	int mutex;
	sf::Text start;
	sf::Texture* tekstura;
	void tlo_glowne(sf::RenderWindow* app);
	void wyjscie();
	void settings();
	void game_setup();
	void game();
	int get_Window_xy();
	sf::RenderWindow& setWindow();
	checked *obrazek;
	sf::RectangleShape *ksztalt;
	sf::Font *font;
	sf::Text *tekst;
	int window_x_return() const;
	int window_y_return() const;
	int f, m;
	void Show_Message(sf::RenderWindow* app);
	void Set_Message(sf::Vector2f& worldPos,  sf::String tekst);
	sf::Text message;
	sf::RectangleShape message_board;
	int reset_showmsg;
	chrono::steady_clock::time_point timer_start;
	chrono::steady_clock::time_point timer_end;
	void Timer();
	int timer_started;
	void dopasuj(checked &obraz, sf::Text &text, float sterowane_x, float sterowane_y, float ograniczenie_x, float ograniczenie_y);
	void dopasuj(checked &obraz, checked &dopasuj_obraz, float sterowane_x, float sterowane_y, float ograniczenie_x, float ograniczenie_ys);
	void dopasuj(checked &obraz, checked &dopasuj_obraz);

	checked *szary;
	checked *niebieski;
	checked *rozowy;
	checked *zielony;
	void set_Players_Skin();

	checked *stwor;
	void set_Stwor_Skin();

	checked *skarb;
	void set_Skarb_Skin();

	checked *kraina;
	void set_Kraina_Skin();

	sf::Text *game_text;
	checked *game_obrazek;
	sf::String pomoc_text;

	checked msg_img;
	sf::Text msg;
	void set_msg(sf::Vector2f& worldPos, sf::String tekst);

};

