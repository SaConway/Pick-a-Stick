#include "Controller.h"
#include <iostream>
#include "MyException.h"


//-------------------------------------------------------------------------------------------------

/* Main function */

int main() 
{
	srand((unsigned) time(NULL));

	try
	{
		Controller controller;
		controller.runMenu();
	}

	catch (FileException e) {}

	return (EXIT_SUCCESS);
}

//-------------------------------------------------------------------------------------------------

/* c-tor of controller */

Controller::Controller()
{	
	m_window.create(VideoMode(WIDTH, HEIGHT), "Pick a Stick");
}

//-------------------------------------------------------------------------------------------------

/* Run menu function */

void Controller::runMenu()
{
	try 
	{
		while (true) 
		{
			m_menu.draw(m_window);

			switch (m_menu.eventHandler(m_window))
			{
			case PLAY: play();
				break;

			case EXIT:
				throw Escape();
			}
		}
	}

	catch (Escape e) 
	{
		m_window.close();
		m_stage.clean();
	}
}

//-------------------------------------------------------------------------------------------------

/* Play game function */

void Controller::play()
{
	bool win = true;

	while (win)
	{
		m_stage.clean();
		m_stage.setLevel(m_num_of_level * 15);
		win = m_stage.runStage(m_window);
		m_num_of_level++;
	}
	m_num_of_level = 1;
}
