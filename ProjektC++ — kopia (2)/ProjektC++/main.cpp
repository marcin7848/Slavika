#include <cmath>
#include "background.h"
#include "controller_window.h"
#include <vector>
#include <thread>
#include "mainEvent.h"

int main()
{
	sf::RenderWindow start;
	start.create(sf::VideoMode(400, 100, 32), "Uruchamianie gry!");
	background TLO;

	std::thread t2(&background::load_page, &TLO);
	t2.detach();

	sf::RectangleShape start_1;
	start_1.setFillColor(sf::Color::White);
	start_1.setSize(sf::Vector2f(400,100));

	while (TLO.mutex != 1)
	{
		start.draw(start_1);
		start.draw(TLO.start);
		start.display();
	}

	start.close();

	sf::RenderWindow* app;
	controller_window Window;
	game *GRA;
	GRA = new game[1];
	app = &(TLO.setWindow());
	app->clear(sf::Color::Black);
	if (Window.GetWindow(app, TLO) == 0) //pobieranie tla okna, w zaleznosci w jakim trybie jest [1-okno glowne]
	{
		MessageBox(NULL, "Nie mozna zaladowac poprawnie okna!", "ERROR", NULL);
		exit(0);
	}
	mainEvent Event;
	while (app->isOpen())
	{
		generuj(app, TLO, Window);
		Event.EventController(app, TLO, Window, GRA[0]);

		if (Window.GetWindow_ID() == 6)
		{
			GRA[0].Drukuj(app, TLO);
		}

		app->display();
	}
	return 0;
}