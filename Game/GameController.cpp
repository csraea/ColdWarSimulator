#include "GameController.h"
#include "State.h"


GameController::GameController()
{
	m_window.create(sf::VideoMode((unsigned)WINDOW_SIZE.x, (unsigned)WINDOW_SIZE.y),
		"Cold War Simulator", sf::Style::Close);
}


void GameController::pushState(std::shared_ptr<State> state)
{
	states.push(state); //adds new state
}

void GameController::popState()
{
	states.pop();  //removes last state
}

inline std::shared_ptr<State> GameController::CurrentState()
{
	if (states.empty())
		return nullptr;
	return states.top();  // returns current state
}

void GameController::gameLoop()
{
	while (m_window.isOpen())
	{
		//exception handling
		if (CurrentState() == nullptr)   
			continue;

		//get user input for current game state
		CurrentState()->handleInput();

		//update anything necessary
		CurrentState()->update();
		CurrentState()->draw();
		
		m_window.display();
		m_window.clear();	
	}
}