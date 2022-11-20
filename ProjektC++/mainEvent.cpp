#include "mainEvent.h"


mainEvent::mainEvent()
{
}


mainEvent::~mainEvent()
{
}

void mainEvent::EventController(sf::RenderWindow* app, background &TLO, controller_window &Window, game &GRA)
{
	while (app->pollEvent(Event))
	{
		pixelPos = sf::Mouse::getPosition(*app);
		worldPos = app->mapPixelToCoords(pixelPos);
		Event_ResetShowMessage(app, TLO, Window);
		if (Window.GetWindow_ID() == 1)
		{
			Event_Menu(app, TLO, Window);
		}
		else if (Window.GetWindow_ID() == 3)
		{
			Event_Settings(app, TLO, Window);
		}
		else if (Window.GetWindow_ID() == 4)
		{
			Event_Close(app, TLO, Window);
		}
		else if (Window.GetWindow_ID() == 5)
		{
			Event_GameSetup(app, TLO, Window, GRA);
		}
		else if (Window.GetWindow_ID() == 6)
		{
			Event_Game(app, TLO, Window, GRA);
		}
	}
}

void mainEvent::Event_ResetShowMessage(sf::RenderWindow * app, background & TLO, controller_window & Window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.obrazek[0].getGlobalBounds().contains(worldPos) && TLO.reset_showmsg == 1)
	{
		TLO.message.setString("");
		TLO.message_board.setSize(sf::Vector2f(0, 0));
		TLO.reset_showmsg = 0;
		TLO.timer_started = 0;
	}

	if (TLO.timer_started == 0)
	{
		TLO.timer_end = chrono::steady_clock::now();
		std::thread t2(&background::Timer, &TLO);
		t2.detach();
		TLO.timer_started = 1;
	}
	
}

void mainEvent::Event_Menu(sf::RenderWindow * app, background & TLO, controller_window & Window)
{
	if ((Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape) || (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.obrazek[4].getGlobalBounds().contains(worldPos)))
	{
		app->clear(sf::Color::Black);
		Window.SetWindow_ID(4);
		if (Window.GetWindow(app, TLO) == 0) //pobieranie tla okna dla wyjscia - 4
		{
			MessageBox(NULL, "Nie mozna zaladowac poprawnie okna!", "ERROR", NULL);
			exit(0);
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.obrazek[3].getGlobalBounds().contains(worldPos))
	{
		app->clear(sf::Color::Black);
		Window.SetWindow_ID(3);
		if (Window.GetWindow(app, TLO) == 0) //pobieranie tla okna dla wyjscia - 4
		{
			MessageBox(NULL, "Nie mozna zaladowac poprawnie okna!", "ERROR", NULL);
			exit(0);
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.obrazek[2].getGlobalBounds().contains(worldPos))
	{
		app->clear(sf::Color::Black);
		Window.SetWindow_ID(5);
		if (Window.GetWindow(app, TLO) == 0) //pobieranie tla okna dla wyjscia - 4
		{
			MessageBox(NULL, "Nie mozna zaladowac poprawnie okna!", "ERROR", NULL);
			exit(0);
		}
	}
}

void mainEvent::Event_Settings(sf::RenderWindow * app, background & TLO, controller_window & Window)
{
	for (int i = 6; i <= 15; i++)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.obrazek[i].getGlobalBounds().contains(worldPos))
		{
			for (int j = 6; j <= 15; j++)
			{
				if (TLO.obrazek[j].getChecked() == 1)
				{
					TLO.obrazek[j].setChecked(0);
					break;
				}

			}

			TLO.obrazek[i].setChecked(1);
			Window.GetWindow(app, TLO);
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.obrazek[16].getGlobalBounds().contains(worldPos))
	{
		if (TLO.obrazek[16].getChecked() == 1)
			TLO.obrazek[16].setChecked(0);
		else
			TLO.obrazek[16].setChecked(1);
		Window.GetWindow(app, TLO);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.obrazek[17].getGlobalBounds().contains(worldPos))
	{
		if (TLO.obrazek[17].getChecked() == 1)
			TLO.obrazek[17].setChecked(0);
		else
			TLO.obrazek[17].setChecked(1);
		Window.GetWindow(app, TLO);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.ksztalt[2].getGlobalBounds().contains(worldPos))
	{
		ofstream plik2;
		string text2;
		plik2.open("config.txt");

		int tab[10][2] = { { 800,600 },{ 1024,768 },{ 1280,600 },{ 1280,720 },{ 1280,768 },{ 1280,800 },{ 1360,768 },{ 1366,768 },{ 1440,900 },{ 1600, 900 } };

		int i;
		for (i = 0; i < 10; i++)
		{
			if (TLO.obrazek[i + 6].getChecked() == 1)
			{
				break;
			}
		}

		std::ostringstream ss, ss2, ss3, ss4;
		ss << tab[i][0];
		ss2 << tab[i][1];
		ss3 << TLO.obrazek[16].getChecked();
		ss4 << TLO.obrazek[17].getChecked();

		text2 = "Window\t" + ss.str() + "\t" + ss2.str() + "\nMusic\t" + ss4.str() + "\nFullscreen\t" + ss3.str();
		plik2 << text2;
		plik2.close();

		app->close();

		sf::RenderWindow start;
		start.create(sf::VideoMode(500, 100, 32), "Uruchamianie gry!");

		std::thread t2(&background::load_page, &TLO);
		t2.detach();

		sf::RectangleShape start_1;
		start_1.setFillColor(sf::Color::White);
		start_1.setSize(sf::Vector2f(500, 100));
		TLO.start.setString(L"Trwa zapisywanie ustawieñ! Proszê czekaæ!");

		while (TLO.mutex != 1)
		{
			start.draw(start_1);
			start.draw(TLO.start);
			start.display();
		}

		start.close();

		app = &(TLO.setWindow());
		app->clear(sf::Color::Black);
		Window.SetWindow_ID(1);
		if (Window.GetWindow(app, TLO) == 0) //pobieranie tla okna, w zaleznosci w jakim trybie jest [1-okno glowne]
		{
			MessageBox(NULL, "Nie mozna zaladowac poprawnie okna!", "ERROR", NULL);
			exit(0);
		}


	}
	else if ((Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape) || (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.ksztalt[3].getGlobalBounds().contains(worldPos)))
	{
		int tab[10][2] = { { 800,600 },{ 1024,768 },{ 1280,600 },{ 1280,720 },{ 1280,768 },{ 1280,800 },{ 1360,768 },{ 1366,768 },{ 1440,900 },{ 1600, 900 } };


		for (int i = 0; i < 10; i++)
		{
			if (TLO.obrazek[i + 6].getChecked() == 1)
			{
				TLO.obrazek[i + 6].setChecked(0);
			}
			if (tab[i][0] == TLO.window_x_return() && tab[i][1] == TLO.window_y_return())
			{
				TLO.obrazek[i + 6].setChecked(1);
			}
		}

		TLO.obrazek[16].setChecked(TLO.f);
		TLO.obrazek[17].setChecked(TLO.m);

		app->clear(sf::Color::Black);
		Window.SetWindow_ID(1);
	}
}

void mainEvent::Event_Close(sf::RenderWindow * app, background & TLO, controller_window & Window)
{
	if ((Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape) || (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.ksztalt[2].getGlobalBounds().contains(worldPos)))
	{
		app->close();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.ksztalt[3].getGlobalBounds().contains(worldPos))
	{
		app->clear(sf::Color::Black);
		Window.SetWindow_ID(1);
	}
}

void mainEvent::Event_GameSetup(sf::RenderWindow * app, background & TLO, controller_window & Window, game &GRA)
{
	unicode = 0;
	if ((Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape) || (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.obrazek[19].getGlobalBounds().contains(worldPos))) //klikniecie ANULUJ
	{
		app->clear(sf::Color::Black);
		Window.SetWindow_ID(1);
		if (Window.GetWindow(app, TLO) == 0) //pobieranie tla okna, w zaleznosci w jakim trybie jest [1-okno glowne]
		{
			MessageBox(NULL, "Nie mozna zaladowac poprawnie okna!", "ERROR", NULL);
			exit(0);
		}
		TLO.tlo_glowne(app);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.ksztalt[1].getGlobalBounds().contains(worldPos)) 
	{
		a = 1;
	}

	if (Event.type == sf::Event::TextEntered && a == 1 && TLO.tekst[17].getString().getSize() < 3)
	{
		unicode = Event.text.unicode;
		if (unicode >= 48 && unicode <= 57)
		{
			if (TLO.tekst[17].getString().getSize() != 0 || unicode != 48) 
			{
				str = TLO.tekst[17].getString();
				str += unicode;
				TLO.tekst[17].setString(str);
			}
		}
	}

	if (Event.type == sf::Event::TextEntered && a == 1 && TLO.tekst[17].getString().getSize() > 0)
	{
		unicode = Event.text.unicode;
		if (unicode == 8)
		{
			str = TLO.tekst[17].getString();
			str.erase(str.getSize() - 1, 1);
			TLO.tekst[17].setString(str);
		}
	}

	//ni¿ej obs³uga aktywowania i dezaktywniwa AKTYWNY dla 4 kolorów
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (TLO.obrazek[2].getGlobalBounds().contains(worldPos) || TLO.obrazek[6].getGlobalBounds().contains(worldPos) || TLO.tekst[2].getGlobalBounds().contains(worldPos)))
	{
		if (TLO.obrazek[6].getGame_checked() == 1)
			TLO.obrazek[6].setGame_checked(0);
		else
			TLO.obrazek[6].setGame_checked(1);

		TLO.game_setup();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (TLO.obrazek[3].getGlobalBounds().contains(worldPos) || TLO.obrazek[7].getGlobalBounds().contains(worldPos) || TLO.tekst[3].getGlobalBounds().contains(worldPos)))
	{
		if (TLO.obrazek[7].getGame_checked() == 1)
			TLO.obrazek[7].setGame_checked(0);
		else
			TLO.obrazek[7].setGame_checked(1);

		TLO.game_setup();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (TLO.obrazek[4].getGlobalBounds().contains(worldPos) || TLO.obrazek[8].getGlobalBounds().contains(worldPos) || TLO.tekst[4].getGlobalBounds().contains(worldPos)))
	{
		if (TLO.obrazek[8].getGame_checked() == 1)
			TLO.obrazek[8].setGame_checked(0);
		else
			TLO.obrazek[8].setGame_checked(1);

		TLO.game_setup();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (TLO.obrazek[5].getGlobalBounds().contains(worldPos) || TLO.obrazek[9].getGlobalBounds().contains(worldPos) || TLO.tekst[5].getGlobalBounds().contains(worldPos)))
	{
		if (TLO.obrazek[9].getGame_checked() == 1)
			TLO.obrazek[9].setGame_checked(0);
		else
			TLO.obrazek[9].setGame_checked(1);

		TLO.game_setup();
	}
	//tutaj koniec ob³sugi AKTYWNY
	//GRACZ 1
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.obrazek[6].getGame_checked() == 1 && (TLO.obrazek[10].getGlobalBounds().contains(worldPos) || TLO.tekst[6].getGlobalBounds().contains(worldPos))) //klieniecie na GRACZ
	{
		TLO.obrazek[10].setPlayer(1);
		TLO.game_setup();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.obrazek[6].getGame_checked() == 1  && (TLO.obrazek[11].getGlobalBounds().contains(worldPos) || TLO.tekst[7].getGlobalBounds().contains(worldPos))) //kliniecie na KOMPUTER
	{
		TLO.obrazek[10].setPlayer(0);
		TLO.game_setup();
	}
	//GRACZ 2
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.obrazek[7].getGame_checked() == 1 && (TLO.obrazek[12].getGlobalBounds().contains(worldPos) || TLO.tekst[8].getGlobalBounds().contains(worldPos))) //klieniecie na GRACZ
	{
		TLO.obrazek[12].setPlayer(1);
		TLO.game_setup();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.obrazek[7].getGame_checked() == 1 && (TLO.obrazek[13].getGlobalBounds().contains(worldPos) || TLO.tekst[9].getGlobalBounds().contains(worldPos))) //kliniecie na KOMPUTER
	{
		TLO.obrazek[12].setPlayer(0);
		TLO.game_setup();
	}
	//GRACZ 3
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.obrazek[8].getGame_checked() == 1 && (TLO.obrazek[14].getGlobalBounds().contains(worldPos) || TLO.tekst[10].getGlobalBounds().contains(worldPos))) //klieniecie na GRACZ
	{
		TLO.obrazek[14].setPlayer(1);
		TLO.game_setup();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.obrazek[8].getGame_checked() == 1 && (TLO.obrazek[15].getGlobalBounds().contains(worldPos) || TLO.tekst[11].getGlobalBounds().contains(worldPos))) //kliniecie na KOMPUTER
	{
		TLO.obrazek[14].setPlayer(0);
		TLO.game_setup();
	}
	//GRACZ 4
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.obrazek[9].getGame_checked() == 1 && (TLO.obrazek[16].getGlobalBounds().contains(worldPos) || TLO.tekst[12].getGlobalBounds().contains(worldPos))) //klieniecie na GRACZ
	{
		TLO.obrazek[16].setPlayer(1);
		TLO.game_setup();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.obrazek[9].getGame_checked() == 1 && (TLO.obrazek[17].getGlobalBounds().contains(worldPos) || TLO.tekst[13].getGlobalBounds().contains(worldPos))) //kliniecie na KOMPUTER
	{
		TLO.obrazek[16].setPlayer(0);
		TLO.game_setup();
	}
	//KONIEC WYBORU GRACZ CZY KOMPUTER

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.obrazek[18].getGlobalBounds().contains(worldPos))
	{
		app->clear(sf::Color::Black);
		Window.SetWindow_ID(6);
		if (Window.GetWindow(app, TLO) == 0) //pobieranie tla gry
		{
			MessageBox(NULL, "Nie mozna zaladowac poprawnie okna!", "ERROR", NULL);
			exit(0);
		}
		GRA.set_game(TLO, Window, worldPos);
	}
}

void mainEvent::Event_Game(sf::RenderWindow * app, background & TLO, controller_window & Window, game &GRA)
{
	GRA.Event_scan(app, TLO, Event, worldPos);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && TLO.game_obrazek[6].getGlobalBounds().contains(worldPos))
	{
		app->close();
	}

}