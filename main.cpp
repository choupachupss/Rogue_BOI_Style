/* Main file of the rogue project
   We will handle the main loop of the game here
   Author : Guillaume Mouton (Kiroxas)
*/
#include "AbstractMazeGenerator.h"
#include "DrunkMazeGenerator.h"
#include "NormalMazeGenerator.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Rendering.h"

#include <memory>
#include <time.h>
#include <stdlib.h>
#include "Input.h"
#include <iostream>

int main()
{
	srand ( time(NULL) );
	std::unique_ptr<AbstractMazeGenerator> g(new NormalMazeGenerator());
	std::unique_ptr<Maze> maze(g->CreateMaze(3));

	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	rendering::render_level(maze.get(),window);

	Input::Input in(window);
	Input::GameInput g_i;//(in.getGameInput());
	sf::Event event; 

	for(;;)
	{
		window.waitEvent(event);
		g_i.update(event);
		if(g_i.isShoot()) std::cout << "Shooting !!" << std::endl;
		if(g_i.isQuit()) return 0;
	}
}
