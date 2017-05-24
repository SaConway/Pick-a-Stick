#pragma once
#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#else
#error "Unrecognized configuration!"
#endif

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Stick.h"
#include "Menu.h"
#include "Stage.h"							
using namespace std;
using namespace sf;

//-------------------------------------------------------------------------------------------------

const int WIDTH = 800;
const int HEIGHT = 800;

//-------------------------------------------------------------------------------------------------

class Controller
{
public:
	Controller();
	void runMenu();
	void play();
	void draw(){ m_window.display(); }
	
private:
	Menu m_menu;
	RenderWindow m_window;
	Stage m_stage;
	int m_num_of_level = 1;
};


