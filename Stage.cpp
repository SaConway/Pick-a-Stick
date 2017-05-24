#include "Stage.h"
#include "MyException.h"

//-------------------------------------------------------------------------------------------------

/* c-tor of stage */

Stage::Stage()
{
	if (!m_back_ground.loadFromFile("background.png"))
		throw FileException("background.png does not exist");

	if(!m_sound_buf.loadFromFile("click.ogg"))
		throw FileException("click.ogg does not exist");

	m_click.setBuffer(m_sound_buf);
	m_back_ground_sprite.setTexture(m_back_ground);
	m_back_ground_sprite.setTextureRect(IntRect{ 0, 0, 800,800 });
}

//-------------------------------------------------------------------------------------------------

/* This function is main stage handler */

bool Stage::runStage(RenderWindow & window)
{
	while (window.isOpen() && !m_game_over)
	{
		m_info.updateTime();
		m_info.updateInfo();
		draw(window);

		if (m_info.checktimer()) m_game_over = true;

		/* User play */

		playerEvent(window);

		if (!m_game_over) draw(window);

		if (m_game_over && m_graph.stickCount() == 0) 
		{
			displayScore(window);
			return true;
		}

		else if(m_game_over)
		{
			displayScore(window);
			return false;
		}
	}
	return true;
}

//-------------------------------------------------------------------------------------------------

/*this function handle player events*/

void Stage::playerEvent(RenderWindow & window)
{
	Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			throw Escape();
		
		case Event::MouseButtonPressed: 
		{
			Vector2f mouse_location = window.mapPixelToCoords(Mouse::getPosition(window));

			if (m_graph.eventHandler(mouse_location)) m_click.play();

			if (m_graph.stickCount() == 0) m_game_over = true;

			m_info.updateScore(m_graph.stickCount());
			break;
		}

		/* Return to menu */
		case sf::Event::KeyPressed:
			if (event.key.code == Keyboard::Escape) m_game_over = true;
			break;
		}
	}

}

//-------------------------------------------------------------------------------------------------

/* This function display score when stage is finish */

void Stage::displayScore(RenderWindow & window)
{
	Event event;

	m_info.displayScore({ window.getSize() });
	draw(window);

	while (window.waitEvent(event)) 
	{
		switch (event.type)
		{
		case Event::Closed:
			throw Escape();
			
		case Event::MouseButtonPressed:
			return;
		}
	}
}

//-------------------------------------------------------------------------------------------------

/* This function is clearing all data in stage */

void Stage::clean()
{
	m_game_over = false;
	m_info.clean();
	m_graph.clean();
}

//-------------------------------------------------------------------------------------------------

/* This function draw the stage to window */

void Stage::draw(RenderWindow & window)
{
	window.clear();
	window.draw(m_back_ground_sprite);
	m_graph.draw(window);
	m_info.draw(window);
	window.display();
}

//-------------------------------------------------------------------------------------------------

/* This function builds new stage */

void Stage::setLevel(int num_of_sticks)
{
	m_graph.createGraph(num_of_sticks);
	m_info.createStage(num_of_sticks);
}
