#include "game.h"

/*
ability:
//playerss
1 - kradnie skarby oraz punkty dodatkowe z potworów
2 - si³a tej karty to 2 + 2 za ka¿dego wojownika w tej krainie
3 - ta karta mo¿na zostaæ zamieniona za dowoln¹ kartê bohatera
4 - maksymalna si³a potwora w tej krainie wynosi 4
5 - wojownik
6 - wojownik

//monsters
ability:
5 - w momencie zagrania tej karty wybierasz jednego bohatera i oddajesz go w rêkê gracza
6 - dzia³a po ustaleniu wyniku walki ze z³em, je¿eli wygrali bohaterowi, najsilniejszy z nich ma si³ê równ¹ 0
7 - si³a wojowników spada do 2
8 - w tej krainie nie dzia³aj¹ umiejêtnoœci bohaterów
9 - t¹ kartê nale¿y traktowaæ jako bohatera i nale¿y j¹ umieszczaæ po stronie bohaterów
10 - staje siê kopi¹ dowolnego potwora umieszczonego w dowolnej krainie

pkt - dodatkowe punkty z potworów

//skarb
pkt - ilosc punktow chwa³y ze skarbu
noc - 1 jeœli jest noc¹, 0 jeœli nie

//krainy
ability:
11 - w tej krainie nie dzia³a umiejêtnoœæ 3 bohaterów (nie mo¿e zostaæ zamieniona dowolnym bohaterem)
12 - si³a bohaterów z umiejêtnoœci¹ 3 wynosi +1
13 - stwory z atakiem 2 i 4 w tej krainie maj¹ +1 do ataku



game_obrazek[1] - przycisk POMOC
game_obrazek[2] - zawiera kolor aktualnego gracza (tzn turê tego gracza)
game_text[3] - czas do konca tury
game_obrazek[4] - przycisk KONIEC TURY
game_obrazek[5] - ZAPISZ GRE
game_obrazek[6] - WYJSCIE
game_obrazek[7] - obrazek TALI
game_obrazek[8] - obrazek DECKU

game_obrazek[9] - T£O na punkty dla SZARY
game_text[7] - "SZARY"
game_text[9] - iloœæ punktów SZAREGO

game_obrazek[10] - T£O na punkty dla NIEBIESKI
game_text[10] - "NIEBIESKI"
game_text[12] - iloœæ punktów NIEBIESKIEGO

game_obrazek[11] - T£O na punkty dla ZIELONY
game_text[13] - "ZIELONY"
game_text[15] - iloœæ punktów ZIELONEGO

game_obrazek[12] - T£O na punkty dla ROZOWY
game_text[16] - "ROZOWY"
game_text[18] - iloœæ punktów ROZOWEGO

*/

game::game()
{
	names = new sf::String[4];
	tab_human = new int[4];
	tab_comp = new int[4];
	is_draw_vip = 0;
	is_mouse = 0;
	krainy = new kraina[5];
	tyl_skarb = new checked[5];
	scale_div = 7;
	kliknieto_bohatera = 0;
	kliknieto_potwora = 0;
	dynamic_pos_drukuj = 0;
	pomoc_active = 1;
	player_id = 0;
	draw_accept = 0;
	tura_pos = 0;

	ilosc_boh_do_wstawienia = 0;
	ilosc_pot_do_wstawienia = 0;
	pick_boh = 0;
	pick_pot = 0;
	walka = 0;
	ilosc_nocy = 0;
	koniec = 0;
}

game::~game()
{
	delete[] player1;
	delete[] names;
	delete[] tab_human;
	delete[] tab_comp;
	delete[] krainy;
	delete[] skarby;
	delete[] tyl_skarb;
	delete[] talia;
	while (!deck.empty())
	{
		deck.pop();
	}
	while (!skarb.empty())
	{
		skarb.pop();
	}
}

void game::set_game(background& TLO, controller_window& Window, sf::Vector2f& worldPos)
{
	stand_x = TLO.szary[0].getGlobalBounds().width;
	stand_y = TLO.szary[0].getGlobalBounds().height;

	ilosc_graczy = 0;
	ilosc_human = 0;
	tab_human_ilosc = 0;
	tab_comp_ilosc = 0;

	for (int i = 6, j=10; i <= 9; i++, j+=2)
	{
		if (TLO.obrazek[i].getGame_checked() == 1) //sprawdzam, czy checkbox aktywny zostal zaznaczony (GRACZ AKTYWNY)
		{
			ilosc_graczy++;
			if (TLO.obrazek[j].getPlayer() == 1) //sprawdzam, który gracz to CZ£OWIEK A KTÓRY TO KOMPUTER
			{
				ilosc_human++;
				tab_human[tab_human_ilosc] = j;
				tab_human_ilosc++;
			}
			else
			{
				tab_comp[tab_comp_ilosc] = j;
				tab_comp_ilosc++;
			}
		}
	}


	if (ilosc_graczy < 2)
	{
		Window.SetWindow_ID(5);
		TLO.Set_Message(worldPos, L"Musisz wybraæ conajmniej 2 graczy do gry, aby mog³a siê rozpocz¹æ! ");
		TLO.timer_start = chrono::steady_clock::now();
		TLO.reset_showmsg = 1;
		TLO.timer_started = 0;
	}
	else
	{
		Create_Deck(&TLO);
		Create_Skarby(&TLO);
		player1 = new player[ilosc_graczy];

		names[0] = "SZARY";
		names[1] = "NIEBIESKI";
		names[2] = L"RÓ¯OWY";
		names[3] = "ZIELONY";

		if (ilosc_graczy <= 3)
			ilosc_krain = 4;
		else
			ilosc_krain = 5;

		setPlayer(TLO);
		setKrainy(TLO);

	}
}

void game::click_boh(player &players)
{
	for (list <checked>::iterator it = players.bohater.begin(); it != players.bohater.end(); it++)
	{
		if (it->kliknieto_bohatera == 1)
		{
			kliknieto_bohatera = 1;
		}
	}

	for (list <checked>::iterator it = players.potwor.begin(); it != players.potwor.end(); it++)
	{
		if (it->kliknieto_potwora == 1)
		{
			kliknieto_potwora = 1;
		}
	}
}

void game::draw_players(sf::RenderWindow* app, player &players)
{
	int i = 0;
	for (list <checked>::iterator it = players.bohater.begin(); it != players.bohater.end(); it++)
	{
		if (player_id == players.id && draw_accept == 1)
		{
			if (it->priorytet == 1)
			{
				draw_vip = *it;
				is_draw_vip = 1;
			}
			else
			{
				app->draw(*it);
			}
		}
		else
		{
			players.tyl_bohater[i].setSize(sf::Vector2f(it->getSize().x, it->getSize().y));
			players.tyl_bohater[i].setPosition(sf::Vector2f(it->getPosition().x, it->getPosition().y));
			app->draw(players.tyl_bohater[i]);
		}
	}
	i = 0;
	for (list <checked>::iterator it = players.potwor.begin(); it != players.potwor.end(); it++)
	{
		if (player_id == players.id && draw_accept == 1)
		{
			if (it->priorytet == 1)
			{
				draw_vip = *it;
				is_draw_vip = 1;
			}
			else
			{
				app->draw(*it);
			}
		}
		else
		{
			players.tyl_potwor[i].setSize(sf::Vector2f(it->getSize().x, it->getSize().y));
			players.tyl_potwor[i].setPosition(sf::Vector2f(it->getPosition().x, it->getPosition().y));
			app->draw(players.tyl_potwor[i]);
		}
	}
}

void game::draw_krainy(sf::RenderWindow* app, kraina &krains)
{
	for (list <checked>::iterator it = krains.bohater.begin(); it != krains.bohater.end(); it++)
	{
		if (it->priorytet == 1)
		{
			draw_vip = *it;
			is_draw_vip = 1;
		}
		else
		{
			if (it->drukuj_ksztalt == 1)
			{
				app->draw(*it);
			}
			else
			{
				if (kliknieto_bohatera == 1)
				{
					app->draw(*it);
				}
			}
		}
	}

	for (list <checked>::iterator it = krains.potwor.begin(); it != krains.potwor.end(); it++)
	{
		if (it->priorytet == 1)
		{
			draw_vip = *it;
			is_draw_vip = 1;
		}
		else
		{
			if (it->drukuj_ksztalt == 1)
			{
				app->draw(*it);
			}
			else
			{
				if (kliknieto_potwora == 1)
				{
					app->draw(*it);
				}
			}
		}
	}

}

void game::Drukuj(sf::RenderWindow * app, background &TLO)
{
	if (ilosc_nocy < 5 && koniec == 0)
	{
		kliknieto_bohatera = 0;
		kliknieto_potwora = 0;

		click_boh(player1[0]);
		click_boh(player1[1]);

		if (ilosc_graczy >= 3)
		{
			click_boh(player1[2]);
		}
		if (ilosc_graczy == 4)
		{
			click_boh(player1[3]);
		}

		if (ilosc_graczy >= 1)
		{

			draw_players(app, player1[0]);

			app->draw(tyl_skarb[0]);
			app->draw(krainy[0].img);

			app->draw(tyl_skarb[1]);
			app->draw(krainy[1].img);

			app->draw(tyl_skarb[2]);
			app->draw(krainy[2].img);


			draw_krainy(app, krainy[0]);
			draw_krainy(app, krainy[1]);
			draw_krainy(app, krainy[2]);
		}

		if (ilosc_graczy >= 2)
		{
			draw_players(app, player1[1]);

			app->draw(tyl_skarb[3]);
			app->draw(krainy[3].img);

			draw_krainy(app, krainy[3]);
		}
		if (ilosc_graczy >= 3)
		{
			draw_players(app, player1[2]);
		}
		if (ilosc_graczy >= 4)
		{
			draw_players(app, player1[3]);

			app->draw(tyl_skarb[4]);
			app->draw(krainy[4].img);

			draw_krainy(app, krainy[4]);
		}

		app->draw(TLO.msg_img);
		app->draw(TLO.msg);

		if (is_draw_vip == 1)
		{
			app->draw(draw_vip);
		}
		if (dynamic_pos_drukuj == 1)
		{
			app->draw(dynamic_pos_ob);
		}
		if (pomoc_active == 1)
		{
			app->draw(TLO.game_obrazek[14]);
			app->draw(TLO.game_text[19]);
		}
	}
	else
	{
		app->draw(TLO.game_obrazek[16]);
		app->draw(TLO.game_text[20]);
	}
}

int game::is_mouse_def(player &players)
{
	int a = 0, b = 0;
	for (list <checked>::iterator it = players.bohater.begin(); it != players.bohater.end(); it++)
	{
		if (it->is_mouse == 1)
		{
			a = 1;
		}
	}

	for (list <checked>::iterator it = players.potwor.begin(); it != players.potwor.end(); it++)
	{
		if (it->is_mouse == 1)
		{
			b = 1;
		}
	}
	if (a == 1 || b == 1)
	{
		return 1;
	}

	return 0;
}

int game::is_mouse_def(kraina &krainy)
{
	int a = 0, b = 0;
	for (list <checked>::iterator it = krainy.bohater.begin(); it != krainy.bohater.end(); it++)
	{
		if (it->is_mouse == 1)
		{
			a = 1;
		}
	}
	for (list <checked>::iterator it = krainy.potwor.begin(); it != krainy.potwor.end(); it++)
	{
		if (it->is_mouse == 1)
		{
			b = 1;
		}
	}
	if (a == 1 || b == 1)
	{
		return 1;
	}

	return 0;
}

void game::is_mouse_Exist()
{
	is_mouse = 0;
	for (int i = 0; i < ilosc_graczy; i++)
	{
		if (is_mouse_def(player1[i]) == 1)
		{
			is_mouse = 1;
		}
	}
	for (int i = 0; i < ilosc_krain; i++)
	{
		if (is_mouse_def(krainy[i]) == 1)
		{
			is_mouse = 1;
		}
	}
}

void game::Event_Player(background &TLO, player &players, sf::Vector2f worldPos, int player_idd, int actual_id_player)
{
	int reset = 0;
	int a = 0;
	for (list <checked>::iterator it = players.bohater.begin(); it != players.bohater.end(); it++)
	{
		if (actual_id_player == players.id && draw_accept == 1 && tura_pos != 2)
		{
			if (it->getGlobalBounds().contains(worldPos) && (is_mouse == 0 || it->is_mouse == 1))
			{
				it->is_mouse = 1;
				for (int i = 0; it->getSize().x <= TLO.window_x_return() / scale_div; i++)
				{
					it->setSize(sf::Vector2f(it->getSize().x + 2.0f * i, it->getSize().y + 3.0f*i));
				}

				if (player_idd <= 1)
				{
					TLO.dopasuj(TLO.obrazek[0], *it);
				}

				it->priorytet = 1;

			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && it->getGlobalBounds().contains(worldPos) && it->is_mouse == 1 && pick_boh == 1)
			{
				if (it->press == 0)
				{
					tmp_pos = worldPos - it->getPosition();
					it->press = 1;
				}
				it->setPosition(worldPos.x - tmp_pos.x, worldPos.y - tmp_pos.y);
				it->back = 0;
				it->click = 1;
				it->kliknieto_bohatera = 1;
			}
			else
			{
				int checked_out = 0;
				if (player_idd == 0)
				{
					if ((worldPos.x < TLO.game_obrazek[9].getPosition().x + TLO.game_obrazek[9].getGlobalBounds().width + 5 + a*stand_x
						|| worldPos.x > TLO.game_obrazek[9].getPosition().x + TLO.game_obrazek[9].getGlobalBounds().width + 5 + a*stand_x + stand_x
						|| worldPos.y > TLO.window_y_return()
						|| worldPos.y < TLO.window_y_return() - stand_y) && it->click == 1)
					{
						checked_out = 1;
					}
				}
				if (player_idd == 1)
				{
					if ((worldPos.x < TLO.game_obrazek[11].getPosition().x - it->getGlobalBounds().width - 1 - a*stand_x
						|| worldPos.x > TLO.game_obrazek[11].getPosition().x - it->getGlobalBounds().width - 1 - a*stand_x + stand_x
						|| worldPos.y > 1 + stand_y
						|| worldPos.y < 1) && it->click == 1)
					{
						checked_out = 1;
					}
				}
				if (player_idd == 2)
				{
					if ((worldPos.x < 1
						|| worldPos.x > 1 + stand_x
						|| worldPos.y > TLO.game_obrazek[10].getPosition().y + TLO.game_obrazek[10].getGlobalBounds().height + 1 + a*stand_x + 2 * stand_x
						|| worldPos.y < TLO.game_obrazek[10].getPosition().y + TLO.game_obrazek[10].getGlobalBounds().height + 1 + a*stand_x + stand_x) && it->click == 1)
					{
						checked_out = 1;
					}
				}
				if (player_idd == 3)
				{
					if ((worldPos.x < TLO.game_obrazek[0].getPosition().x - stand_y
						|| worldPos.x > TLO.game_obrazek[0].getPosition().x
						|| worldPos.y > TLO.game_obrazek[12].getPosition().y - it->getGlobalBounds().height - TLO.game_text[16].getGlobalBounds().height - 2 - a*stand_x - stand_x
						|| worldPos.y < TLO.game_obrazek[12].getPosition().y - it->getGlobalBounds().height - TLO.game_text[16].getGlobalBounds().height - 2 - a*stand_x + 2 * stand_x) && it->click == 1)
					{
						checked_out = 1;
					}
				}
				if (checked_out == 1)
				{
					it->back = 1;
					it->press = 0;
					it->przesunieto_bohatera = 1;
					it->click = 0;
					it->kliknieto_bohatera = 0;

					for (int i = 0; i < ilosc_krain; i++)
					{
						for (list <checked>::iterator it2 = krainy[i].bohater.begin(); it2 != krainy[i].bohater.end(); it2++)
						{
							if (it2->getGlobalBounds().contains(worldPos) && it2->drukuj_ksztalt == 0)
							{
								if (krainy[i].ilosc_boh < krainy[i].max_ilosc_boh)
								{
									it->setSize(sf::Vector2f(it2->getSize().x, it2->getSize().y));
									it->setPosition(sf::Vector2f(it2->getPosition().x, it2->getPosition().y));
									it->setFillColor(sf::Color(255, 255, 255, 255));
									it->drukuj_ksztalt = 1;
									if (player_idd == 2)
									{
										it->rotate(-270);
									}
									if (player_idd == 3)
									{
										it->rotate(-90);
									}
									list <checked>::iterator tmpk;
									for (tmpk = krainy[i].bohater.begin(); tmpk != krainy[i].bohater.end(); tmpk++)
									{
										if (tmpk->drukuj_ksztalt == 0)
										{
											break;
										}
									}

									ilosc_boh_do_wstawienia--;
									krainy[i].ilosc_boh++;

									it2 = krainy[i].bohater.insert(tmpk, *it);
									krainy[i].bohater.pop_back();

									it = players.bohater.erase(it);
									setKrainy2(TLO, krainy[i], 1);
									reset = 1;
									break;
								}
							}
						}
						if (reset == 1)
						{
							break;
						}
					}

					if (reset == 1)
					{
						break;
					}
				}
			}
		}
		if (!it->getGlobalBounds().contains(worldPos) || it->back == 1)
		{
			if (player_idd == 0)
			{
				it->setPosition(TLO.game_obrazek[9].getPosition().x + TLO.game_obrazek[9].getGlobalBounds().width + 5 + a*stand_x, TLO.window_y_return() - stand_y);
			}
			if (player_idd == 1)
			{
				it->setPosition(TLO.game_obrazek[11].getPosition().x - it->getGlobalBounds().width - 1 - a*stand_x, 1);
			}
			if (player_idd == 2)
			{
				it->setPosition(1, TLO.game_obrazek[10].getPosition().y + TLO.game_obrazek[10].getGlobalBounds().height + 1 + a*stand_x + stand_x);
			}
			if (player_idd == 3)
			{
				it->setPosition(TLO.game_obrazek[0].getPosition().x, TLO.game_obrazek[12].getPosition().y - it->getGlobalBounds().height - TLO.game_text[16].getGlobalBounds().height - 2 - a*stand_x - stand_x/2);
			}
			it->setSize(sf::Vector2f(stand_x, stand_y));
			it->priorytet = 0;
			is_draw_vip = 0;
			it->is_mouse = 0;
			it->back = 0;
		}
		a++;
	}

	for (list <checked>::iterator it = players.potwor.begin(); it != players.potwor.end(); it++)
	{
		if (actual_id_player == players.id && draw_accept == 1)
		{
			if (it->getGlobalBounds().contains(worldPos) && (is_mouse == 0 || it->is_mouse == 1))
			{
				it->is_mouse = 1;
				for (int i = 0; it->getSize().x <= TLO.window_x_return() / scale_div; i++)
				{
					it->setSize(sf::Vector2f(it->getSize().x + 2.0f * i, it->getSize().y + 3.0f*i));
				}

				if (player_idd <= 1)
				{
					TLO.dopasuj(TLO.obrazek[0], *it);
				}

				it->priorytet = 1;

			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && it->getGlobalBounds().contains(worldPos) && it->is_mouse == 1 && pick_pot == 1)
			{
				if (it->press == 0)
				{
					tmp_pos = worldPos - it->getPosition();
					it->press = 1;
				}
				it->setPosition(worldPos.x - tmp_pos.x, worldPos.y - tmp_pos.y);
				it->back = 0;
				it->click = 1;
				it->kliknieto_potwora = 1;
			}
			else
			{
				int checked_out = 0;
				if (player_idd == 0)
				{
					if ((worldPos.x < TLO.game_obrazek[9].getPosition().x + TLO.game_obrazek[9].getGlobalBounds().width + 5 + a*stand_x
						|| worldPos.x > TLO.game_obrazek[9].getPosition().x + TLO.game_obrazek[9].getGlobalBounds().width + 5 + a*stand_x + stand_x
						|| worldPos.y > TLO.window_y_return()
						|| worldPos.y < TLO.window_y_return() - stand_y) && it->click == 1)
					{
						checked_out = 1;
					}
				}
				if (player_idd == 1)
				{
					if ((worldPos.x < TLO.game_obrazek[11].getPosition().x - it->getGlobalBounds().width - 1 - a*stand_x
						|| worldPos.x > TLO.game_obrazek[11].getPosition().x - it->getGlobalBounds().width - 1 - a*stand_x + stand_x
						|| worldPos.y > 1 + stand_y
						|| worldPos.y < 1) && it->click == 1)
					{
						checked_out = 1;
					}
				}
				if (player_idd == 2)
				{
					if ((worldPos.x < 1
						|| worldPos.x > 1 + stand_x
						|| worldPos.y > TLO.game_obrazek[10].getPosition().y + TLO.game_obrazek[10].getGlobalBounds().height + 1 + a*stand_x + 2 * stand_x
						|| worldPos.y < TLO.game_obrazek[10].getPosition().y + TLO.game_obrazek[10].getGlobalBounds().height + 1 + a*stand_x + stand_x) && it->click == 1)
					{
						checked_out = 1;
					}
				}
				if (player_idd == 3)
				{
					if ((worldPos.x < TLO.game_obrazek[0].getPosition().x - stand_y
						|| worldPos.x > TLO.game_obrazek[0].getPosition().x
						|| worldPos.y > TLO.game_obrazek[12].getPosition().y - it->getGlobalBounds().height - TLO.game_text[16].getGlobalBounds().height - 2 - a*stand_x
						|| worldPos.y < TLO.game_obrazek[12].getPosition().y - it->getGlobalBounds().height - TLO.game_text[16].getGlobalBounds().height - 2 - a*stand_x + stand_x) && it->click == 1)
					{
						checked_out = 1;
					}
				}

				if (checked_out == 1)
				{
					it->back = 1;
					it->press = 0;
					it->przesunieto_potwora = 1;
					for (int i = 0; i < ilosc_krain; i++)
					{
						for (list <checked>::iterator it2 = krainy[i].potwor.begin(); it2 != krainy[i].potwor.end(); it2++)
						{
							if (it2->getGlobalBounds().contains(worldPos) && it2->drukuj_ksztalt == 0)
							{
								if (krainy[i].ilosc_stwor < krainy[i].max_ilosc_stwor)
								{
									it->setSize(sf::Vector2f(it2->getSize().x, it2->getSize().y));
									it->setPosition(sf::Vector2f(it2->getPosition().x, it2->getPosition().y));
									it->setFillColor(sf::Color(255, 255, 255, 255));
									it->drukuj_ksztalt = 1;
									if (player_idd == 2)
									{
										it->rotate(-270);
									}
									if (player_idd == 3)
									{
										it->rotate(-90);
									}
									list <checked>::iterator tmpk;
									for (tmpk = krainy[i].potwor.begin(); tmpk != krainy[i].potwor.end(); tmpk++)
									{
										if (tmpk->drukuj_ksztalt == 0)
										{
											break;
										}
									}

									ilosc_pot_do_wstawienia--;
									
									krainy[i].ilosc_stwor++;

									it2 = krainy[i].potwor.insert(tmpk, *it);
									krainy[i].potwor.pop_back();

									it = players.potwor.erase(it);
									setKrainy2(TLO, krainy[i], 1);
									players.ilosc_potworow--;
									reset = 1;
									break;
								}
							}
						}
						if (reset == 1)
						{
							break;
						}
					}
					if (reset == 1)
					{
						break;
					}
				}
				it->click = 0;
				it->kliknieto_potwora = 0;
			}
		}
		if (!it->getGlobalBounds().contains(worldPos) || it->back == 1)
		{
			if (player_idd == 0)
			{
				it->setPosition(TLO.game_obrazek[9].getPosition().x + TLO.game_obrazek[9].getGlobalBounds().width + 5 + a*stand_x, TLO.window_y_return() - stand_y);
			}
			if (player_idd == 1)
			{
				it->setPosition(TLO.game_obrazek[11].getPosition().x - it->getGlobalBounds().width - 1 - a*stand_x, 1);
			}
			if (player_idd == 2)
			{
				it->setPosition(1, TLO.game_obrazek[10].getPosition().y + TLO.game_obrazek[10].getGlobalBounds().height + 1 + a*stand_x + stand_x);
			}
			if (player_idd == 3)
			{
				it->setPosition(TLO.game_obrazek[0].getPosition().x, TLO.game_obrazek[12].getPosition().y - it->getGlobalBounds().height - TLO.game_text[16].getGlobalBounds().height - 2 - a*stand_x - stand_x/2);
			}
			it->setSize(sf::Vector2f(stand_x, stand_y));
			it->priorytet = 0;
			is_draw_vip = 0;
			it->is_mouse = 0;
			it->back = 0;
		}

		if (tura_pos == 2 && draw_accept == 1)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && it->getGlobalBounds().contains(worldPos))
			{
				deck.push(*it);
				it = players.potwor.erase(it);
				players.ilosc_potworow--;
				Set_Potwor(player_id, TLO);
				tura_pos = 3;
				std::thread t3(&game::set_tura_pos, this, 1);
				t3.detach();
				sf::String textt;
				textt = L"Pozosta³o Ci 5 sekund na przejrzenie swoich kart!";
				sf::Vector2f v1(TLO.game_obrazek[12].getPosition().x - TLO.window_x_return() / 6, TLO.window_y_return() - 5);
				TLO.set_msg(v1, textt);
				break;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.msg_img.getGlobalBounds().contains(worldPos))
			{
				Set_Potwor(player_id, TLO);
				tura_pos = 3;
				std::thread t3(&game::set_tura_pos, this, 1);
				t3.detach();
				sf::String textt;
				textt = L"Pozosta³o Ci 5 sekund na przejrzenie swoich kart!";
				sf::Vector2f v1(TLO.game_obrazek[12].getPosition().x - TLO.window_x_return() / 6, TLO.window_y_return() - 5);
				TLO.set_msg(v1, textt);
				break;
			}
		}

		a++;
	}

	if (draw_accept == 0)
	{
		sf::String textt;
		textt = L"Upewnij siê, ¿e gracz przeciwny nie patrzy na monitor i kliknij na t¹ wiadomoœæ, aby odkryæ Twoje karty!";
		sf::Vector2f v1(TLO.game_obrazek[12].getPosition().x - TLO.window_x_return()/6, TLO.window_y_return() - 5);
		TLO.set_msg(v1, textt);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.msg_img.getGlobalBounds().contains(worldPos))
		{
			draw_accept = 1;
			tura_pos = 1;
			if (players.bohater.size() >= 2)
			{
				ilosc_boh_do_wstawienia = 2;
				ilosc_pot_do_wstawienia = 1;
			}
			if (players.bohater.size() == 1)
			{
				ilosc_boh_do_wstawienia = 1;
				ilosc_pot_do_wstawienia = 2;
			}
			if (players.bohater.size() == 0)
			{
				ilosc_boh_do_wstawienia = 0;
				ilosc_pot_do_wstawienia = 2;
			}

			int maxx = 0;
			int odj = 0;

			for (int i = 0; i < ilosc_krain; i++)
			{
				maxx += krainy[i].max_ilosc_boh;
				odj += krainy[i].ilosc_boh;
			}
			while (maxx - odj < ilosc_boh_do_wstawienia)
			{
				ilosc_boh_do_wstawienia--;
			}

			maxx = 0;
			odj = 0;
			for (int i = 0; i < ilosc_krain; i++)
			{
				maxx += krainy[i].max_ilosc_stwor;
				odj += krainy[i].ilosc_stwor;
			}

			while (maxx - odj < ilosc_pot_do_wstawienia)
			{
				ilosc_pot_do_wstawienia--;
			}

			sf::String textt;
			textt = L"Wybierz teraz karty graczy i bohaterów i umieœæ je w wybranych przez Ciebie krainach!";
			sf::Vector2f v1(TLO.game_obrazek[12].getPosition().x - TLO.window_x_return() / 6, TLO.window_y_return() - 5);
			TLO.set_msg(v1, textt);
		}
	}
	if (tura_pos == 1 && draw_accept == 1)
	{
		pick_boh = 0;
		pick_pot = 0;
		if (ilosc_boh_do_wstawienia != 0)
		{
			pick_boh = 1;
		}
		if (ilosc_pot_do_wstawienia != 0)
		{
			pick_pot = 1;
		}
		if (ilosc_boh_do_wstawienia == 0 && ilosc_pot_do_wstawienia == 0)
		{
			sf::String textt;
			textt = L"Kliknij na kartê potwora, by j¹ wymieniæ lub na t¹ wiadomoœæ, aby nie wymieniaæ ¿adnej!";
			sf::Vector2f v1(TLO.game_obrazek[12].getPosition().x - TLO.window_x_return() / 6, TLO.window_y_return() - 5);
			TLO.set_msg(v1, textt);
			tura_pos = 2;
		}
	}
	
	if (tura_pos == 4 && draw_accept == 1)
	{
		walka = 0;
		int walka_tab[5];
		for (int i = 0; i < ilosc_krain; i++)
		{
			if (krainy[i].ilosc_stwor == krainy[i].max_ilosc_stwor)
			{
				walka_tab[walka] = i;
				walka++;
			}
		}
		for (int j = 0; j < walka; j++)
		{
			int i = walka_tab[j];
			int reset_boh_ability = 0; //jest 1, to nie dzialaj¹ umiejêtnoœci bohaterów
			int sila_boh_0 = 0; //dziala po ustaleniu walki, jesli wygrali bohaterowie, nasilniejszy ma 0 sily
			int sil_woj_2 = 0; //sila wojownikow wynosi 2
			int kradziez = 0; //czy gracz kradnie skarby i pkt z potworow
			int kradziez_id = -1; //id gracza, ktora kradnie skarby
			int zwieksz_atak = 0; //zwieksza sile o +2 za kazdego wojownika w krainie
			int ilosc_wojownikow = 0; //ilosc wojownikow w danej krainie
			int dodatk_pkt_z_potw = 0; //ilosc dodatkowych pkt z potworow
			int max_pot_4 = 0; //maksymalny atak potwora to 4
			int max_sila = 0; //bohater z najwieksza sila

			int sila_boh = 0;
			int sila_pot = 0;

			for (list <checked>::iterator it = krainy[i].bohater.begin(); it != krainy[i].bohater.end(); it++)
			{
				if (krainy[i].ability == 12)
				{
					if (it->ability == 3)
					{
						it->sila += 1;
					}
				}
				if (it->ability == 1)
				{
					kradziez = 1;
					kradziez_id = it->player_id;
				}
				if (it->ability == 2)
				{
					zwieksz_atak = 1;
				}
				if (it->ability == 4)
				{
					max_pot_4 = 1;
				}
				if (it->ability == 5 || it->ability == 6)
				{
					ilosc_wojownikow++;
				}
				if (max_sila < it->sila)
				{
					max_sila = it->sila;
				}

			}

			for (list <checked>::iterator it = krainy[i].potwor.begin(); it != krainy[i].potwor.end(); it++)
			{
				if (krainy[i].ability == 13)
				{
					if (it->sila == 2 || it->sila == 4)
					{
						it->sila += 1;
					}
				}

				if (it->ability == 8)
				{
					reset_boh_ability = 1;
				}
				if (it->ability == 6)
				{
					sila_boh_0 = 1;
				}
				if (it->ability == 7)
				{
					sil_woj_2 = 1;
				}
				if (it->pkt != 0)
				{
					dodatk_pkt_z_potw += it->pkt;
				}
				if (max_pot_4 == 1)
				{
					if (it->sila > 4)
					{
						it->sila = 4;
					}
				}

			}

			for (list <checked>::iterator it = krainy[i].bohater.begin(); it != krainy[i].bohater.end(); it++)
			{
				if (sil_woj_2 == 1)
				{
					if (it->ability == 5 || it->ability == 6)
					{
						it->sila = 2;
					}
				}
				if (zwieksz_atak == 1 && reset_boh_ability == 0)
				{
					if (it->ability == 2)
					{
						it->sila += 2 * ilosc_wojownikow;
					}
				}

				sila_boh += it->sila;
			}

			for (list <checked>::iterator it = krainy[i].potwor.begin(); it != krainy[i].potwor.end(); it++)
			{
				sila_pot += it->sila;
			}

			
			if (sila_pot > sila_boh)
			{
				//potwory wygraly
				for (list <checked>::iterator it = krainy[i].potwor.begin(); it != krainy[i].potwor.end(); it++)
				{
					deck.push(*it);
				}

				krainy[i].potwor.clear();

				for (list <checked>::iterator it = krainy[i].bohater.begin(); it != krainy[i].bohater.end(); it++)
				{
					if (it->player_id > -1)
					{
						if (it->player_id == 2)
						{
							it->rotate(270);
						}
						if (it->player_id == 3)
						{
							it->rotate(90);
						}
						player1[it->player_id].bohater.push_back(*it);
					}
				}

				krainy[i].bohater.clear();

				changeKrainy(TLO, i);

				sf::String textt;
				textt = L"Nikt nie wygra³ walki o krainê, bohaterowie wrócili do rêki gracza! Kliknij lewy przycisk myszy by przejœæ dalej!";
				sf::Vector2f v1(TLO.game_obrazek[12].getPosition().x - TLO.window_x_return() / 6, TLO.window_y_return() - 5);
				TLO.set_msg(v1, textt);

				tura_pos = 5;
			}
			else
			{
				int zwyc[5] = { 0,0,0,0,0 };
				for (list <checked>::iterator it = krainy[i].bohater.begin(); it != krainy[i].bohater.end(); it++)
				{
					if (sila_boh_0 == 1)
					{
						if (it->sila == max_sila)
						{
							it->sila = 0;
						}
					}
					zwyc[it->player_id] += it->sila;
				}
				int first = 4;
				int max2 = 0;
				for (int i = 0; i < ilosc_graczy; i++)
				{
					if (zwyc[i] > max2)
					{
						max2 = zwyc[i];
						first = i;
					}
				}
				zwyc[first] = 0;

				int second = 4;
				max2 = 0;
				for (int i = 0; i < ilosc_graczy; i++)
				{
					if (zwyc[i] > max2)
					{
						max2 = zwyc[i];
						second = i;
					}
				}
				zwyc[second] = 0;
				int third = 4;
				if (ilosc_graczy >= 3)
				{

					max2 = 0;
					for (int i = 0; i < ilosc_graczy; i++)
					{
						if (zwyc[i] > max2)
						{
							max2 = zwyc[i];
							third = i;
						}
					}
					zwyc[third] = 0;
				}
				int forth = 4;
				if (ilosc_graczy >= 4)
				{
					max2 = 0;
					for (int i = 0; i < ilosc_graczy; i++)
					{
						if (zwyc[i] > max2)
						{
							max2 = zwyc[i];
							forth = i;
						}
					}
					zwyc[forth] = 0;
				}

				int pkt_skarby = 0;
				int nocka = 0;
				for (list <checked>::iterator it = krainy[i].skarb.begin(); it != krainy[i].skarb.end(); it++)
				{
					pkt_skarby += it->pkt;
					nocka += it->noc;
				}

				int punkty = 0;
				string pkt_pos;

				int pkt_0 = 0;
				int pkt_1 = 0;
				int pkt_2 = 0;
				int pkt_3 = 0;

				if (first != 4)
				{
					punkty = 0;
					pkt_pos = "";
					punkty = player1[first].pkt;
					if (kradziez == 0)
					{
						punkty += pkt_skarby + dodatk_pkt_z_potw;
					}
					if (kradziez == 1)
					{
						if (kradziez_id == first)
						{
							punkty += pkt_skarby + dodatk_pkt_z_potw;
						}
					}
					pkt_0 = punkty;
					punkty += krainy[i].first_place;
					player1[first].pkt = punkty;
					ostringstream ss;
					ss << punkty;
					pkt_pos = ss.str();
					TLO.game_text[player1[first].id_text_pkt].setString(pkt_pos);
					if (player1[first].id_text_pkt == 9)
						TLO.dopasuj(TLO.game_obrazek[9], TLO.game_text[9], 0, 0, 10, TLO.game_text[8].getGlobalBounds().height + 10);
					else if (player1[first].id_text_pkt == 15)
						TLO.dopasuj(TLO.game_obrazek[11], TLO.game_text[15], 0, 0, 10, TLO.game_text[14].getGlobalBounds().height + 10);
					else if (player1[first].id_text_pkt == 12)
						TLO.dopasuj(TLO.game_obrazek[10], TLO.game_text[12], 0, 0, 10, TLO.game_text[11].getGlobalBounds().height + 10);
					else
						TLO.dopasuj(TLO.game_obrazek[12], TLO.game_text[18], 0, 0, 10, TLO.game_text[17].getGlobalBounds().height + 10);
						
				}

				if (second != 4)
				{
					punkty = 0;
					pkt_pos = "";
					punkty = player1[second].pkt;
					if (kradziez == 1)
					{
						if (kradziez_id == second)
						{
							punkty += pkt_skarby + dodatk_pkt_z_potw;
						}
					}
					pkt_1 = punkty;
					punkty += krainy[i].second_place;
					player1[second].pkt = punkty;
					ostringstream ss2;
					ss2 << punkty;
					pkt_pos = ss2.str();
					TLO.game_text[player1[second].id_text_pkt].setString(pkt_pos);
					if (player1[second].id_text_pkt == 9)
						TLO.dopasuj(TLO.game_obrazek[9], TLO.game_text[9], 0, 0, 10, TLO.game_text[8].getGlobalBounds().height + 10);
					else if (player1[second].id_text_pkt == 15)
						TLO.dopasuj(TLO.game_obrazek[11], TLO.game_text[15], 0, 0, 10, TLO.game_text[14].getGlobalBounds().height + 10);
					else if (player1[second].id_text_pkt == 12)
						TLO.dopasuj(TLO.game_obrazek[10], TLO.game_text[12], 0, 0, 10, TLO.game_text[11].getGlobalBounds().height + 10);
					else
						TLO.dopasuj(TLO.game_obrazek[12], TLO.game_text[18], 0, 0, 10, TLO.game_text[17].getGlobalBounds().height + 10);
				}
				if (third != 4)
				{
					if (ilosc_graczy >= 3)
					{
						punkty = 0;
						pkt_pos = "";
						punkty = player1[third].pkt;
						if (kradziez == 1)
						{
							if (kradziez_id == third)
							{
								punkty += pkt_skarby + dodatk_pkt_z_potw;
							}
						}
						pkt_2 = punkty;
						punkty += krainy[i].third_place;
						player1[third].pkt = punkty;
						ostringstream ss3;
						ss3 << punkty;
						pkt_pos = ss3.str();
						TLO.game_text[player1[third].id_text_pkt].setString(pkt_pos);
						if (player1[third].id_text_pkt == 9)
							TLO.dopasuj(TLO.game_obrazek[9], TLO.game_text[9], 0, 0, 10, TLO.game_text[8].getGlobalBounds().height + 10);
						else if (player1[third].id_text_pkt == 15)
							TLO.dopasuj(TLO.game_obrazek[11], TLO.game_text[15], 0, 0, 10, TLO.game_text[14].getGlobalBounds().height + 10);
						else if (player1[third].id_text_pkt == 12)
							TLO.dopasuj(TLO.game_obrazek[10], TLO.game_text[12], 0, 0, 10, TLO.game_text[11].getGlobalBounds().height + 10);
						else
							TLO.dopasuj(TLO.game_obrazek[12], TLO.game_text[18], 0, 0, 10, TLO.game_text[17].getGlobalBounds().height + 10);
					}
				}
				if (forth != 4)
				{
					if (ilosc_graczy >= 4)
					{
						if (kradziez == 1)
						{
							if (kradziez_id == forth)
							{
								punkty = 0;
								pkt_pos = "";
								punkty = player1[forth].pkt;
								punkty += pkt_skarby + dodatk_pkt_z_potw;
								pkt_3 = punkty;
								player1[forth].pkt = punkty;
								ostringstream ss4;
								ss4 << punkty;
								pkt_pos = ss4.str();
								TLO.game_text[player1[forth].id_text_pkt].setString(pkt_pos);
								if (player1[forth].id_text_pkt == 9)
									TLO.dopasuj(TLO.game_obrazek[9], TLO.game_text[9], 0, 0, 10, TLO.game_text[8].getGlobalBounds().height + 10);
								else if (player1[forth].id_text_pkt == 15)
									TLO.dopasuj(TLO.game_obrazek[11], TLO.game_text[15], 0, 0, 10, TLO.game_text[14].getGlobalBounds().height + 10);
								else if (player1[forth].id_text_pkt == 12)
									TLO.dopasuj(TLO.game_obrazek[10], TLO.game_text[12], 0, 0, 10, TLO.game_text[11].getGlobalBounds().height + 10);
								else
									TLO.dopasuj(TLO.game_obrazek[12], TLO.game_text[18], 0, 0, 10, TLO.game_text[17].getGlobalBounds().height + 10);
							}
						}
					}
				}


				for (list <checked>::iterator it = krainy[i].potwor.begin(); it != krainy[i].potwor.end(); it++)
				{
					deck.push(*it);
				}

				krainy[i].potwor.clear();

				for (list <checked>::iterator it = krainy[i].bohater.begin(); it != krainy[i].bohater.end(); it++)
				{
					if (it->player_id > -1)
					{
						if (it->player_id == 2)
						{
							it->rotate(270);
						}
						if (it->player_id == 3)
						{
							it->rotate(90);
						}
						player1[it->player_id].bohater.push_back(*it);
					}
				}

				krainy[i].bohater.clear();
				 
				changeKrainy(TLO, i);

				ilosc_nocy += nocka;

				string pkt_noc;
				ostringstream ss5;
				ss5 << ilosc_nocy;
				pkt_noc = ss5.str();
				TLO.game_text[3].setString(pkt_noc);

				sf::String textt;
				textt = L"Walka o krainê odby³a siê. Wygrali gracze. Liczba punktów zosta³a rodzielona pomiêdzy graczy, a liczba nocy zosta³a dodana do licznika! Kliknij lewy przycisk myszy, by przejœæ dalej!";
				sf::Vector2f v1(TLO.game_obrazek[12].getPosition().x - TLO.window_x_return() / 6, TLO.window_y_return() - 5);
				TLO.set_msg(v1, textt);

				tura_pos = 5;
			}
			
		

		}

		if (walka == 0)
		{
			if (player_id + 1 == ilosc_graczy)
			{
				player_id = 0;
			}
			else
			{
				player_id++;
			}

			TLO.game_obrazek[2].setTexture(player1[player_id].tyl_bohater->getTexture(), true);

			draw_accept = 0;
			tura_pos = 0;
	
		}
	}
	
	if (tura_pos == 5)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.obrazek[0].getGlobalBounds().contains(worldPos))
		{
			if (player_id + 1 == ilosc_graczy)
			{
				player_id = 0;
			}
			else
			{
				player_id++;
			}

			TLO.game_obrazek[2].setTexture(player1[player_id].tyl_bohater->getTexture(), true);
			tura_pos = 0;
			draw_accept = 0;
		}

	}

	if (tura_pos == 6)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.obrazek[0].getGlobalBounds().contains(worldPos))
		{
			if (player_id + 1 == ilosc_graczy)
			{
				player_id = 0;
			}
			else
			{
				player_id++;
			}

			TLO.game_obrazek[2].setTexture(player1[player_id].tyl_bohater->getTexture(), true);
			draw_accept = 0;
			tura_pos = 0;
		}
	}
	a++;

}

void game::set_tura_pos(int a)
{
	if (a == 1)
	{
		Sleep(5000);
		tura_pos = 4;
	}
}

void game::Event_Krainy(background &TLO, kraina &krains, sf::Vector2f worldPos)
{
	for (list <checked>::iterator it = krains.bohater.begin(); it != krains.bohater.end(); it++)
	{
		if (it->getGlobalBounds().contains(worldPos) && (is_mouse == 0 || it->is_mouse == 1) && (it->drukuj_ksztalt == 1))
		{
			it->is_mouse = 1;
			for (int i = 0; it->getSize().x <= TLO.window_x_return() / scale_div; i++)
			{
				it->setSize(sf::Vector2f(it->getSize().x + 2.0f * i, it->getSize().y + 3.0f*i));
			}

			it->priorytet = 1;

		}
		if (!it->getGlobalBounds().contains(worldPos) || it->is_mouse == 0)
		{
			it->setSize(sf::Vector2f(stand_x, stand_y));
			it->priorytet = 0;
			is_draw_vip = 0;
			it->is_mouse = 0;
		}
	}

	for (list <checked>::iterator it = krains.potwor.begin(); it != krains.potwor.end(); it++)
	{
		if (it->getGlobalBounds().contains(worldPos) && (is_mouse == 0 || it->is_mouse == 1) && (it->drukuj_ksztalt == 1))
		{
			it->is_mouse = 1;
			for (int i = 0; it->getSize().x <= TLO.window_x_return() / scale_div; i++)
			{
				it->setSize(sf::Vector2f(it->getSize().x + 2.0f * i, it->getSize().y + 3.0f*i));
			}

			it->priorytet = 1;

		}
		if (!it->getGlobalBounds().contains(worldPos) || it->is_mouse == 0)
		{
			it->setSize(sf::Vector2f(stand_x, stand_y));
			it->priorytet = 0;
			is_draw_vip = 0;
			it->is_mouse = 0;
		}
	}

}

void game::dynamic_position(checked obrazek, sf::Vector2f pkt1, sf::Vector2f pkt2)
{
	dynamic_pos_ob = obrazek;
	dynamic_pos_ob.setPosition(sf::Vector2f(pkt1.x, pkt1.y));

	dynamic_pos_drukuj = 1;
	float a, b, y;
	a = (pkt2.y - pkt1.y) / (pkt2.x - pkt1.x);
	b = pkt1.y - a*pkt1.x;

	if (pkt1.x < pkt2.x)
	{
		for (float x = pkt1.x; x < pkt2.x; x += 0.00005f)
		{
			y = a*x + b;
			dynamic_pos_ob.setPosition(sf::Vector2f(x, y));
		}
	}

	if (pkt1.x > pkt2.x)
	{
		for (float x = pkt1.x; x > pkt2.x; x -= 0.00005f)
		{
			y = a*x + b;
			dynamic_pos_ob.setPosition(sf::Vector2f(x, y));
		}
	}
	dynamic_pos_drukuj = 0;
}

void game::Event_scan(sf::RenderWindow * app, background & TLO, sf::Event Event, sf::Vector2f worldPos)
{
	if (ilosc_nocy < 5 && koniec == 0)
	{
		is_mouse_Exist();
		if (ilosc_graczy >= 1)
		{
			Event_Player(TLO, player1[0], worldPos, 0, player_id);
		}
		if (ilosc_graczy >= 2)
		{
			Event_Player(TLO, player1[1], worldPos, 1, player_id);
		}
		if (ilosc_graczy >= 3)
		{
			Event_Player(TLO, player1[2], worldPos, 2, player_id);
		}
		if (ilosc_graczy >= 4)
		{
			Event_Player(TLO, player1[3], worldPos, 3, player_id);
		}

		Event_Krainy(TLO, krainy[0], worldPos);
		Event_Krainy(TLO, krainy[1], worldPos);
		Event_Krainy(TLO, krainy[2], worldPos);

		if (ilosc_graczy >= 3)
		{
			Event_Krainy(TLO, krainy[3], worldPos);
		}
		if (ilosc_graczy == 4)
		{
			Event_Krainy(TLO, krainy[4], worldPos);
		}

		if (pomoc_active == 1)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.game_obrazek[14].getGlobalBounds().contains(worldPos))
			{
				pomoc_active = 0;
			}
		}
		if (pomoc_active == 0)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.game_obrazek[1].getGlobalBounds().contains(worldPos))
			{
				pomoc_active = 1;
			}
		}
	}
	else
	{
		if (koniec == 0)
		{
			sf::String tekst_kon;
			tekst_kon = L"Gra zosta³a zakoñczona! Odpowiednia liczba nocy zosta³a ju¿ zebrana!";
			TLO.game_text[20].setString(tekst_kon);
			TLO.dopasuj(TLO.game_obrazek[16], TLO.game_text[20], 0, 0, 10, 0);
			koniec = 1;
		}
	}
}

bool game::Rand_check(int liczba, int tab[], int ile)
{
	if (ile <= 0)
		return false;

	int i = 0;
	do
	{
		if (tab[i] == liczba)
			return true;

		i++;
	} while (i < ile);

	return false;
}

int game::Rand(int max)
{
	return rand() % max;
}

void game::Create_Deck(background * TLO)
{

	tmp = new checked[54];
	memcpy(tmp, TLO->stwor, 13 * sizeof *TLO->stwor);

	for (int i = 13; i <= 23; i++)
	{
		tmp[i] = TLO->stwor[0];
	}

	for (int i = 24; i <= 32; i++)
	{
		tmp[i] = TLO->stwor[1];
	}

	for (int i = 33; i <= 37; i++)
	{
		tmp[i] = TLO->stwor[2];
	}

	for (int i = 38; i <= 41; i++)
	{
		tmp[i] = TLO->stwor[3];
	}

	for (int i = 42; i <= 44; i++)
	{
		tmp[i] = TLO->stwor[4];
	}

	for (int i = 45; i <= 46; i++)
	{
		tmp[i] = TLO->stwor[5];
	}


	tmp[47] = TLO->stwor[6];
	tmp[48] = TLO->stwor[7];
	tmp[49] = TLO->stwor[8];
	tmp[50] = TLO->stwor[9];
	tmp[51] = TLO->stwor[10];
	tmp[52] = TLO->stwor[11];
	tmp[53] = TLO->stwor[12];

	talia = new checked[54];

	srand(unsigned int(time(0)));
	int wylosowane[54];
	int wylosowanych = 0;

	while (wylosowanych < 54)
	{
		int liczba = Rand(54);
		if (Rand_check(liczba, wylosowane, wylosowanych) == false)
		{
			wylosowane[wylosowanych] = liczba;
			talia[wylosowanych] = tmp[liczba];
			deck.push(talia[wylosowanych]);
			wylosowanych++;
		}
	}

	delete[] TLO->stwor;
	TLO->stwor = new checked[54];
	memcpy(TLO->stwor, talia, 54 * sizeof *talia);
}

void game::Create_Skarby(background * TLO)
{
	tmp2 = new checked[20];
	memcpy(tmp2, TLO->skarb, 8 * sizeof *TLO->skarb);

	for (int i = 8; i <= 12; i++)
	{
		tmp2[i] = TLO->skarb[5];
	}
	for (int i = 13; i <= 16; i++)
	{
		tmp2[i] = TLO->skarb[6];
	}
	for (int i = 17; i <= 19; i++)
	{
		tmp2[i] = TLO->skarb[7];
	}

	skarby = new checked[20];

	srand(unsigned int(time(0)));
	int wylosowane[20];
	int wylosowanych = 0;

	while (wylosowanych < 20)
	{
		int liczba = Rand(20);
		if (Rand_check(liczba, wylosowane, wylosowanych) == false)
		{
			wylosowane[wylosowanych] = liczba;
			skarby[wylosowanych] = tmp2[liczba];
			skarb.push(skarby[wylosowanych]);
			wylosowanych++;
		}
	}

	delete[] TLO->skarb;
	TLO->skarb = new checked[20];
	memcpy(TLO->skarb, skarby, 20 * sizeof *skarby);

}

void game::setPlayer(background & TLO)
{
	int pos = 0;
	sf::String name;

	for (int i = 0; i < tab_human_ilosc; i++)
	{
		if (tab_human[i] == 10)
		{
			if (pos == 0)
			{
				TLO.game_obrazek[2].setTexture(&TLO.tekstura[5], true);
			}
			for (int j = 0; j <= 5; j++)
			{
				player1[pos].tyl_bohater[j] = TLO.obrazek[2];
			}

			if (pos == 2)
			{
				for (int j = 0; j <= 5; j++)
				{
					TLO.szary[j].rotate(270);
					player1[pos].tyl_bohater[j].rotate(270);
				}
			}
			if (pos == 3)
			{
				for (int j = 0; j <= 5; j++)
				{
					TLO.szary[j].rotate(90);
					player1[pos].tyl_bohater[j].rotate(90);
				}
			}
			name = names[0];
			for (int j = 0; j <= 5; j++)
			{
				TLO.szary[j].player_id = pos;
				player1[pos].bohater.push_back(TLO.szary[j]);
			}
		}
		else if (tab_human[i] == 12)
		{
			if (pos == 0)
			{
				TLO.game_obrazek[2].setTexture(&TLO.tekstura[6], true);
			}
			for (int j = 0; j <= 5; j++)
			{
				player1[pos].tyl_bohater[j] = TLO.obrazek[3];
			}

			if (pos == 2)
			{
				for (int j = 0; j <= 5; j++)
				{
					TLO.niebieski[j].rotate(270);
					player1[pos].tyl_bohater[j].rotate(270);
				}
			}
			if (pos == 3)
			{
				for (int j = 0; j <= 5; j++)
				{
					TLO.niebieski[j].rotate(90);
					player1[pos].tyl_bohater[j].rotate(90);
				}
			}
			name = names[1];
			for (int j = 0; j <= 5; j++)
			{
				TLO.niebieski[j].player_id = pos;
				player1[pos].bohater.push_back(TLO.niebieski[j]);
			}
		}
		else if (tab_human[i] == 14)
		{
			if (pos == 0)
			{
				TLO.game_obrazek[2].setTexture(&TLO.tekstura[7], true);
			}
			for (int j = 0; j <= 5; j++)
			{
				player1[pos].tyl_bohater[j] = TLO.obrazek[4];
			}

			if (pos == 2)
			{
				for (int j = 0; j <= 5; j++)
				{
					TLO.rozowy[j].rotate(270);
					player1[pos].tyl_bohater[j].rotate(270);
				}
			}
			if (pos == 3)
			{
				for (int j = 0; j <= 5; j++)
				{
					TLO.rozowy[j].rotate(90);
					player1[pos].tyl_bohater[j].rotate(90);
				}
			}
			name = names[2];
			for (int j = 0; j <= 5; j++)
			{
				TLO.rozowy[j].player_id = pos;
				player1[pos].bohater.push_back(TLO.rozowy[j]);
			}
		}
		else if (tab_human[i] == 16)
		{
			if (pos == 0)
			{
				TLO.game_obrazek[2].setTexture(&TLO.tekstura[8], true);
			}
			for (int j = 0; j <= 5; j++)
			{
				player1[pos].tyl_bohater[j] = TLO.obrazek[5];
			}

			if (pos == 2)
			{
				for (int j = 0; j <= 5; j++)
				{
					TLO.zielony[j].rotate(270);
					player1[pos].tyl_bohater[j].rotate(270);
				}
			}
			if (pos == 3)
			{
				for (int j = 0; j <= 5; j++)
				{
					TLO.zielony[j].rotate(90);
					player1[pos].tyl_bohater[j].rotate(90);
				}
			}
			name = names[3];
			for (int j = 0; j <= 5; j++)
			{
				TLO.zielony[j].player_id = pos;
				player1[pos].bohater.push_back(TLO.zielony[j]);
			}
		}

		if (pos == 0)
		{
			player1[pos].id_text_pkt = 9;
		}

		if (pos == 1)
		{
			player1[pos].id_text_pkt = 12;
		}
		if (pos == 2)
		{
			player1[pos].id_text_pkt = 15;
		}
		if (pos == 3)
		{
			player1[pos].id_text_pkt = 18;
		}
		player1[pos].human = 1;
		player1[pos].name = name;
		player1[pos].pkt = 0;
		player1[pos].id = pos;

		SetPlayer_Skin(TLO, pos, name);
		Set_Potwor(pos, TLO);
		pos++;
	}

	for (int i = 0; i < tab_comp_ilosc; i++)
	{
		if (tab_comp[i] == 10)
		{
			for (int j = 0; j <= 5; j++)
			{
				player1[pos].tyl_bohater[j] = TLO.obrazek[2];
			}
			if (pos == 2)
			{
				for (int j = 0; j <= 5; j++)
				{
					TLO.szary[j].rotate(270);
					player1[pos].tyl_bohater[j].rotate(270);
				}
			}
			if (pos == 3)
			{
				for (int j = 0; j <= 5; j++)
				{
					TLO.szary[j].rotate(90);
					player1[pos].tyl_bohater[j].rotate(90);
				}
			}
			name = names[0];
			for (int j = 0; j <= 5; j++)
			{
				TLO.szary[j].player_id = pos;
				player1[pos].bohater.push_back(TLO.szary[j]);
			}
		}
		else if (tab_comp[i] == 12)
		{
			for (int j = 0; j <= 5; j++)
			{
				player1[pos].tyl_bohater[j] = TLO.obrazek[3];
			}
			if (pos == 2)
			{
				for (int j = 0; j <= 5; j++)
				{
					TLO.niebieski[j].rotate(270);
					player1[pos].tyl_bohater[j].rotate(270);
				}
			}
			if (pos == 3)
			{
				for (int j = 0; j <= 5; j++)
				{
					TLO.niebieski[j].rotate(90);
					player1[pos].tyl_bohater[j].rotate(90);
				}
			}
			name = names[1];
			for (int j = 0; j <= 5; j++)
			{
				TLO.niebieski[j].player_id = pos;
				player1[pos].bohater.push_back(TLO.niebieski[j]);
			}
		}
		else if (tab_comp[i] == 14)
		{
			for (int j = 0; j <= 5; j++)
			{
				player1[pos].tyl_bohater[j] = TLO.obrazek[4];
			}
			if (pos == 2)
			{
				for (int j = 0; j <= 5; j++)
				{
					TLO.rozowy[j].rotate(270);
					player1[pos].tyl_bohater[j].rotate(270);
				}
			}
			if (pos == 3)
			{
				for (int j = 0; j <= 5; j++)
				{
					TLO.rozowy[j].rotate(90);
					player1[pos].tyl_bohater[j].rotate(90);
				}
			}
			name = names[2];
			for (int j = 0; j <= 5; j++)
			{
				TLO.rozowy[j].player_id = pos;
				player1[pos].bohater.push_back(TLO.rozowy[j]);
			}
		}
		else if (tab_comp[i] == 16)
		{
			for (int j = 0; j <= 5; j++)
			{
				player1[pos].tyl_bohater[j] = TLO.obrazek[5];
			}
			if (pos == 2)
			{
				for (int j = 0; j <= 5; j++)
				{
					TLO.zielony[j].rotate(270);
					player1[pos].tyl_bohater[j].rotate(270);
				}
			}
			if (pos == 3)
			{
				for (int j = 0; j <= 5; j++)
				{
					TLO.zielony[j].rotate(90);
					player1[pos].tyl_bohater[j].rotate(90);
				}
			}
			name = names[3];
			for (int j = 0; j <= 5; j++)
			{
				TLO.zielony[j].player_id = pos;
				player1[pos].bohater.push_back(TLO.zielony[j]);
			}
		}

		name +="_B";
		player1[pos].human = 0;
		player1[pos].name = name;
		player1[pos].pkt = 0;
		player1[pos].id = pos;

		if (pos == 0)
		{
			player1[pos].id_text_pkt = 9;
		}

		if (pos == 1)
		{
			player1[pos].id_text_pkt = 12;
		}
		if (pos == 2)
		{
			player1[pos].id_text_pkt = 15;
		}
		if (pos == 3)
		{
			player1[pos].id_text_pkt = 18;
		}

		SetPlayer_Skin(TLO, pos, name);
		Set_Potwor(pos, TLO);
		pos++;
	}
}

void game::SetPlayer_Skin(background & TLO, int n, sf::String &name)
{
	if (n == 0)
	{
		TLO.game_obrazek[9].setSize(sf::Vector2f(TLO.window_x_return() / 20.0f, TLO.window_y_return() / 10.0f));
		TLO.game_obrazek[9].setFillColor(sf::Color(255, 255, 255, 255));
		TLO.game_obrazek[9].setOutlineColor(sf::Color::Black);
		TLO.game_obrazek[9].setOutlineThickness(2.0f);
		TLO.game_obrazek[9].setPosition(sf::Vector2f(3.0f, TLO.window_y_return() - TLO.game_obrazek[9].getGlobalBounds().height));

		TLO.game_text[7].setFont(TLO.font[0]);
		TLO.game_text[7].setString(name);
		TLO.game_text[7].setFillColor(sf::Color::Black);
		TLO.game_text[7].setStyle(sf::Text::Bold);
		TLO.game_text[7].setPosition(0.0f, 0.0f);
		TLO.dopasuj(TLO.game_obrazek[9], TLO.game_text[7], TLO.game_obrazek[9].getPosition().x, 0, 0, 0);
		TLO.game_text[7].setPosition(sf::Vector2f(TLO.game_text[7].getPosition().x, TLO.game_obrazek[9].getPosition().y - TLO.game_text[7].getGlobalBounds().height * 2));

		TLO.game_text[8] = TLO.game_text[7];
		TLO.game_text[8].setString("PUNKTY");
		TLO.game_text[8].setPosition(0.0f, 0.0f);
		TLO.dopasuj(TLO.game_obrazek[9], TLO.game_text[8], 0, TLO.game_obrazek[9].getPosition().y + 3, 0, 0);

		TLO.game_text[9] = TLO.game_text[7];
		TLO.game_text[9].setString("0");
		TLO.game_text[9].setPosition(0.0f, 0.0f);
		TLO.dopasuj(TLO.game_obrazek[9], TLO.game_text[9], 0, 0, 10, TLO.game_text[8].getGlobalBounds().height + 10);
	}
	else if (n == 1)
	{
		TLO.game_obrazek[11] = TLO.game_obrazek[9];
		TLO.game_obrazek[11].setPosition(sf::Vector2f(TLO.game_obrazek[0].getPosition().x - TLO.game_obrazek[11].getGlobalBounds().width - 3, 20));

		TLO.game_text[13] = TLO.game_text[7];
		TLO.game_text[13].setString(name);
		TLO.game_text[13].setPosition(0.0f, 0.0f);
		TLO.dopasuj(TLO.game_obrazek[11], TLO.game_text[13], TLO.game_obrazek[11].getPosition().x, 0, 0, 0);
		TLO.game_text[13].setPosition(sf::Vector2f(TLO.game_text[13].getPosition().x, TLO.game_obrazek[11].getPosition().y - TLO.game_text[13].getGlobalBounds().height * 2));

		TLO.game_text[14] = TLO.game_text[7];
		TLO.game_text[14].setString("PUNKTY");
		TLO.game_text[14].setPosition(0.0f, 0.0f);
		TLO.dopasuj(TLO.game_obrazek[11], TLO.game_text[14], 0, TLO.game_obrazek[11].getPosition().y + 3, 0, 0);

		TLO.game_text[15] = TLO.game_text[7];
		TLO.game_text[15].setString("0");
		TLO.game_text[15].setPosition(0.0f, 0.0f);
		TLO.dopasuj(TLO.game_obrazek[11], TLO.game_text[15], 0, 0, 10, TLO.game_text[14].getGlobalBounds().height + 10);
	}
	else if (n == 2)
	{
		TLO.game_obrazek[10] = TLO.game_obrazek[9];
		TLO.game_obrazek[10].setPosition(sf::Vector2f(3.0f, 20));

		TLO.game_text[10] = TLO.game_text[7];
		TLO.game_text[10].setString(name);
		TLO.game_text[10].setPosition(0.0f, 0.0f);
		TLO.dopasuj(TLO.game_obrazek[10], TLO.game_text[10], TLO.game_obrazek[10].getPosition().x, 0, 0, 0);
		TLO.game_text[10].setPosition(sf::Vector2f(TLO.game_text[10].getPosition().x, TLO.game_obrazek[10].getPosition().y - TLO.game_text[10].getGlobalBounds().height * 2));

		TLO.game_text[11] = TLO.game_text[7];
		TLO.game_text[11].setString("PUNKTY");;
		TLO.game_text[11].setPosition(0.0f, 0.0f);
		TLO.dopasuj(TLO.game_obrazek[10], TLO.game_text[11], 0, TLO.game_obrazek[10].getPosition().y + 3, 0, 0);

		TLO.game_text[12] = TLO.game_text[7];
		TLO.game_text[12].setString("0");
		TLO.game_text[12].setPosition(0.0f, 0.0f);
		TLO.dopasuj(TLO.game_obrazek[10], TLO.game_text[12], 0, 0, 10, TLO.game_text[11].getGlobalBounds().height + 10);

	}
	else
	{
		TLO.game_obrazek[12] = TLO.game_obrazek[9];
		TLO.game_obrazek[12].setPosition(sf::Vector2f(TLO.game_obrazek[0].getPosition().x - TLO.game_obrazek[11].getGlobalBounds().width - 3, TLO.window_y_return() - TLO.game_obrazek[9].getGlobalBounds().height));

		TLO.game_text[16] = TLO.game_text[7];
		TLO.game_text[16].setString(name);
		TLO.game_text[16].setPosition(0.0f, 0.0f);
		TLO.dopasuj(TLO.game_obrazek[12], TLO.game_text[16], TLO.game_obrazek[12].getPosition().x, 0, 0, 0);
		TLO.game_text[16].setPosition(sf::Vector2f(TLO.game_text[16].getPosition().x, TLO.game_obrazek[12].getPosition().y - TLO.game_text[16].getGlobalBounds().height * 2));

		TLO.game_text[17] = TLO.game_text[7];
		TLO.game_text[17].setString("PUNKTY");
		TLO.game_text[17].setPosition(0.0f, 0.0f);
		TLO.dopasuj(TLO.game_obrazek[12], TLO.game_text[17], 0, TLO.game_obrazek[12].getPosition().y + 3, 0, 0);

		TLO.game_text[18] = TLO.game_text[7];
		TLO.game_text[18].setString("0");
		TLO.game_text[18].setPosition(0.0f, 0.0f);
		TLO.dopasuj(TLO.game_obrazek[12], TLO.game_text[18], 0, 0, 10, TLO.game_text[17].getGlobalBounds().height + 10);
	}

}

void game::Set_Potwor(int pos, background &TLO)
{
	int a = 0;
	while (player1[pos].ilosc_potworow != 5)
	{
		player1[pos].tyl_potwor[a] = TLO.game_obrazek[15];
		if (pos == 2)
		{
			player1[pos].tyl_potwor[a].setRotation(270);
			deck.front().rotate(270);
		}
		if (pos == 3)
		{
			player1[pos].tyl_potwor[a].setRotation(90);
			deck.front().rotate(90);
		}

		player1[pos].potwor.push_back(deck.front());
		deck.pop();
		player1[pos].ilosc_potworow++;
		a++;
	}
}

void game::setKrainy(background & TLO)
{
	krainy[0].setKraina(TLO.kraina[0], TLO.kraina[1]);
	krainy[0].img.setPosition(sf::Vector2f(TLO.window_x_return()/2 - krainy[0].img.getGlobalBounds().width/2 - TLO.game_obrazek[0].getGlobalBounds().width/2, player1[1].bohater.front().getPosition().y + stand_y + 5));
	
	tyl_skarb[0].setSize(sf::Vector2f(krainy[0].img.getGlobalBounds().height + 8, krainy[0].img.getGlobalBounds().width / 2));
	tyl_skarb[0].setPosition(0.0f, 0.0f);
	tyl_skarb[0].setTexture(&TLO.tekstura[47], true);
	tyl_skarb[0].rotate(90);
	tyl_skarb[0].setPosition(krainy[0].img.getPosition().x + krainy[0].img.getGlobalBounds().width - tyl_skarb[0].getGlobalBounds().width / 2, krainy[0].img.getPosition().y - 4);
	
	krainy[1].setKraina(TLO.kraina[2], TLO.kraina[3]);
	krainy[1].img.setPosition(sf::Vector2f(krainy[0].img.getPosition().x, krainy[0].img.getPosition().y+ krainy[0].img.getGlobalBounds().height + 2));

	tyl_skarb[1].setSize(sf::Vector2f(krainy[1].img.getGlobalBounds().height + 8, krainy[1].img.getGlobalBounds().width / 2));
	tyl_skarb[1].setPosition(0.0f, 0.0f);
	tyl_skarb[1].setTexture(&TLO.tekstura[47], true);
	tyl_skarb[1].rotate(90);
	tyl_skarb[1].setPosition(krainy[1].img.getPosition().x + krainy[1].img.getGlobalBounds().width - tyl_skarb[1].getGlobalBounds().width / 2, krainy[1].img.getPosition().y - 4);

	krainy[2].setKraina(TLO.kraina[4], TLO.kraina[5]);
	krainy[2].img.setPosition(sf::Vector2f(krainy[0].img.getPosition().x, krainy[1].img.getPosition().y + krainy[1].img.getGlobalBounds().height + 2));
	
	tyl_skarb[2].setSize(sf::Vector2f(krainy[2].img.getGlobalBounds().height + 8, krainy[2].img.getGlobalBounds().width / 2));
	tyl_skarb[2].setPosition(0.0f, 0.0f);
	tyl_skarb[2].setTexture(&TLO.tekstura[47], true);
	tyl_skarb[2].rotate(90);
	tyl_skarb[2].setPosition(krainy[2].img.getPosition().x + krainy[2].img.getGlobalBounds().width - tyl_skarb[2].getGlobalBounds().width / 2, krainy[2].img.getPosition().y - 4);

	if (ilosc_graczy >= 2 && ilosc_graczy <= 3)
	{
		krainy[3].setKraina(TLO.kraina[6], TLO.kraina[7]);
		krainy[3].img.setPosition(sf::Vector2f(krainy[0].img.getPosition().x, krainy[2].img.getPosition().y + krainy[2].img.getGlobalBounds().height + 2));
		
		tyl_skarb[3].setSize(sf::Vector2f(krainy[3].img.getGlobalBounds().height + 8, krainy[3].img.getGlobalBounds().width / 2));
		tyl_skarb[3].setPosition(0.0f, 0.0f);
		tyl_skarb[3].setTexture(&TLO.tekstura[47], true);
		tyl_skarb[3].rotate(90);
		tyl_skarb[3].setPosition(krainy[3].img.getPosition().x + krainy[3].img.getGlobalBounds().width - tyl_skarb[3].getGlobalBounds().width / 2, krainy[3].img.getPosition().y - 4);

	}
	if (ilosc_graczy == 4)
	{
		krainy[3].setKraina(TLO.kraina[8], TLO.kraina[9]);
		krainy[3].img.setPosition(sf::Vector2f(krainy[0].img.getPosition().x, krainy[2].img.getPosition().y + krainy[2].img.getGlobalBounds().height + 2));
		
		tyl_skarb[3].setSize(sf::Vector2f(krainy[3].img.getGlobalBounds().height + 8, krainy[3].img.getGlobalBounds().width / 2));
		tyl_skarb[3].setPosition(0.0f, 0.0f);
		tyl_skarb[3].setTexture(&TLO.tekstura[47], true);
		tyl_skarb[3].rotate(90);
		tyl_skarb[3].setPosition(krainy[3].img.getPosition().x + krainy[3].img.getGlobalBounds().width - tyl_skarb[3].getGlobalBounds().width / 2, krainy[3].img.getPosition().y - 4);

		krainy[4].setKraina(TLO.kraina[10], TLO.kraina[11]);
		krainy[4].img.setPosition(sf::Vector2f(krainy[0].img.getPosition().x, krainy[3].img.getPosition().y + krainy[3].img.getGlobalBounds().height + 2));
	
		tyl_skarb[4].setSize(sf::Vector2f(krainy[4].img.getGlobalBounds().height + 8, krainy[4].img.getGlobalBounds().width / 2));
		tyl_skarb[4].setPosition(0.0f, 0.0f);
		tyl_skarb[4].setTexture(&TLO.tekstura[47], true);
		tyl_skarb[4].rotate(90);
		tyl_skarb[4].setPosition(krainy[4].img.getPosition().x + krainy[4].img.getGlobalBounds().width - tyl_skarb[4].getGlobalBounds().width / 2, krainy[4].img.getPosition().y - 4);

	}

	setKrainy2(TLO, krainy[0]);
	setKrainy2(TLO, krainy[1]);
	setKrainy2(TLO, krainy[2]);

	if (ilosc_graczy >= 3)
	{
		setKrainy2(TLO, krainy[3]);

	}
	if (ilosc_graczy == 4)
	{
		setKrainy2(TLO, krainy[4]);
	}

	sf::Vector2f pkt1(50, 10);
	sf::Vector2f pkt2(761, 450);


}

void game::setKrainy2(background &TLO, kraina &krainy, int only_setpos)
{
	int a = 0;
	if (only_setpos != 1)
	{
		while (a != krainy.max_ilosc_boh)
		{
			krainy.bohater.push_front(TLO.game_obrazek[13]);
			a++;
		}

		a = 0;
		while (a != krainy.max_ilosc_stwor)
		{
			krainy.potwor.push_front(TLO.game_obrazek[13]);
			a++;
		}

		if (!skarb.empty())
		{
			a = 0;
			while (a != krainy.max_ilosc_skarb)
			{
				krainy.skarb.push_front(skarb.front());
				skarb.pop();
				a++;
			}
		}
	}


	a = 0;
	for (list <checked>::iterator it = krainy.bohater.begin(); it != krainy.bohater.end(); it++)
	{
		it->setPosition(krainy.img.getPosition().x + krainy.img.getGlobalBounds().width + 10 + a*stand_x, krainy.img.getPosition().y + krainy.img.getGlobalBounds().height / 2 - krainy.bohater.front().getGlobalBounds().height / 2);
		it->setSize(sf::Vector2f(stand_x, stand_y));
		a++;
	}

	a = 1;
	for (list <checked>::iterator it = krainy.potwor.begin(); it != krainy.potwor.end(); it++)
	{
		it->setPosition(krainy.img.getPosition().x - 10 - a*stand_x, krainy.img.getPosition().y + krainy.img.getGlobalBounds().height / 2 - krainy.potwor.front().getGlobalBounds().height / 2);
		it->setSize(sf::Vector2f(stand_x, stand_y));
		a++;
	}

}

void game::changeKrainy(background & TLO, int id_kraina)
{
	if (id_kraina == 0)
	{
		krainy[0].setKraina(TLO.kraina[0], TLO.kraina[1]);
		krainy[0].img.setPosition(sf::Vector2f(TLO.window_x_return() / 2 - krainy[0].img.getGlobalBounds().width / 2 - TLO.game_obrazek[0].getGlobalBounds().width / 2, player1[1].bohater.front().getPosition().y + stand_y + 5));

	
		setKrainy2(TLO, krainy[0]);
	}

	if (id_kraina == 1)
	{
		krainy[1].setKraina(TLO.kraina[2], TLO.kraina[3]);
		krainy[1].img.setPosition(sf::Vector2f(krainy[0].img.getPosition().x, krainy[0].img.getPosition().y + krainy[0].img.getGlobalBounds().height + 2));



		setKrainy2(TLO, krainy[1]);
	}

	if (id_kraina == 2)
	{
		krainy[2].setKraina(TLO.kraina[4], TLO.kraina[5]);
		krainy[2].img.setPosition(sf::Vector2f(krainy[0].img.getPosition().x, krainy[1].img.getPosition().y + krainy[1].img.getGlobalBounds().height + 2));

		setKrainy2(TLO, krainy[2]);
	}
	if (id_kraina == 3)
	{
		if (ilosc_graczy >= 2 && ilosc_graczy <= 3)
		{
			krainy[3].setKraina(TLO.kraina[6], TLO.kraina[7]);
			krainy[3].img.setPosition(sf::Vector2f(krainy[0].img.getPosition().x, krainy[2].img.getPosition().y + krainy[2].img.getGlobalBounds().height + 2));
			setKrainy2(TLO, krainy[3]);
		}
	}
	if (id_kraina == 3)
	{
		if (ilosc_graczy == 4)
		{
			krainy[3].setKraina(TLO.kraina[8], TLO.kraina[9]);
			krainy[3].img.setPosition(sf::Vector2f(krainy[0].img.getPosition().x, krainy[2].img.getPosition().y + krainy[2].img.getGlobalBounds().height + 2));
			setKrainy2(TLO, krainy[3]);

			krainy[4].setKraina(TLO.kraina[10], TLO.kraina[11]);
			krainy[4].img.setPosition(sf::Vector2f(krainy[0].img.getPosition().x, krainy[3].img.getPosition().y + krainy[3].img.getGlobalBounds().height + 2));
			setKrainy2(TLO, krainy[4]);
		}
	}
}