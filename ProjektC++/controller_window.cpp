#include "controller_window.h"



controller_window::controller_window()
{
	window_id = 1; //1 - okno g³owne gry
}


controller_window::~controller_window()
{

}

void controller_window::SetWindow_ID(int a)
{
	window_id = a;
}

int controller_window::GetWindow_ID() const
{
	return window_id;
}

int controller_window::GetWindow(sf::RenderWindow* app, background & TLO)
{

	int tab[10][2] = { { 800,600 },{ 1024,768 },{ 1280,600 },{ 1280,720 },{ 1280,768 },{ 1280,800 },{ 1360,768 },{ 1366,768 },{ 1440,900 },{ 1600, 900 } };
	int a=0;
	for (int i = 0; i < 10; i++)
	{
		if (tab[i][0] == TLO.window_x_return() && tab[i][1] == TLO.window_y_return())
		{
			a = 1;
		}
	}

	if (a == 0)
	{
		return 0;
	}

	if (GetWindow_ID() == 1)
	{
		TLO.tlo_glowne(app);

	}
	else if (GetWindow_ID() == 3)
	{
		TLO.settings();
	}
	else if (GetWindow_ID() == 4)
	{
		TLO.wyjscie();

	}
	else if (GetWindow_ID() == 5)
	{
		TLO.game_setup();
	}
	else if (GetWindow_ID() == 6)
	{
		TLO.game();
	}
	return 1;
}

void generuj(sf::RenderWindow* app, background & TLO, controller_window & win)
{
	int a = win.GetWindow_ID();
	if (a == 1 || a == 3 || a == 4)
	{
		for (int i = 0; i <= 4; i++)
		{
			app->draw(TLO.obrazek[i]);
		}
		for (int i = 0; i <= 3; i++)
		{
			app->draw(TLO.tekst[i]);
		}
		if (a == 4)
		{
			for (int i = 0; i <= 3; i++)
			{
				app->draw(TLO.ksztalt[i]);
			}
			app->draw(TLO.tekst[5]);
			app->draw(TLO.tekst[6]);
			app->draw(TLO.tekst[7]);
		}
		if (a == 3)
		{
			app->draw(TLO.ksztalt[0]);
			app->draw(TLO.ksztalt[1]);
			app->draw(TLO.ksztalt[2]);
			app->draw(TLO.ksztalt[3]);
			for (int i = 5; i <= 21; i++)
			{
				app->draw(TLO.tekst[i]);
			}
			for (int i = 6; i <= 17; i++)
			{
				app->draw(TLO.obrazek[i]);
			}
		}
	}
	if (a == 5)
	{
		app->draw(TLO.obrazek[0]);
		for (int i = 2; i <= 19; i++)
		{
			app->draw(TLO.obrazek[i]);
		}
		app->draw(TLO.ksztalt[1]);
		for (int i = 0; i <= 17; i++)
		{
			app->draw(TLO.tekst[i]);
		}
	}
	if (a == 6)
	{
		app->draw(TLO.obrazek[0]);
		for (int i = 0; i <= 12; i++)
		{
			app->draw(TLO.game_obrazek[i]);
		}

		for (int i = 0; i <= 18; i++)
		{
			app->draw(TLO.game_text[i]);
		}
	}
	TLO.Show_Message(app);
}