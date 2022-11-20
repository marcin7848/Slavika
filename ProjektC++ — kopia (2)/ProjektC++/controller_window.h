#pragma once
#include "background.h"

using namespace std;

class controller_window
{
public:
	controller_window();
	~controller_window();
	void SetWindow_ID(int a);
	int GetWindow_ID() const;
	int GetWindow(sf::RenderWindow* app, background & TLO);
	friend void generuj(sf::RenderWindow* app, background & TLO, controller_window & win);

private:
	int window_id;

};

