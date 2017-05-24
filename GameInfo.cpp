#include "GameInfo.h"
#include <sstream>
#include "MyException.h"

//-------------------------------------------------------------------------------------------------

/* c-tor of Game Info */

GameInfo::GameInfo()
{
	if(!m_font.loadFromFile("Khalifah.ttf"))
		throw FileException("Khalifah.ttf does not exist");

	m_textTime.setFont(m_font);
	m_textTime.setCharacterSize(30);
	m_textTime.setStyle(sf::Text::Bold);
	m_textTime.setPosition(sf::Vector2f{ 10, 10 });

	m_textScore.setFont(m_font);
	m_textScore.setCharacterSize(30);
	m_textScore.setStyle(sf::Text::Bold);
	m_textScore.setPosition(sf::Vector2f{ 450, 10 });

}
//-------------------------------------------------------------------------------------------------
 
/* This function set new data for the current stage */

void GameInfo::createStage(int num_of_sticks )
{
	m_num_of_stick = num_of_sticks;
	m_start_num_of_stick = num_of_sticks;
	int total_seconds = num_of_sticks * 4;
	m_clock.restart();
	m_timer.x = total_seconds / 60;
	m_timer.y = total_seconds % 60;
}

//-------------------------------------------------------------------------------------------------

/* This function is updating the time */

void GameInfo::updateTime()
{
	sf::Time second = sf::seconds(1);

	/*evrey second update*/
	if (m_clock.getElapsedTime() > second && m_timer.x != -1)
	{
		m_clock.restart();

		if (m_timer.y == 0) 
		{
			m_timer.y = 59;
			--m_timer.x;
		}

		else
			--m_timer.y;

		/*game bar red warning when time or steps is about to end*/
		if (m_timer.x == 0 && m_timer.y <= 10 ) {

			if (m_textTime.getFillColor() == sf::Color::Red)
				m_textTime.setFillColor(sf::Color::White);
			else
				m_textTime.setFillColor(sf::Color::Red);
		}
	}
}

//-------------------------------------------------------------------------------------------------

/* This function update the stage status bar info */

void GameInfo::updateInfo()
{
	stringstream _stringTime, _stringScore;

	_stringScore << "Score: " << m_score ;

	if (m_timer.x != -1)
	{
		_stringTime << "     Time left:  " << "0" << m_timer.x << ':';

		if (m_timer.y < 10)
			_stringTime << "0";

		_stringTime << m_timer.y;
	}

	m_textScore.setString(_stringScore.str());
	m_textTime.setString(_stringTime.str());
}

//-------------------------------------------------------------------------------------------------

/* This function update the score */

void GameInfo::updateScore(int curr_stick_count)
{
	if (curr_stick_count == m_num_of_stick)
	{
		m_score -= 5;
		return;
	}

	m_num_of_stick--;
	m_score += m_start_num_of_stick - m_num_of_stick + 2;
}

//-------------------------------------------------------------------------------------------------

/* This function reset the data */

void GameInfo::clean()
{
	m_textTime.setFillColor(sf::Color::White);
	m_timer = sf::Vector2i{ 0,0 };
	m_clock.restart();
	m_textScore.setCharacterSize(30);
	m_textScore.setPosition(sf::Vector2f{ 450, 10 });
	m_score = 0;
}

//-------------------------------------------------------------------------------------------------

/* This function display score at end of level */

void GameInfo::displayScore(Vector2u window_size)
{
	std::stringstream _string;

	_string << "Your score is :\n";
	_string << m_score;
	m_textScore.setCharacterSize(70);
	m_textScore.setString(_string.str());
	m_textScore.setPosition({(float)window_size.x / 4 ,(float)window_size.y / 4 });
	m_textScore.setFillColor(sf::Color::White);
}
