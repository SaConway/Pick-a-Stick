#include "Menu.h"
#include "MyException.h"

//-------------------------------------------------------------------------------------------------

/*c- tor menu*/

Menu::Menu()
{
	if(!m_background.loadFromFile("Mbackground.png"))
		throw FileException("Mbackground.png does not exist");

	m_sprite.setTexture(m_background);
	if(!m_font.loadFromFile("Khalifah.ttf"))
		throw FileException("Khalifah.ttf does not exist");

	m_playText.setFont(m_font);
	m_playText.setString("Play");
	m_playText.setCharacterSize(60);
	m_playText.setPosition(70, 500);
	m_playText.setFillColor(Color(38, 42, 48, 255));
	
	m_exitText.setFont(m_font);
	m_exitText.setString("Exit");
	m_exitText.setCharacterSize(60);
	m_exitText.setPosition(70, 650);
	m_exitText.setFillColor(Color(38, 42, 48, 255));

	m_pickTheStick.setFont(m_font);
	m_pickTheStick.setString("Pick a Stick");
	m_pickTheStick.setCharacterSize(50);
	m_pickTheStick.setPosition(400, 150);
	m_pickTheStick.setFillColor(Color(208, 211, 216, 230));
}

//-------------------------------------------------------------------------------------------------

/*menu event handler*/

int Menu::eventHandler(RenderWindow & window)
{
	Event event;

	while (window.waitEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			window.close();
			break;

		case Event::MouseButtonPressed:
			if (event.mouseButton.button == Mouse::Left)
			{
				if (m_playText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					return PLAY;

				if (m_exitText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					window.close();
					return EXIT;
				}
			}
		}
		draw(window);
	}

}

//-------------------------------------------------------------------------------------------------

/*Draw menu*/

void Menu::draw(RenderWindow & window) const
{
	window.clear();
	window.draw(m_sprite);
	window.draw(m_exitText);
	window.draw(m_playText);
	window.draw(m_pickTheStick);
	window.display();
}

