#include "background.h"

background::background()
{
	font = new sf::Font[2];

	if (!(font[0].loadFromFile("arial.ttf")))
	{
		MessageBox(NULL, "Nie mozna zaladowac czcionki arial!", "ERROR", NULL);
		exit(0);
	}
	if (!(font[1].loadFromFile("kust.ttf")))
	{
		MessageBox(NULL, "Nie mozna zaladowac czcionki kust!", "ERROR", NULL);
		exit(0);
	}

	start.setFont(font[0]);
	start.setString(L"Trwa ³adowanie gry. Proszê czekaæ!");
	start.setCharacterSize(20);
	start.setPosition(40,30);
	start.setFillColor(sf::Color::Black);

	window_x = 1360;
	window_y = 768;

	obrazek = new checked[20];
	ksztalt = new sf::RectangleShape[4];
	tekst = new sf::Text[22];
	tekstura = new sf::Texture[69];

	szary = new checked[6];
	niebieski = new checked[6];
	rozowy = new checked[6];
	zielony = new checked[6];

	stwor = new checked[13];
	skarb = new checked[8];
	kraina = new checked[12];

	game_obrazek = new checked[17];
	game_text = new sf::Text[21];
}


background::~background()
{
	delete[] obrazek;
	delete[] ksztalt;
	delete[] font;
	delete[] tekst;
	delete[] tekstura;
	delete[] szary;
	delete[] niebieski;
	delete[] rozowy;
	delete[] zielony;
	delete[] stwor;
	delete[] skarb;
	delete[] kraina;
	delete[] game_obrazek;
	delete[] game_text;
}

int background::load_page()
{
	mutex = 0;
	if ((!tekstura[0].loadFromFile(TLO1)) || (!tekstura[1].loadFromFile(TLO2)) || (!tekstura[2].loadFromFile(BUTTON))|| (!tekstura[3].loadFromFile(CHECKBOX_NOCHECKED)) || 
		(!tekstura[4].loadFromFile(CHECKBOX_CHECKED)) || (!tekstura[5].loadFromFile(SZARY_TYL)) || (!tekstura[6].loadFromFile(NIEBIESKI_TYL)) || (!tekstura[7].loadFromFile(ROZOWY_TYL)) || 
		(!tekstura[8].loadFromFile(ZIELONY_TYL)) 
		|| (!tekstura[9].loadFromFile(SZARY_1)) || (!tekstura[10].loadFromFile(SZARY_2)) || (!tekstura[11].loadFromFile(SZARY_3)) || (!tekstura[12].loadFromFile(SZARY_4)) || (!tekstura[13].loadFromFile(SZARY_5)) ||
		(!tekstura[14].loadFromFile(SZARY_6))
		|| (!tekstura[15].loadFromFile(NIEBIESKI_1)) || (!tekstura[16].loadFromFile(NIEBIESKI_2)) || (!tekstura[17].loadFromFile(NIEBIESKI_3)) || (!tekstura[18].loadFromFile(NIEBIESKI_4)) || 
		(!tekstura[19].loadFromFile(NIEBIESKI_5)) || (!tekstura[20].loadFromFile(NIEBIESKI_6))
		|| (!tekstura[21].loadFromFile(ROZOWY_1)) || (!tekstura[22].loadFromFile(ROZOWY_2)) || (!tekstura[23].loadFromFile(ROZOWY_3)) || (!tekstura[24].loadFromFile(ROZOWY_4)) ||
		(!tekstura[25].loadFromFile(ROZOWY_5)) || (!tekstura[26].loadFromFile(ROZOWY_6))
		|| (!tekstura[27].loadFromFile(ZIELONY_1)) || (!tekstura[28].loadFromFile(ZIELONY_2)) || (!tekstura[29].loadFromFile(ZIELONY_3)) || (!tekstura[30].loadFromFile(ZIELONY_4)) ||
		(!tekstura[31].loadFromFile(ZIELONY_5)) || (!tekstura[32].loadFromFile(ZIELONY_6))
		|| (!tekstura[33].loadFromFile(STWOR_TYL)) || (!tekstura[34].loadFromFile(STWOR_1)) || (!tekstura[35].loadFromFile(STWOR_2)) || (!tekstura[36].loadFromFile(STWOR_3)) ||
		(!tekstura[37].loadFromFile(STWOR_4)) || (!tekstura[38].loadFromFile(STWOR_5)) || (!tekstura[39].loadFromFile(STWOR_6)) || (!tekstura[40].loadFromFile(STWOR_7)) ||
		(!tekstura[41].loadFromFile(STWOR_8)) || (!tekstura[42].loadFromFile(STWOR_9)) || (!tekstura[43].loadFromFile(STWOR_10)) || (!tekstura[44].loadFromFile(STWOR_11)) || 
		(!tekstura[45].loadFromFile(STWOR_12)) || (!tekstura[46].loadFromFile(STWOR_13))
		|| (!tekstura[47].loadFromFile(SKARB_TYL)) || (!tekstura[48].loadFromFile(NOC_1)) || (!tekstura[49].loadFromFile(NOC_2)) || (!tekstura[50].loadFromFile(NOC_3)) || (!tekstura[51].loadFromFile(NOC_4)) ||
		(!tekstura[52].loadFromFile(NOC_5)) || (!tekstura[53].loadFromFile(SKARB_2)) || (!tekstura[54].loadFromFile(SKARB_3)) || (!tekstura[55].loadFromFile(SKARB_4))
		|| (!tekstura[56].loadFromFile(KRAINA_1)) || (!tekstura[57].loadFromFile(KRAINA_2)) || (!tekstura[58].loadFromFile(KRAINA_3)) || (!tekstura[59].loadFromFile(KRAINA_4)) || (!tekstura[60].loadFromFile(KRAINA_5)) ||
		(!tekstura[61].loadFromFile(KRAINA_6)) || (!tekstura[62].loadFromFile(KRAINA_7)) || (!tekstura[63].loadFromFile(KRAINA_8)) || (!tekstura[64].loadFromFile(KRAINA_9)) ||
		(!tekstura[65].loadFromFile(KRAINA_10)) || (!tekstura[66].loadFromFile(KRAINA_11)) || (!tekstura[67].loadFromFile(KRAINA_12)) || (!tekstura[68].loadFromFile(TLO3)))
	{
		MessageBox(NULL, "Nie mozna zaladowac grafik!", "ERROR", NULL);
		exit(0);
	}

	mutex = 1;
	return 1;
}

int background::get_Window_xy()
{
	int x = 0, y = 0, a = 0, c = 0, d = 0;
	f = 0;
	m = 0;

	plik.open("config.txt");
	if (!plik.good())
	{
		sf::VideoMode aj;
		x = aj.getDesktopMode().width;
		y = aj.getDesktopMode().height;
		std::ostringstream ss, ss2;
		ss << x;
		ss2 << y;

		plik2.open("config.txt");
		text2 = "Window\t" + ss.str() + "\t" + ss2.str() + "\nMusic\t1\nFullscreen\t1";
		plik2 << text2;

		plik2.close();
	}
	plik.close();


	plik.open("config.txt");
	if (!plik.good())
	{
		MessageBox(NULL, "Nie mozna zaladowac config.txt", "ERROR", NULL);
		exit(0);
	}

	while (getline(plik, line))
	{
		if (line.find("Window") != string::npos)
		{
			std::istringstream inputstringstream(line);
			if (inputstringstream >> text >> x >> y)
			{
				a = 1;
			}
		}
		if (line.find("Fullscreen") != string::npos)
		{
			std::istringstream inputstringstream(line);
			if (inputstringstream >> text >> f)
			{
				c = 1;
			}
		}
		if (line.find("Music") != string::npos)
		{
			std::istringstream inputstringstream(line);
			if (inputstringstream >> text >> m)
			{
				d = 1;
			}
		}
	}
	if (a == 0 || c == 0 || d == 0)
	{
		MessageBox(NULL, "Blad przy pobieraniu danych z config.txt. Usun go z folderu!", "ERROR", NULL);
		exit(0);
	}
	plik.close();

	int tab[10][2] = { { 800,600 },{ 1024,768 },{ 1280,600 },{ 1280,720 },{ 1280,768 },{ 1280,800 },{ 1360,768 },{ 1366,768 },{ 1440,900 },{ 1600, 900 } };
	for (int i = 0; i < 10; i++)
	{
		if (tab[i][0] == x && tab[i][1] == y)
		{
			window_x = x;
			window_y = y;
		}
	}

	if (f == 1)
	{
		obrazek[16].setChecked(1);
	}

	if (m == 1)
	{
		obrazek[17].setChecked(1);
	}

	for (int i = 0; i < 10; i++)
	{
		if (tab[i][0] == window_x && tab[i][1] == window_y)
		{
			obrazek[i + 6].setChecked(1);
		}
	}

	if ((window_x == 1600 && window_y == 900) || (window_x == 1366 && window_y == 768) || (window_x == 1360 && window_y == 768) || (window_x == 1280 && window_y == 720) || (window_x == 1024 && window_y == 768))
	{
		stand_x_tlo = 28;
		stand_y_tlo = 11;
		stand_x_kr = 7;
		stand_y_kr = 7;
	}

	if ((window_x == 1440 && window_y == 900) || (window_x == 1280 && window_y == 800) || (window_x == 1280 && window_y == 768))
	{
		stand_x_tlo = 25;
		stand_y_tlo = 10;
		stand_x_kr = 7;
		stand_y_kr = 7;
	}

	if (window_x == 1280 && window_y == 600)
	{
		stand_x_tlo = 33;
		stand_y_tlo = 12;
		stand_x_kr = 8;
		stand_y_kr = 8;
	}

	if (window_x == 800 && window_y == 600)
	{
		stand_x_tlo = 22;
		stand_y_tlo = 10;
		stand_x_kr = 7;
		stand_y_kr = 7;
	}
	set_Players_Skin();
	set_Stwor_Skin();
	set_Skarb_Skin();
	set_Kraina_Skin();

	return 1;
}

int background::window_x_return() const
{
	return window_x;
}

int background::window_y_return() const
{
	return window_y;
}

void background::Show_Message(sf::RenderWindow* app)
{
	app->draw(message_board);
	app->draw(message);
}

void background::Set_Message(sf::Vector2f& worldPos, sf::String tekst)
{
	sf::String tekst_all, last_word, tmp;
	message.setFont(font[0]);
	message.setCharacterSize(20);
	message.setFillColor(sf::Color::Black);
	message.setStyle(sf::Text::Regular);
	message.setPosition(0.0f, 0.0f);

	for (unsigned int i = 0; i < tekst.getSize(); i++)
	{
		if (tekst[i] != ' ')
		{
			last_word += tekst[i];
		}
		else
		{
			last_word += ' ';
			tmp = tekst_all + last_word;
			message.setString(tmp);

			if (worldPos.x + message.getGlobalBounds().width - window_x < -10)
			{
				tekst_all += last_word;
			}
			else
			{
				tekst_all += "\n" + last_word;
			}
			last_word = "";
		}

	}
	message.setString(tekst_all);
	int j;
	for (j = 10; worldPos.y + message.getGlobalBounds().height - window_y - j > -20; j++){}

	message.setPosition(worldPos.x+10, worldPos.y-j);

	message_board.setSize(sf::Vector2f(message.getGlobalBounds().width+3, message.getGlobalBounds().height+10));
	message_board.setFillColor(sf::Color(255, 255, 255, 255));
	message_board.setOutlineColor(sf::Color::Black);
	message_board.setOutlineThickness(2.0f);
	message_board.setPosition(sf::Vector2f(message.getPosition().x-3, message.getPosition().y-3));


}

void background::set_msg(sf::Vector2f& worldPos, sf::String tekst)
{
	sf::String tekst_all, last_word, tmp;

	msg.setFont(font[0]);
	msg.setCharacterSize(15);
	msg.setFillColor(sf::Color::Black);
	msg.setStyle(sf::Text::Regular);
	msg.setPosition(0.0f, 0.0f);

	for (unsigned int i = 0; i < tekst.getSize(); i++)
	{
		if (tekst[i] != ' ')
		{
			last_word += tekst[i];
		}
		else
		{
			last_word += ' ';
			tmp = tekst_all + last_word;
			msg.setString(tmp);

			if (worldPos.x + msg.getGlobalBounds().width - window_x + game_obrazek[0].getGlobalBounds().width + game_obrazek[12].getGlobalBounds().width< -10)
			{
				tekst_all += last_word;
			}
			else
			{
				tekst_all += "\n" + last_word;
			}
			last_word = "";
		}

	}
	tekst_all += last_word;
	msg.setString(tekst_all);
	int j;
	for (j = 10; worldPos.y + msg.getGlobalBounds().height - window_y - j > -20; j++) {}

	msg.setPosition(worldPos.x + 10, worldPos.y - j);

	msg_img.setSize(sf::Vector2f(msg.getGlobalBounds().width + 3, msg.getGlobalBounds().height + 10));
	msg_img.setFillColor(sf::Color(255, 255, 255, 255));
	msg_img.setOutlineColor(sf::Color::Black);
	msg_img.setOutlineThickness(2.0f);
	msg_img.setPosition(sf::Vector2f(msg.getPosition().x - 3, msg.getPosition().y - 3));


}

void background::Timer()
{
	while(std::chrono::duration_cast<std::chrono::seconds>(timer_end - timer_start).count() < 4 && reset_showmsg == 1)
	{
		timer_end = chrono::steady_clock::now();
	}

	reset_showmsg = 0;
	timer_started = 0;
	message.setString("");
	message_board.setSize(sf::Vector2f(0, 0));
	
}

void background::dopasuj(checked &obraz, sf::Text &text, float sterowane_x, float sterowane_y, float ograniczenie_x, float ograniczenie_y)
{
	int size_text = 0;
	float x, y;

	do
	{
		text.setCharacterSize(size_text);
		size_text++;
	} while ((text.getGlobalBounds().width < obraz.getGlobalBounds().width-10 - ograniczenie_x && text.getGlobalBounds().height < obraz.getGlobalBounds().height-10 - ograniczenie_y) && size_text <= 100);

	text.setCharacterSize(size_text-1);

	if (sterowane_x == 0)
		x = obraz.getPosition().x + obraz.getGlobalBounds().width / 2 - text.getGlobalBounds().width / 2 - ograniczenie_x/ 4;
	else
		x = sterowane_x;

	if (sterowane_y == 0)
		y = obraz.getPosition().y + obraz.getGlobalBounds().height / 2 - text.getGlobalBounds().height + ograniczenie_y / 2;
	else
		y = sterowane_y;

	text.setPosition(sf::Vector2f(x, y));
}

void background::dopasuj(checked &obraz, checked &dopasuj_obraz, float sterowane_x, float sterowane_y, float ograniczenie_x, float ograniczenie_y)
{
	float scale = 0.0f;
	float x, y;

	do
	{
		dopasuj_obraz.setScale(sf::Vector2f(scale, scale));
		scale += 0.01f;
		
	} while (dopasuj_obraz.getGlobalBounds().width < obraz.getGlobalBounds().width - 10 - ograniczenie_x && dopasuj_obraz.getGlobalBounds().height < obraz.getGlobalBounds().height - 10 - ograniczenie_y);

	dopasuj_obraz.setScale(sf::Vector2f(scale-0.01f, scale-0.01f));

	if (sterowane_x == 0)
		x = obraz.getPosition().x + obraz.getGlobalBounds().width / 2.0f - dopasuj_obraz.getGlobalBounds().width / 2.0f ;
	else
		x = sterowane_x;
	if (sterowane_y == 0)
		y = obraz.getPosition().y + obraz.getGlobalBounds().height / 2 - dopasuj_obraz.getGlobalBounds().height + ograniczenie_y;
	else
		y = sterowane_y;

	dopasuj_obraz.setPosition(sf::Vector2f(x, y));
}

void background::dopasuj(checked &obraz, checked &dopasuj_obraz)
{
	while (obraz.getPosition().x>dopasuj_obraz.getPosition().x)
	{
		dopasuj_obraz.setPosition(sf::Vector2f(dopasuj_obraz.getPosition().x+1.0f, dopasuj_obraz.getPosition().y));
	}
	while (obraz.getPosition().y>dopasuj_obraz.getPosition().y)
	{
		dopasuj_obraz.setPosition(sf::Vector2f(dopasuj_obraz.getPosition().x, dopasuj_obraz.getPosition().y+1.0f));
	}
	while (obraz.getPosition().x + obraz.getGlobalBounds().width < dopasuj_obraz.getPosition().x + dopasuj_obraz.getGlobalBounds().width)
	{
		dopasuj_obraz.setPosition(sf::Vector2f(dopasuj_obraz.getPosition().x-1.0f, dopasuj_obraz.getPosition().y));
	}
	while (obraz.getPosition().y + obraz.getGlobalBounds().height < dopasuj_obraz.getPosition().y + dopasuj_obraz.getGlobalBounds().height)
	{
		dopasuj_obraz.setPosition(sf::Vector2f(dopasuj_obraz.getPosition().x, dopasuj_obraz.getPosition().y-1.0f));
	}
}

void background::set_Players_Skin()
{
	for (int i = 0; i <= 5; i++)
	{
		szary[i].sila = i + 1;
		niebieski[i].sila = i + 1;
		rozowy[i].sila = i + 1;
		zielony[i].sila = i + 1;
		//if (i != 5)
		//{
			szary[i].ability = i + 1;
			niebieski[i].ability = i + 1;
			rozowy[i].ability = i + 1;
			zielony[i].ability = i + 1;
		//}
		//else
		//{
		//	szary[i].ability = 0;
		//	niebieski[i].ability = 0;
		//	rozowy[i].ability = 0;
		//	zielony[i].ability = 0;
		//}
	}

	for(int i = 0, j = 9; i <= 5; i++, j++)
	{
		szary[i].setSize(sf::Vector2f(float(window_x / stand_x_tlo), float(window_y / stand_y_tlo)));
		szary[i].setPosition(0.0f, 0.0f);
		szary[i].setTexture(&tekstura[j], true);
	}

	for (int i = 0, j = 15; i <= 5; i++, j++)
	{
		niebieski[i].setSize(sf::Vector2f(float(window_x / stand_x_tlo), float(window_y / stand_y_tlo)));
		niebieski[i].setPosition(0.0f, 0.0f);
		niebieski[i].setTexture(&tekstura[j], true);
	}

	for (int i = 0, j = 21; i <= 5; i++, j++)
	{
		rozowy[i].setSize(sf::Vector2f(float(window_x / stand_x_tlo), float(window_y / stand_y_tlo)));
		rozowy[i].setPosition(0.0f, 0.0f);
		rozowy[i].setTexture(&tekstura[j], true);
	}

	for (int i = 0, j = 27; i <= 5; i++, j++)
	{
		zielony[i].setSize(sf::Vector2f(float(window_x / stand_x_tlo), float(window_y / stand_y_tlo)));
		zielony[i].setPosition(0.0f, 0.0f);
		zielony[i].setTexture(&tekstura[j], true);
	}
}

void background::set_Stwor_Skin()
{
	for (int i = 0; i <= 6; i++)
	{
		stwor[i].sila = i+1;
		stwor[i].ability = 0;
		stwor[i].pkt = 0;
	}
	stwor[4].pkt = 1;
	stwor[5].pkt = 2;
	stwor[6].pkt = 3;

	for (int i = 7, j=5; i <= 12; i++, j++)
	{
		stwor[i].sila = 0;
		stwor[i].ability = j;
		stwor[i].pkt = 0;
	}

	for (int i = 0, j = 34 ; i <= 12; i++, j++)
	{
		stwor[i].setSize(sf::Vector2f(float(window_x / stand_x_tlo), float(window_y / stand_y_tlo)));
		stwor[i].setPosition(0.0f, 0.0f);
		stwor[i].setTexture(&tekstura[j], true);
	}

}

void background::set_Skarb_Skin()
{
	for (int i = 0; i <= 4; i++)
	{
		skarb[i].pkt = 0;
		skarb[i].noc = 1;
	}

	skarb[5].pkt = 2;
	skarb[5].noc = 0;

	skarb[6].pkt = 2;
	skarb[6].noc = 0;

	skarb[7].pkt = 2;
	skarb[7].noc = 0;

	for (int i = 0, j = 48; i <= 7; i++, j++)
	{
		skarb[i].setSize(sf::Vector2f(float(window_x / stand_x_kr), float(window_y / stand_y_kr)));
		skarb[i].setPosition(0.0f, 0.0f);
		skarb[i].setTexture(&tekstura[j], true);
	}

}

void background::set_Kraina_Skin()
{
	kraina[0].ability = 0;
	kraina[0].ilosc_boh = 3;
	kraina[0].ilosc_skarb = 1;
	kraina[0].ilosc_stwor = 3;
	kraina[0].first_place = 7;
	kraina[0].second_place = 4;
	kraina[0].third_place = 0;

	kraina[1].ability = 11;
	kraina[1].ilosc_boh = 3;
	kraina[1].ilosc_skarb = 1;
	kraina[1].ilosc_stwor = 3;
	kraina[1].first_place = 8;
	kraina[1].second_place = 4;
	kraina[1].third_place = 0;

	kraina[2].ability = 0;
	kraina[2].ilosc_boh = 4;
	kraina[2].ilosc_skarb = 2;
	kraina[2].ilosc_stwor = 5;
	kraina[2].first_place = 19;
	kraina[2].second_place = 13;
	kraina[2].third_place = 5;

	kraina[3].ability = 0;
	kraina[3].ilosc_boh = 4;
	kraina[3].ilosc_skarb = 1;
	kraina[3].ilosc_stwor = 5;
	kraina[3].first_place = 18;
	kraina[3].second_place = 11;
	kraina[3].third_place = 6;

	kraina[4].ability = 12;
	kraina[4].ilosc_boh = 4;
	kraina[4].ilosc_skarb = 1;
	kraina[4].ilosc_stwor = 3;
	kraina[4].first_place = 6;
	kraina[4].second_place = 3;
	kraina[4].third_place = 0;

	kraina[5].ability = 0;
	kraina[5].ilosc_boh = 4;
	kraina[5].ilosc_skarb = 1;
	kraina[5].ilosc_stwor = 3;
	kraina[5].first_place = 5;
	kraina[5].second_place = 3;
	kraina[5].third_place = 0;
	
	kraina[6].ability = 13;
	kraina[6].ilosc_boh = 3;
	kraina[6].ilosc_skarb = 1;
	kraina[6].ilosc_stwor = 4;
	kraina[6].first_place = 11;
	kraina[6].second_place = 6;
	kraina[6].third_place = 3;

	kraina[7].ability = 0;
	kraina[7].ilosc_boh = 3;
	kraina[7].ilosc_skarb = 1;
	kraina[7].ilosc_stwor = 4;
	kraina[7].first_place = 10;
	kraina[7].second_place = 6;
	kraina[7].third_place = 2;

	kraina[8].ability = 0;
	kraina[8].ilosc_boh = 4;
	kraina[8].ilosc_skarb = 1;
	kraina[8].ilosc_stwor = 4;
	kraina[8].first_place = 10;
	kraina[8].second_place = 6;
	kraina[8].third_place = 2;

	kraina[9].ability = 13;
	kraina[9].ilosc_boh = 4;
	kraina[9].ilosc_skarb = 1;
	kraina[9].ilosc_stwor = 4;
	kraina[9].first_place = 11;
	kraina[9].second_place = 6;
	kraina[9].third_place = 3;

	kraina[10].ability = 0;
	kraina[10].ilosc_boh = 5;
	kraina[10].ilosc_skarb = 1;
	kraina[10].ilosc_stwor = 5;
	kraina[10].first_place = 13;
	kraina[10].second_place = 9;
	kraina[10].third_place = 5;

	kraina[11].ability = 0;
	kraina[11].ilosc_boh = 5;
	kraina[11].ilosc_skarb = 1;
	kraina[11].ilosc_stwor = 5;
	kraina[11].first_place = 13;
	kraina[11].second_place = 10;
	kraina[11].third_place = 4;

	for (int i = 0, j = 56; i <= 11; i++, j++)
	{
		kraina[i].setSize(sf::Vector2f(float(window_x / stand_x_kr), float(window_y / stand_y_kr)));
		kraina[i].setPosition(0.0f, 0.0f);
		kraina[i].setTexture(&tekstura[j], true);
	}

}

sf::RenderWindow & background::setWindow()
{
	get_Window_xy();
	if (obrazek[16].getChecked() == 0)
	{
		window.create(sf::VideoMode(window_x, window_y, 32), "Snake - Marcin Kaczor");
	}
	else
	{
		window.create(sf::VideoMode(window_x, window_y, 32), "Snake - Marcin Kaczor", sf::Style::Fullscreen);
	}
	return window;
}

void background::tlo_glowne(sf::RenderWindow* app)
{

	obrazek[0].setSize(sf::Vector2f(float(window_x), float(window_y)));
	obrazek[0].setPosition(0, 0);
	obrazek[0].setTexture(&tekstura[0], true);
	obrazek[0].setFillColor(sf::Color(255, 255, 255, 255));

	obrazek[1].setSize(sf::Vector2f(float(window_x*0.5), float(window_y*0.95)));
	obrazek[1].setTexture(&tekstura[1], true);
	obrazek[1].setRotation(-30);
	obrazek[1].setPosition(sf::Vector2f(float(window_x / 2 - obrazek[1].getSize().x*1.2), float(window_y / 2 - obrazek[1].getSize().y / 7)));
	obrazek[1].setFillColor(sf::Color(255, 255, 255, 255));

	obrazek[2].setSize(sf::Vector2f(float(window_x/4), float(window_y/7)));
	obrazek[2].setPosition(float(window_x - window_x / 2.6), float(window_y-window_y/1.5));
	obrazek[2].setTexture(&tekstura[2], true);
	obrazek[2].setFillColor(sf::Color(255, 255, 255, 255));

	for (int i = 3; i <= 5; i++)
	{
		obrazek[i] = obrazek[2];
		obrazek[i].setPosition(float(window_x - window_x / 2.6), float(obrazek[i-1].getPosition().y + obrazek[i-1].getGlobalBounds().height + 5));
	}

	int rozm = 45, rozm1 = 150;
	if (window_x <= 1024)
	{
		rozm = 35;
		rozm1 = 100;
	}

	tekst[0].setFont(font[1]);
	tekst[0].setString("SLAVIKA");
	tekst[0].setCharacterSize(rozm1);
	tekst[0].setPosition(0.0f, 0.0f);
	tekst[0].setStyle(sf::Text::Regular);
	tekst[0].setPosition(float(window_x - window_x / 2.3), 0);
	tekst[0].setFillColor(sf::Color(8, 37, 103));

	tekst[1].setString("Graj");
	//tekst[2].setString("Wczytaj");
	tekst[2].setString("Ustawienia");
	tekst[3].setString("Wyjscie");

	for (int i = 1; i <= 3; i++)
	{
		tekst[i].setFont(font[0]);
		tekst[i].setCharacterSize(rozm);
		tekst[i].setFillColor(sf::Color(8, 37, 103));
		tekst[i].setStyle(sf::Text::Regular);
		tekst[i].setPosition(0.0f, 0.0f);
		tekst[i].setPosition(obrazek[i+1].getPosition().x + obrazek[i+1].getGlobalBounds().width / 2 - tekst[i].getGlobalBounds().width / 2 - tekst[i].getGlobalBounds().left, obrazek[i+1].getPosition().y + obrazek[i+1].getGlobalBounds().height / 2 - tekst[i].getGlobalBounds().height / 2 - tekst[i].getGlobalBounds().top);
	}
}

 void background::wyjscie()
{
	ksztalt[0].setSize(sf::Vector2f(2000, 1000));
	ksztalt[0].setFillColor(sf::Color(0, 0, 0, 150));
	ksztalt[0].setScale(sf::Vector2f(float(window_x), float(window_y)));

	ksztalt[1].setSize(sf::Vector2f(600, 200));
	ksztalt[1].setFillColor(sf::Color(255, 255, 255, 255));
	ksztalt[1].setPosition(sf::Vector2f(window_x /2- ksztalt[1].getSize().x/2, window_y /2- ksztalt[1].getSize().y / 2));
	ksztalt[1].setOutlineColor(sf::Color::Blue);
	ksztalt[1].setOutlineThickness(4.0f);

	ksztalt[2].setSize(sf::Vector2f(200, 40));
	ksztalt[2].setFillColor(sf::Color(255, 255, 255, 255));
	ksztalt[2].setOutlineColor(sf::Color::Black);
	ksztalt[2].setOutlineThickness(2.0f);
	ksztalt[2].setPosition(sf::Vector2f(ksztalt[1].getPosition().x + ksztalt[1].getGlobalBounds().width/4.0f - ksztalt[2].getGlobalBounds().width/2.0f, ksztalt[1].getPosition().y + ksztalt[1].getGlobalBounds().height/1.5f));

	ksztalt[3].setSize(sf::Vector2f(200, 40));
	ksztalt[3].setFillColor(sf::Color(255, 255, 255, 255));
	ksztalt[3].setOutlineColor(sf::Color::Black);
	ksztalt[3].setOutlineThickness(2.0f);
	ksztalt[3].setPosition(sf::Vector2f(ksztalt[1].getPosition().x + ksztalt[1].getGlobalBounds().width*0.75f - ksztalt[2].getGlobalBounds().width / 2.0f, ksztalt[1].getPosition().y + ksztalt[1].getGlobalBounds().height / 1.5f));
	
	tekst[5].setFont(font[0]);
	tekst[5].setString("Czy na pewno chcesz wyjsc z gry?");
	tekst[5].setCharacterSize(30);
	tekst[5].setFillColor(sf::Color::Black);
	tekst[5].setStyle(sf::Text::Regular);
	tekst[5].setPosition(0.0f, 0.0f);
	tekst[5].setPosition(ksztalt[1].getPosition().x + ksztalt[1].getGlobalBounds().width / 2 - tekst[5].getGlobalBounds().width / 2 - tekst[5].getGlobalBounds().left, ksztalt[1].getPosition().y + ksztalt[1].getGlobalBounds().height / 3 - tekst[5].getGlobalBounds().height / 2 - tekst[5].getGlobalBounds().top);


	tekst[6].setFont(font[0]);
	tekst[6].setString("Tak");
	tekst[6].setCharacterSize(20);
	tekst[6].setStyle(sf::Text::Regular);
	tekst[6].setFillColor(sf::Color::Black);
	tekst[6].setPosition(0.0f, 0.0f);
	tekst[6].setPosition(ksztalt[2].getPosition().x + ksztalt[2].getGlobalBounds().width / 2 - tekst[6].getGlobalBounds().width / 2 - tekst[6].getGlobalBounds().left, ksztalt[2].getPosition().y + ksztalt[2].getGlobalBounds().height / 2 - tekst[6].getGlobalBounds().height / 2 - tekst[6].getGlobalBounds().top);

	tekst[7].setFont(font[0]);
	tekst[7].setString("Nie");
	tekst[7].setStyle(sf::Text::Regular);
	tekst[7].setCharacterSize(20);
	tekst[7].setFillColor(sf::Color::Black);
	tekst[7].setPosition(0.0f, 0.0f);
	tekst[7].setPosition(ksztalt[3].getPosition().x + ksztalt[3].getGlobalBounds().width / 2 - tekst[7].getGlobalBounds().width / 2 - tekst[7].getGlobalBounds().left, ksztalt[3].getPosition().y + ksztalt[3].getGlobalBounds().height / 2 - tekst[7].getGlobalBounds().height / 2 - tekst[7].getGlobalBounds().top);

}

void background::settings()
{
	ksztalt[0].setSize(sf::Vector2f(2000, 1000));
	ksztalt[0].setFillColor(sf::Color(0, 0, 0, 150));
	ksztalt[0].setScale(sf::Vector2f(float(window_x), float(window_y)));

	ksztalt[1].setSize(sf::Vector2f(400, 500));
	ksztalt[1].setFillColor(sf::Color(255, 255, 255, 255));
	ksztalt[1].setPosition(sf::Vector2f(window_x / 2 - ksztalt[1].getSize().x / 2, window_y / 2 - ksztalt[1].getSize().y / 2));
	ksztalt[1].setOutlineColor(sf::Color::Blue);
	ksztalt[1].setOutlineThickness(4.0f);

	obrazek[6].setSize(sf::Vector2f(20, 20));
	obrazek[6].setPosition(ksztalt[1].getPosition().x+10, ksztalt[1].getPosition().y+80);
	obrazek[6].setTexture(&tekstura[3]);
	obrazek[6].setFillColor(sf::Color(255, 255, 255, 255));

	for (int i = 7; i <= 15; i++)
	{
		obrazek[i].setSize(sf::Vector2f(20, 20));
		obrazek[i].setTexture(&tekstura[3]);
		obrazek[i].setPosition(ksztalt[1].getPosition().x + 10, obrazek[i-1].getPosition().y + obrazek[i-1].getGlobalBounds().height + 3);
		obrazek[i].setFillColor(sf::Color(255,255,255,255));
	}


	tekst[5].setFont(font[0]);
	tekst[5].setString("Ustawienia");
	tekst[5].setCharacterSize(30);
	tekst[5].setFillColor(sf::Color::Black);
	tekst[5].setStyle(sf::Text::Regular);
	tekst[5].setPosition(0.0f, 0.0f);
	tekst[5].setPosition(ksztalt[1].getPosition().x + ksztalt[1].getGlobalBounds().width / 2 - tekst[5].getGlobalBounds().width / 2 - tekst[5].getGlobalBounds().left, ksztalt[1].getPosition().y + tekst[5].getGlobalBounds().height / 2);

	tekst[6].setFont(font[0]);
	tekst[6].setString(L"Ustawienia rozdzielcznoœci");
	tekst[6].setCharacterSize(20);
	tekst[6].setFillColor(sf::Color::Black);
	tekst[6].setStyle(sf::Text::Regular);
	tekst[6].setPosition(0.0f, 0.0f);
	tekst[6].setPosition(ksztalt[1].getPosition().x + 10, tekst[5].getPosition().y + tekst[5].getGlobalBounds().height + 15);

	tekst[7].setFont(font[0]);
	tekst[7].setString("800x600");
	tekst[7].setCharacterSize(15);
	tekst[7].setFillColor(sf::Color::Black);
	tekst[7].setStyle(sf::Text::Regular);
	tekst[7].setPosition(0.0f, 0.0f);
	tekst[7].setPosition(obrazek[6].getPosition().x + obrazek[6].getGlobalBounds().width + 5, obrazek[6].getPosition().y);

	for (int i = 8; i <= 16; i++)
	{
		tekst[i] = tekst[7];
		tekst[i].setPosition(0.0f, 0.0f);
		tekst[i].setPosition(obrazek[i - 1].getPosition().x + obrazek[i - 1].getGlobalBounds().width + 5, obrazek[i - 1].getPosition().y);
	}

	tekst[8].setString("1024x768");
	tekst[9].setString("1280x600");
	tekst[10].setString("1280x720");
	tekst[11].setString("1280x768");
	tekst[12].setString("1280x800");
	tekst[13].setString("1360x768");
	tekst[14].setString("1366x768");
	tekst[15].setString("1440x900");
	tekst[16].setString("1600x900");

	tekst[17].setFont(font[0]);
	tekst[17].setString("Inne ustawienia");
	tekst[17].setCharacterSize(20);
	tekst[17].setFillColor(sf::Color::Black);
	tekst[17].setStyle(sf::Text::Regular);
	tekst[17].setPosition(0.0f, 0.0f);
	tekst[17].setPosition(ksztalt[1].getPosition().x + 10, obrazek[15].getPosition().y+obrazek[15].getGlobalBounds().height+15);


	obrazek[16].setSize(sf::Vector2f(20, 20));
	obrazek[16].setPosition(ksztalt[1].getPosition().x + 10, tekst[17].getPosition().y + tekst[17].getGlobalBounds().height+15);
	obrazek[16].setTexture(&tekstura[3]);
	obrazek[16].setFillColor(sf::Color(255, 255, 255, 255));

	tekst[18].setFont(font[0]);
	tekst[18].setString(L"Pe³ny ekran");
	tekst[18].setCharacterSize(15);
	tekst[18].setFillColor(sf::Color::Black);
	tekst[18].setStyle(sf::Text::Regular);
	tekst[18].setPosition(0.0f, 0.0f);
	tekst[18].setPosition(obrazek[16].getPosition().x + obrazek[16].getGlobalBounds().width + 5, obrazek[16].getPosition().y);


	obrazek[17].setSize(sf::Vector2f(20, 20));
	obrazek[17].setPosition(ksztalt[1].getPosition().x + 10, tekst[18].getPosition().y + tekst[18].getGlobalBounds().height + 15);
	obrazek[17].setTexture(&tekstura[3]);
	obrazek[17].setFillColor(sf::Color(255, 255, 255, 255));

	tekst[19].setFont(font[0]);
	tekst[19].setString(L"Muzyka w³¹czona");
	tekst[19].setCharacterSize(15);
	tekst[19].setFillColor(sf::Color::Black);
	tekst[19].setStyle(sf::Text::Regular);
	tekst[19].setPosition(0.0f, 0.0f);
	tekst[19].setPosition(obrazek[17].getPosition().x + obrazek[17].getGlobalBounds().width + 5, obrazek[17].getPosition().y);

	for (int i = 6; i <= 17; i++)
	{
		if (obrazek[i].getChecked() == 1)
		{
			obrazek[i].setTexture(&tekstura[4]);
		}
	}


	ksztalt[2].setSize(sf::Vector2f(140, 35));
	ksztalt[2].setFillColor(sf::Color(255, 255, 255, 255));
	ksztalt[2].setOutlineColor(sf::Color::Black);
	ksztalt[2].setOutlineThickness(2.0f);
	ksztalt[2].setPosition(sf::Vector2f(ksztalt[1].getPosition().x + ksztalt[1].getGlobalBounds().width / 4.0f - ksztalt[2].getGlobalBounds().width / 2.0f, tekst[19].getPosition().y + tekst[19].getGlobalBounds().height+25));

	ksztalt[3].setSize(sf::Vector2f(140, 35));
	ksztalt[3].setFillColor(sf::Color(255, 255, 255, 255));
	ksztalt[3].setOutlineColor(sf::Color::Black);
	ksztalt[3].setOutlineThickness(2.0f);
	ksztalt[3].setPosition(sf::Vector2f(ksztalt[1].getPosition().x + ksztalt[1].getGlobalBounds().width*0.75f - ksztalt[2].getGlobalBounds().width / 2.0f, tekst[19].getPosition().y + tekst[19].getGlobalBounds().height + 25));

	tekst[20].setFont(font[0]);
	tekst[20].setString("Zapisz");
	tekst[20].setCharacterSize(20);
	tekst[20].setFillColor(sf::Color::Black);
	tekst[20].setStyle(sf::Text::Regular);
	tekst[20].setPosition(0.0f, 0.0f);
	tekst[20].setPosition(ksztalt[2].getPosition().x + ksztalt[2].getGlobalBounds().width / 2 - tekst[20].getGlobalBounds().width / 2 - tekst[20].getGlobalBounds().left, ksztalt[2].getPosition().y + ksztalt[2].getGlobalBounds().height / 2 - tekst[20].getGlobalBounds().height / 2 - tekst[20].getGlobalBounds().top);


	tekst[21].setFont(font[0]);
	tekst[21].setString("Anuluj");
	tekst[21].setCharacterSize(20);
	tekst[21].setFillColor(sf::Color::Black);
	tekst[21].setStyle(sf::Text::Regular);
	tekst[21].setPosition(0.0f, 0.0f);
	tekst[21].setPosition(ksztalt[3].getPosition().x + ksztalt[3].getGlobalBounds().width / 2 - tekst[21].getGlobalBounds().width / 2 - tekst[21].getGlobalBounds().left, ksztalt[3].getPosition().y + ksztalt[3].getGlobalBounds().height / 2 - tekst[21].getGlobalBounds().height / 2 - tekst[21].getGlobalBounds().top);


}

void background::game_setup()
{
	tekst[0].setFont(font[0]);
	tekst[0].setString("Ustawienia gry");
	tekst[0].setCharacterSize(60);
	tekst[0].setFillColor(sf::Color(35,39,50));
	tekst[0].setStyle(sf::Text::Bold);
	tekst[0].setPosition(0.0f, 0.0f);
	tekst[0].setPosition(window_x/2-tekst[0].getGlobalBounds().width/2, 0);

	tekst[1].setFont(font[0]);
	tekst[1].setString("Wybierz graczy");
	tekst[1].setCharacterSize(40);
	tekst[1].setFillColor(sf::Color::Black);
	tekst[1].setStyle(sf::Text::Bold);
	tekst[1].setPosition(0.0f, 0.0f);
	tekst[1].setPosition(window_x / 2 - tekst[1].getGlobalBounds().width / 2, tekst[0].getPosition().y+tekst[0].getGlobalBounds().height+10);

	obrazek[2].setSize(sf::Vector2f(float(window_x / 5.5), float(window_y / 2.5)));
	obrazek[2].setPosition(0.0f, 0.0f);
	obrazek[2].setPosition(window_x/4-obrazek[2].getGlobalBounds().width-30, tekst[1].getPosition().y+tekst[1].getGlobalBounds().height+90);
	obrazek[2].setTexture(&tekstura[5], true);


	for(int i = 3; i <= 5; i++) //wyswietlam grafiki kart graczy, 4 kolory
	{
		obrazek[i].setSize(sf::Vector2f(float(window_x / 5.5), float(window_y / 2.5)));
		obrazek[i].setPosition(0.0f, 0.0f);
		float a = 4;
		if (i == 3) a = 2;
		if (i == 4) a = 3;
		obrazek[i].setPosition(window_x* a / 4 - obrazek[i].getGlobalBounds().width - 30, obrazek[2].getPosition().y);
		obrazek[i].setTexture(&tekstura[i+3], true);
	}
	for (int i = 2; i <= 5; i++)
	{
		if (obrazek[i+4].getGame_checked() == 0) //zaciemniam grafiki kart graczy, jesli nie jest aktywny checkbox AKTYWNY
		{
			obrazek[i].setFillColor(sf::Color(95, 95, 95, 150));
		}
		else
		{
			obrazek[i].setFillColor(sf::Color(255, 255, 255, 255));
		}
	}


	for (int i = 6; i <= 9; i++) //checkboxy - AKTYWNY
	{
		obrazek[i].setSize(sf::Vector2f(window_x / 30.0f, window_x / 30.0f));
		obrazek[i].setPosition(obrazek[i-4].getPosition().x, obrazek[i-4].getPosition().y - obrazek[i].getGlobalBounds().height);
		if (obrazek[i].getGame_checked() == 0) //sprawdzam, czy checkbox aktywny zostal zaznaczony
		{
			obrazek[i].setTexture(&tekstura[3], true);
		}
		else
		{
			obrazek[i].setTexture(&tekstura[4], true);
		}
	}



	for (int i = 2; i <= 5; i++) //wyswietlanie tekstu AKTYWNY
	{
		tekst[i].setFont(font[0]);
		tekst[i].setString("AKTYWNY");
		tekst[i].setCharacterSize(22);
		tekst[i].setFillColor(sf::Color::Black);
		tekst[i].setStyle(sf::Text::Bold);
		tekst[i].setPosition(0.0f, 0.0f);
		tekst[i].setPosition(obrazek[i+4].getPosition().x + obrazek[i+4].getGlobalBounds().width + 5, obrazek[i+4].getPosition().y + obrazek[i+4].getGlobalBounds().height / 2 - tekst[i].getGlobalBounds().height);
	}



	for (int i = 10, j=2, k=6; i <= 16; i = i + 2, j++, k++)
	{
		obrazek[i].setSize(sf::Vector2f(window_x / 30.0f, window_x / 30.0f));
		obrazek[i].setPosition(obrazek[j].getPosition().x, obrazek[j].getPosition().y + obrazek[j].getGlobalBounds().height);
		if (obrazek[i].getPlayer() == 1) //sprawdzam, czy dany kolor ustawiony jest jako gracz, wyswietla odpowiedni checkbox
		{
			obrazek[i].setTexture(&tekstura[4], true);
			obrazek[i + 1].setTexture(&tekstura[3], true);
		}
		else
		{
			obrazek[i].setTexture(&tekstura[3], true);
			obrazek[i + 1].setTexture(&tekstura[4], true);
		}
		obrazek[i+1].setSize(sf::Vector2f(window_x / 30.0f, window_x / 30.0f));
		obrazek[i+1].setPosition(obrazek[j].getPosition().x, obrazek[i].getPosition().y + obrazek[i].getGlobalBounds().height + 5);

		tekst[i-4] = tekst[2];
		tekst[i-4].setPosition(0.0f, 0.0f);
		tekst[i-4].setString("Gracz");
		tekst[i-4].setPosition(obrazek[i].getPosition().x + obrazek[i].getGlobalBounds().width + 5, obrazek[i].getPosition().y + obrazek[i].getGlobalBounds().height / 2 - tekst[i-4].getGlobalBounds().height);

		tekst[i-3] = tekst[2];
		tekst[i-3].setPosition(0.0f, 0.0f);
		tekst[i-3].setString("Komputer");
		tekst[i-3].setPosition(obrazek[i+1].getPosition().x + obrazek[i+1].getGlobalBounds().width + 5, obrazek[i+1].getPosition().y + obrazek[i+1].getGlobalBounds().height / 2 - tekst[i-3].getGlobalBounds().height / 2);

		if (obrazek[k].getGame_checked() == 0) //sprawdzam, czy przy danym kolorze AKTYWNY jest zaznaczone, jesli nie, to przyciemniam gafiki i teksty
		{
			obrazek[i].setFillColor(sf::Color(95, 95, 95, 150));
			obrazek[i+1].setFillColor(sf::Color(95, 95, 95, 150));
			tekst[i-4].setFillColor(sf::Color(95, 95, 95, 150));
			tekst[i-3].setFillColor(sf::Color(95, 95, 95, 150));
		}
		else
		{
			obrazek[i].setFillColor(sf::Color(255,255,255,255));
			obrazek[i+1].setFillColor(sf::Color(255, 255, 255, 255));
			tekst[i-4].setFillColor(sf::Color::Black);
			tekst[i-3].setFillColor(sf::Color::Black);
		}
		obrazek[i].setSize(sf::Vector2f(0,0));
		obrazek[i+1].setSize(sf::Vector2f(0, 0));
		tekst[i - 4].setCharacterSize(0);
		tekst[i - 3].setCharacterSize(0);
	}

	//tekst[14].setFont(font[0]);
	//tekst[14].setString("Czas tury [s]: ");
	//tekst[14].setCharacterSize(22);
	//tekst[14].setFillColor(sf::Color::Black);
	//tekst[14].setStyle(sf::Text::Bold);
	//tekst[14].setPosition(0.0f, 0.0f);
	//tekst[14].setPosition(obrazek[2].getPosition().x, obrazek[11].getPosition().y + obrazek[11].getGlobalBounds().height + 10);
	tekst[14].setCharacterSize(0);
	ksztalt[1].setSize(sf::Vector2f(0, 0));
	//ksztalt[1].setSize(sf::Vector2f(100, tekst[14].getGlobalBounds().height));
	//ksztalt[1].setFillColor(sf::Color(255, 255, 255, 255));
	//ksztalt[1].setPosition(0.0f, 0.0f);
	//ksztalt[1].setPosition(sf::Vector2f(tekst[14].getPosition().x+tekst[14].getGlobalBounds().width+5, tekst[14].getPosition().y+tekst[14].getGlobalBounds().height/2-ksztalt[1].getGlobalBounds().height/2 + 4));
	//ksztalt[1].setOutlineColor(sf::Color::Blue);
	//ksztalt[1].setOutlineThickness(1.0f);

	obrazek[18].setSize(sf::Vector2f(float(window_x / 4), float(window_y / 7)));
	obrazek[18].setPosition(window_x / 2 - obrazek[18].getGlobalBounds().width / 2, window_y - obrazek[18].getGlobalBounds().height - 10);
	obrazek[18].setTexture(&tekstura[2], true);

	int rozm = 45, rozm1 = 35;
	if (window_x <= 1024)
	{
		rozm = 35;
		rozm1 = 20;
	}

	tekst[15].setFont(font[0]);
	tekst[15].setString("Graj");
	tekst[15].setCharacterSize(rozm);
	tekst[15].setFillColor(sf::Color(8, 37, 103));
	tekst[15].setStyle(sf::Text::Regular);
	tekst[15].setPosition(0.0f, 0.0f);
	tekst[15].setPosition(obrazek[18].getPosition().x + obrazek[18].getGlobalBounds().width / 2 - tekst[15].getGlobalBounds().width / 2 - tekst[15].getGlobalBounds().left, obrazek[18].getPosition().y + obrazek[18].getGlobalBounds().height / 2 - tekst[15].getGlobalBounds().height / 2 - tekst[15].getGlobalBounds().top);

	obrazek[19].setSize(sf::Vector2f(float(window_x / 5.5), float(window_y / 8.5)));
	obrazek[19].setPosition(window_x - obrazek[19].getGlobalBounds().width, window_y - obrazek[19].getGlobalBounds().height - 5);
	obrazek[19].setTexture(&tekstura[2], true);

	tekst[16].setFont(font[0]);
	tekst[16].setString("Anuluj");
	tekst[16].setCharacterSize(rozm1);
	tekst[16].setFillColor(sf::Color(8, 37, 103));
	tekst[16].setStyle(sf::Text::Regular);
	tekst[16].setPosition(0.0f, 0.0f);
	tekst[16].setPosition(obrazek[19].getPosition().x + obrazek[19].getGlobalBounds().width / 2 - tekst[16].getGlobalBounds().width / 2 - tekst[16].getGlobalBounds().left, obrazek[19].getPosition().y + obrazek[19].getGlobalBounds().height / 2 - tekst[16].getGlobalBounds().height / 2 - tekst[16].getGlobalBounds().top);
	tekst[17].setCharacterSize(0);

	//tekst[17].setFont(font[0]);
	//if (tekst[17].getString() == "" || tekst[17].getString() == "Inne ustawienia")
	//{
	//	tekst[17].setString("90");
	//};
	//tekst[17].setCharacterSize(20);
	//tekst[17].setFillColor(sf::Color::Black);
	//tekst[17].setStyle(sf::Text::Regular);
	//tekst[17].setPosition(0.0f, 0.0f);
	//tekst[17].setPosition(ksztalt[1].getPosition().x+5, ksztalt[1].getPosition().y+ksztalt[1].getGlobalBounds().height/2-tekst[17].getGlobalBounds().height/2-tekst[17].getGlobalBounds().top);

}

void background::game()
{
	game_obrazek[0].setSize(sf::Vector2f(float(window_x / 8), float(window_y)));
	game_obrazek[0].setPosition(window_x-window_x/8.0f, 0.0f);
	game_obrazek[0].setTexture(&tekstura[68], true);

	game_obrazek[1].setSize(sf::Vector2f(game_obrazek[0].getGlobalBounds().width-10.0f, window_y/30.0f));
	game_obrazek[1].setFillColor(sf::Color(255, 255, 255, 255));
	game_obrazek[1].setOutlineColor(sf::Color::Black);
	game_obrazek[1].setOutlineThickness(2.0f);
	dopasuj(game_obrazek[0], game_obrazek[1], 0, 10, 0, 0);

	game_text[0].setFont(font[0]);
	game_text[0].setString("POMOC");
	game_text[0].setFillColor(sf::Color::Black);
	game_text[0].setStyle(sf::Text::Bold);
	game_text[0].setPosition(0.0f, 0.0f);
	dopasuj(game_obrazek[1], game_text[0], 0,0, 10, 0);

	game_text[1].setFont(font[0]);
	game_text[1].setString("Aktualny gracz");
	game_text[1].setFillColor(sf::Color::White);
	game_text[1].setStyle(sf::Text::Bold);
	game_text[1].setPosition(0.0f, 0.0f);
	dopasuj(game_obrazek[0], game_text[1], 0, 70, 0, 0);

	game_obrazek[2].setTexture(&tekstura[5], true);
	game_obrazek[2].setSize(sf::Vector2f(float(tekstura[5].getSize().x), float(tekstura[5].getSize().y)));
	dopasuj(game_obrazek[0], game_obrazek[2], 0, game_text[1].getPosition().y + game_text[1].getGlobalBounds().height + 10, window_x/20.0f, 0);

	game_obrazek[3].setSize(sf::Vector2f(game_obrazek[0].getGlobalBounds().width - 10.0f, window_y / 5.0f));
	game_obrazek[3].setFillColor(sf::Color(255, 255, 255, 255));
	game_obrazek[3].setOutlineColor(sf::Color::Black);
	game_obrazek[3].setOutlineThickness(2.0f);
	dopasuj(game_obrazek[0], game_obrazek[3], 0, game_obrazek[2].getPosition().y+game_obrazek[2].getGlobalBounds().height+5,window_x/40.0f,0);

	game_text[2].setFont(font[0]);
	game_text[2].setString("Liczba nocy ");
	game_text[2].setFillColor(sf::Color::Black);
	game_text[2].setStyle(sf::Text::Bold);
	game_text[2].setPosition(0.0f, 0.0f);
	dopasuj(game_obrazek[3], game_text[2], 0, game_obrazek[3].getPosition().y+3, 0, 0);

	game_text[3].setFont(font[0]);
	game_text[3].setString("0");
	game_text[3].setFillColor(sf::Color::Black);
	game_text[3].setStyle(sf::Text::Bold);
	game_text[3].setPosition(0.0f, 0.0f);
	dopasuj(game_obrazek[3], game_text[3], 0, 0, 20, game_text[2].getGlobalBounds().height + 5);

	game_obrazek[4].setSize(sf::Vector2f(0, 0));
	//game_obrazek[4].setSize(sf::Vector2f(game_obrazek[0].getGlobalBounds().width - 10.0f, window_y / 20.0f));
	//game_obrazek[4].setFillColor(sf::Color(255, 255, 255, 255));
	//game_obrazek[4].setOutlineColor(sf::Color::Black);
	//game_obrazek[4].setOutlineThickness(2.0f);
	//dopasuj(game_obrazek[0], game_obrazek[4], 0, game_obrazek[3].getPosition().y + game_obrazek[3].getGlobalBounds().height + 5,0,0);

	//game_text[4].setFont(font[0]);
	//game_text[4].setString("KONIEC TURY");
	//game_text[4].setFillColor(sf::Color::Black);
	//game_text[4].setStyle(sf::Text::Bold);
	//game_text[4].setPosition(0.0f, 0.0f);
	//dopasuj(game_obrazek[4], game_text[4], 0, 0, 10, 0);

	game_obrazek[7].setSize(sf::Vector2f(float(tekstura[33].getSize().x), float(tekstura[33].getSize().y)));
	game_obrazek[7].setTexture(&tekstura[33], true);
	dopasuj(game_obrazek[0], game_obrazek[7], 0, game_obrazek[3].getPosition().y + game_obrazek[3].getGlobalBounds().height + 10, window_x / 25.0f, 0);

	game_obrazek[8].setSize(sf::Vector2f(float(tekstura[47].getSize().x), float(tekstura[47].getSize().y)));
	game_obrazek[8].setTexture(&tekstura[47], true);
	dopasuj(game_obrazek[0], game_obrazek[8], 0, game_obrazek[7].getPosition().y + game_obrazek[7].getGlobalBounds().height + 10, window_x / 40.0f, 0);

	//game_obrazek[5].setSize(sf::Vector2f(game_obrazek[0].getGlobalBounds().width - 10.0f, window_y / 20.0f));
	//game_obrazek[5].setFillColor(sf::Color(255, 255, 255, 255));
	//game_obrazek[5].setOutlineColor(sf::Color::Black);
	//game_obrazek[5].setOutlineThickness(2.0f);
	//dopasuj(game_obrazek[0], game_obrazek[5], 0, game_obrazek[8].getPosition().y + game_obrazek[8].getGlobalBounds().height + 5, 0, 0);
	game_obrazek[5].setSize(sf::Vector2f(0, 0));
	//game_text[5].setFont(font[0]);
	//game_text[5].setString("ZAPISZ GRE");
	//game_text[5].setFillColor(sf::Color::Black);
	//game_text[5].setStyle(sf::Text::Bold);
	//game_text[5].setPosition(0.0f, 0.0f);
	//dopasuj(game_obrazek[5], game_text[5], 0, 0, 10, 0);


	game_obrazek[6].setSize(sf::Vector2f(game_obrazek[0].getGlobalBounds().width - 10.0f, window_y / 20.0f));
	game_obrazek[6].setFillColor(sf::Color(255, 255, 255, 255));
	game_obrazek[6].setOutlineColor(sf::Color::Black);
	game_obrazek[6].setOutlineThickness(2.0f);
	dopasuj(game_obrazek[0], game_obrazek[6], 0, game_obrazek[8].getPosition().y + game_obrazek[8].getGlobalBounds().height + 5.0f, 0, 0);

	game_text[6].setFont(font[0]);
	game_text[6].setString("WYJSCIE");
	game_text[6].setFillColor(sf::Color::Black);
	game_text[6].setStyle(sf::Text::Bold);
	game_text[6].setPosition(0.0f, 0.0f);
	dopasuj(game_obrazek[6], game_text[6], 0, 0, 10, 0);

	game_obrazek[13].setSize(sf::Vector2f(stwor[0].getSize().x, stwor[0].getSize().y));
	game_obrazek[13].setFillColor(sf::Color(65, 65, 65, 200));
	game_obrazek[13].setPosition(0.0f, 0.0f);
	game_obrazek[13].setOutlineColor(sf::Color::Blue);
	game_obrazek[13].setOutlineThickness(1.0f);

	game_obrazek[14].setSize(sf::Vector2f(window_x-game_obrazek[0].getGlobalBounds().width, float(window_y)));
	game_obrazek[14].setFillColor(sf::Color(255, 255, 255, 255));
	game_obrazek[14].setPosition(sf::Vector2f(0, 0));
	game_obrazek[14].setOutlineThickness(1.0f);

	pomoc_text = L"POMOC!\nW grze slawika gracze wcielaj¹ siê w g³owy mo¿nych rodw w fantystycznym œwiecie Slavika. Ka¿dy z nich dysponuje 6 bohaterami, \nktórych w trakcie gry wysy³a do ró¿nych krain,gdzie bêd¹ oni mogli walczyæ z nawiedzaj¹cymi je potworami. Im wiêkszy \nwk³ad bohaterów gracza w pokonanie potworów, tym wiêcej zdobêdzie punktów chwa³y dla swojego rodu. Gra toczy siê \nprzez kilka miesiêcy, do chwili, w której ksiê¿niczka bêdzie mog³a wype³niæ rytua³ i odnowiæ moc amuletu. Ród, \nktóry w tym czasie zdobêdzie najwiêcej punktów chwa³y, zdobêdzie prawo do rêki ksiê¿niczki i wygra grê. \n\nW gdze gracze na przemian wykonuj¹ swoje tury. Ka¿dy gracz w turze ma do wykonania 3 akcje: \n1. Do³o¿yæ 2 karty bohatera do krain (jeœli to tylko mo¿liwe) \n2. Do³o¿yæ do krain 1 kartê potwora (jeœli gracz nie po³o¿y³ ¿adnej karty bohatera w tej turze albo po³o¿y³ tylko jedn¹ \nnale¿y do³o¿yæ do krain 2 karty potwora) \n3. Wymieniæ jedn¹ z kart potworów na inn¹ (mo¿na ten ruch pomin¹æ, wystarczy klikn¹æ na odpowiednie okno) \n\nNa koñcu ka¿dej tury liczba kart potworów gracza jest uzupe³niana do 5. \n\nW momencie, gdy w danej krainie zostanie wype³niona maksymalna iloœæ potworów, na koñcu tury danego gracza rozpoczyna siê \nwalka. Walkê o krainê tocz¹ gracze i potwory, a wygrywa j¹ ta strona, która posiada wiêksz¹ iloœæ punktów si³y. \nIloœæ punktów si³y wypisana jest na ka¿dej karciew lewym górnym rogu. Do tego ka¿da karta posiada specjaln¹ \numiejêtnoœæ, która modyfikuje zachowanie i punkty si³y innch bohaterów i potworów, w zale¿noœci od ich umiejêtnoœci \noraz punktów si³y.";
	game_text[19].setFont(font[0]);
	game_text[19].setString(pomoc_text);
	game_text[19].setFillColor(sf::Color::Black);
	game_text[19].setStyle(sf::Text::Bold);
	game_text[19].setPosition(0.0f, 0.0f);
	dopasuj(game_obrazek[14], game_text[19], 0, 10, 10, 0);

	game_obrazek[15].setSize(sf::Vector2f(float(window_x / 5.5), float(window_y / 2.5)));
	game_obrazek[15].setPosition(0.0f, 0.0f);
	game_obrazek[15].setTexture(&tekstura[33], true);

	game_obrazek[16].setSize(sf::Vector2f(window_x - game_obrazek[0].getGlobalBounds().width, float(window_y)));
	game_obrazek[16].setFillColor(sf::Color(255, 255, 255, 255));
	game_obrazek[16].setPosition(sf::Vector2f(0, 0));
	game_obrazek[16].setOutlineThickness(1.0f);

	game_text[20].setFont(font[0]);
	game_text[20].setString("Koniec gry");
	game_text[20].setFillColor(sf::Color::Black);
	game_text[20].setStyle(sf::Text::Bold);
	game_text[20].setPosition(0.0f, 0.0f);
	dopasuj(game_obrazek[16], game_text[20], 0, 0, 10, 0);

}