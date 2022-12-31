#include "MenuState.h"
#include "NewGame.h"
#include "Help.h"
#include "HighScore.h" 
#include "Exit.h"
#include "GameController.h"
#include "PlayingState.h"
#include <memory>
#include <functional>

using std::function;

//-----------------------------------------------------------------------------
MenuState::MenuState(std::shared_ptr<GameController> game)
{
	m_sprites.resize(NUM_OF_BUTTONS);
	m_game = game;

	sf::Sprite m_newGameButton;
	sf::Sprite m_exitButton;

	m_gameBackground.setTexture(Resources::get_instance().getGeneralTexture(MENU_BACKGROUND_T));

	m_newGameButton.setTexture(Resources::get_instance().getGeneralTexture(START_BUTTON_T));
	m_newGameButton.setOrigin(m_newGameButton.getGlobalBounds().width / 2, m_newGameButton.getGlobalBounds().height / 2);
	m_newGameButton.setPosition((WINDOW_SIZE.x / 2.f), (WINDOW_SIZE.y / 2.f));

	m_exitButton.setTexture(Resources::get_instance().getGeneralTexture(EXIT_BUTTON_T));
	m_exitButton.setOrigin(m_exitButton.getGlobalBounds().width / 2, m_exitButton.getGlobalBounds().height / 2);
	m_exitButton.setPosition(m_newGameButton.getPosition() + sf::Vector2f{ 0.f, 120.f });

	m_sprites[logo_ID::START_BUTTON] = m_newGameButton;
	m_sprites[logo_ID::EXIT_BUTTON] = m_exitButton;
	
	add("NewGame", std::make_unique<NewGame>());
	add("Exit", std::make_unique<Exit>());
}
//-----------------------------------------------------------------------------
void MenuState::add(std::string name, std::unique_ptr<Command> c)
{
	m_options.emplace_back(option(name, std::move(c)));
}
//-----------------------------------------------------------------------------
void MenuState::draw()
{
	m_game->m_window.draw(m_gameBackground);
	m_game->m_window.draw(m_logo);

	for (auto &sprite : m_sprites)
		m_game->m_window.draw(sprite);
}
//-----------------------------------------------------------------------------
void MenuState::handleInput()
{	
	sf::Event event;
	while (m_game->m_window.pollEvent(event))
	{
		switch (event.type)
		{
			
		case sf::Event::Closed:
			m_game->m_window.close();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				m_game->m_window.close();
			else if (event.key.code == sf::Keyboard::Return)
				loadgame();
			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left) 
			{
				for (int i = 0; i < m_sprites.size(); i++)
				{
					if (m_sprites[i].getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
						if (i == START_BUTTON)
							loadgame();
							
						else
							m_options[i].second->execute(m_game->m_window);
					}
				}
			}
		}
	}
}
//-----------------------------------------------------------------------------
void MenuState::loadgame()
{
	m_game->pushState(std::make_shared<PlayingState>(m_game));
}