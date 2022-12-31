#include "GameOverState.h"
#include "GameController.h"

//-----------------------------------------------------------------------------
GameOverState::GameOverState(std::shared_ptr<GameController> game, int score)
{
	m_game = game;
	m_score = score;

	if (m_score <= 0)
	{
		m_gameoverBackground.setTexture(Resources::get_instance().getGeneralTexture(GAMEOVER_BACKGROUND1_T));
		Resources::get_instance().play(MUSIC_ID::DEFEAT_M);
	}
	else
	{
		m_gameoverBackground.setTexture(Resources::get_instance().getGeneralTexture(GAMEOVER_BACKGROUND2_T));
		Resources::get_instance().play(MUSIC_ID::VICTORY_M);
	}

	m_yourScore.setFont(Resources::get_instance().getFont());
	m_yourScore.setString("Your Score: " + std::to_string(score > 0 ? score : score * -1));
	m_yourScore.setCharacterSize(50);
	m_yourScore.setOrigin(m_yourScore.getGlobalBounds().width / 2, 0);
	m_yourScore.setPosition((WINDOW_SIZE.x / 2) - 50, (WINDOW_SIZE.y / 2) + 40);

	m_yourScore.setFillColor(sf::Color(255, 211, 57, 255));
}
//-----------------------------------------------------------------------------
void GameOverState::draw()
{
	m_game->m_window.draw(m_gameoverBackground);
	m_game->m_window.draw(m_yourScore);
}
//-----------------------------------------------------------------------------
void GameOverState::handleInput()
{
	sf::Event event;

	while (m_game->m_window.pollEvent(event))
	{
		switch (event.type)
		{
			/* Close the window */
		case sf::Event::Closed:
			m_game->m_window.close();
			break;

		case sf::Event::KeyPressed:
			return;
		}
	}
}