ColdWar

made by Korotetskyi

*Files and classes:*

• **Main.cpp** 
	The main file that runs the start of the GameManager, pushes a menu state.

• **Macros.h**
	File holds all defines and consts, enums, structs as well as usings and includes used throughout the program.

• **Resources:**
	The resources class is in charge of loading and holding all outer files, such as pictures, music’s and fonts.
	It is a static Singleton class.

• **Chronometer:**
	A namespace which is an expansion of sf::clock, it has an addition of a pause and resume function which allows us to pause and resume the game clock when we pass between states.

• **Bullet, Enemy, PowerUp factories:**
	These classes are each in charge of creating objects.
	The class holds a static map which holds a key matching to the proper objects and a pointer to a function which creates the object. Each object is in charge of registering itself to the factory.

• **Level Controller:**
	The level controller gets the vector of entities and updates them by using the outer level files. It creates the objects according to the char in the file using the factories.

• **Game Controller:**
	The game controller runs the main game loop. It holds a stack of states like menu, pause, play, gameover. 
	Generically it calls a set of functions for the state that’s on the top of the stack.
	It has a push and pop function which are called when we want to move between game states.

• **State:**
	State is an abstract class that represents possible game states.

• **Menu state:**
	The class inherits from state, represents the main menu state. It is the first state pushed into the stack of states.
	It holds a vector of pointers that inherit from command, such as start and exit.

• **Playing State:**
	This state is the playing state, it holds the vectors of entities and is in charge of all playing updates, like movement, shooting, collision, deletion of objects….

• **PauseState:**
	The state pauses all game clocks…

• **GameOverState:**
	The state is in charge of ending the playing state.. cleaning everything getting users name and adding it to the multimap of high scores.

• **Command:**
	Abstract class that represents all buttons in games, has an execute function

• **Exit:**
	Inherits from command, exits the game.

• **NewGame:**
	Pushes the playing State.

• **MoveStrategy:**
	Abstract class that represents the enemy’s movements.

• **SimpleMove:**
	Inherits from MoveStrategy, is the default move for the simple enemies. Moves them in an army motion.

• **TeleportMove:**
	Inherits from MoveStrategy and continues to move the enemy according to his previous move, until the teleport animation stops. It then puts the enemy’s position in front of the player. And changes the enemy’s move Strategy to horizontal move.

• **HorizontalMove:**
	Inherits from MoveStrategy, this move is given to the enemy that was just teleported in front of the Lenin.

• **BossMove:**
	Inherits from MoveStrategy and moves the boss.

• **Entity:**
	Abstract class which represents a game object.

• **Bullet:**
	Abstract class represents a bullet.

• **SimpleEnemyBullet:**
	Bullet of an enemy

• **DefaultBullet:**
	Default hero bullet

• **StarBullet:**
	Bullet for hero gotten after a powerup

• **Weaponable:**
	Abstract class represents an enemy or a hero

• **Hero:**
	Inherits from weaponable, is the playable class

• **Enemy:**
	Inherits from weaponable, is abstract

• **SimpleEnemy:**
	Inherits from enemy

• **SmartEnemy:**
	Inherits from enemy

• **BossEnemy:**
	Inherits from enemy
	
• **PowerUp:**
    Abstract class that inherits from entity.

• **Shield:**
	Class that inherits from powerup, makes player invulnerable to ememy attacks

• **StarBullet:**
	Inherits from bullet, has addtional speed and damage.

• **Life:**
	Inherits from powerup, represents additional life gained to player
