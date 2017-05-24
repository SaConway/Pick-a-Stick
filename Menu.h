#pragma once
//-------------------------------------------------------------------------------------------------
									/* include section */
#include <SFML/Graphics.hpp>

//-------------------------------------------------------------------------------------------------
									/* using section */
using namespace sf;

//-------------------------------------------------------------------------------------------------
									/* const section */
const int PLAY = 0;
const int RULES = 1;
const int EXIT = 2;

//-------------------------------------------------------------------------------------------------

class Menu
{
public:
	Menu();
	int eventHandler(RenderWindow &);
	void draw(RenderWindow &) const;

private:
	Texture m_background;
	Sprite m_sprite;
	Font m_font;
	Text m_playText;
	Text m_exitText;
	Text m_pickTheStick;
};

