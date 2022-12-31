#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <vector>

#include "../Game/GameController.h"
#include "../Game/GameOverState.h"
#include "../Game/PauseState.h"
#include "../Game/SmartEnemy.h"
#include "../Game/MoveHorizontal.h"
#include "../Game/SimpleMove.h"
#include "../Game/TeleportMove.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ColdWarTest
{
	TEST_CLASS(ColdWarTest)
	{
	public:
		
		TEST_METHOD(GameStateTestCase1)
		{
			std::shared_ptr<GameController> game = std::make_shared<GameController>();
			game->pushState(std::make_shared<GameOverState>());
			game->pushState(std::make_shared<PauseState>());

			Assert::IsFalse(typeid(game->CurrentState()) == typeid(std::make_shared<GameOverState>()));
		};

		TEST_METHOD(GameStateTestCase2)
		{
			std::shared_ptr<GameController> game = std::make_shared<GameController>();
			game->pushState(std::make_shared<GameOverState>());
			game->pushState(std::make_shared<PauseState>());

			game->popState();

			Assert::IsTrue(typeid(game->CurrentState()) != typeid(std::make_shared<PauseState>()));
		};

		TEST_METHOD(MoveStrategyTestCase1)
		{
			std::unique_ptr<Enemy> e;

			e.get()->setMoveStrategy(std::unique_ptr<SimpleMove>());
			e.get()->setMoveStrategy(std::unique_ptr<MoveHorizontal>());

			Assert::IsFalse(typeid(e.get()->getStrategy().get()) == typeid(std::unique_ptr<SimpleMove>()));
		};

		TEST_METHOD(MoveStrategyTestCase2)
		{
			std::unique_ptr<Enemy> e;

			e.get()->setMoveStrategy(std::unique_ptr<SimpleMove>());
			e.get()->setMoveStrategy(std::unique_ptr<TeleportMove>());

			Assert::IsTrue(typeid(e.get()->getStrategy().get()) == typeid(std::unique_ptr<SimpleMove>()));
		}

		TEST_METHOD(TestMethod5)
		{

		}

	};
}
