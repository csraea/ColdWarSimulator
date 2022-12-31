#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#else
#error "Unrecognized configuration!"
#endif

#include "MenuState.h"
#include "MyExceptions.h"
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include "GameController.h"

//-----------------------------------------------------------------------------
int main()
{
	srand((unsigned)time(nullptr));

	try
	{
		std::shared_ptr<GameController> game = std::make_shared<GameController>();
		game->pushState(std::make_shared<MenuState>(game));  //pushing main menu
		game->gameLoop();
	}
	catch (std::exception &e)
	{
		std::string s = "Exception: ";
		std::cerr << s << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}