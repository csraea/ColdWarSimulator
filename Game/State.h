#pragma once
#include <memory>

class GameController;

class State
{
public:
	State() = default;
	virtual~State() = default;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void handleInput() = 0;

protected:
	std::shared_ptr<GameController> m_game;
};