#pragma once
#include "controller_window.h"
#include "game.h"
#include <thread>

class mainEvent
{
private:
	sf::Event Event;
	sf::Vector2i pixelPos;
	sf::Vector2f worldPos;
	sf::Uint32 unicode;
	sf::String str;
	int a;
	void Event_Menu(sf::RenderWindow* app, background &TLO, controller_window &Window);
	void Event_Settings(sf::RenderWindow* app, background &TLO, controller_window &Window);
	void Event_Close(sf::RenderWindow* app, background &TLO, controller_window &Window);
	void Event_GameSetup(sf::RenderWindow* app, background &TLO, controller_window &Window, game &GRA);
	void Event_Game(sf::RenderWindow* app, background &TLO, controller_window &Window, game &GRA);
	void Event_ResetShowMessage(sf::RenderWindow* app, background &TLO, controller_window &Window);

public:
	mainEvent();
	~mainEvent();
	void EventController(sf::RenderWindow* app, background &TLO, controller_window &Window, game &GRA);

};

