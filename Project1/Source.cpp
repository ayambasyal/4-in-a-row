#include "Game.h"
//
/*
how this works
1.  there is the game object that has many things after instantiation of the object , the constructor initializes the 
	window and other variables(private and public)
2.	the game runs by updating the values through the update mentod eg- by running the polling thing
3.	the game renders each time the render method is called hence forming the basics of the game

About the game itself
1.	The game has two halves one empty and another full.
2.	What the player has to do is reach the highest possible level that can be reached.

##### update needed 
1.	maintaining the polling event irrespective of the frame rate/ program execution 
	--> possible solution = multithreading ?

*/

//StateType defines which state the game is in
	// there is enum for it in game class itself




int main() {
	//init game engine
	Game game;
	//std::chrono::steady_clock::time_point This, That;
	//std::chrono::milliseconds now(25);
	while (game.running()) 
	{	
		//That = std::chrono::steady_clock::now();
		
		game.update();
		//auto a = std::chrono::steady_clock::now();
		//while ((std::chrono::steady_clock::now() - a) <= std::chrono::milliseconds(20)) { game.render(); };
		game.render();

		
	}
}
/*
std::chrono::steady_clock::time_point This, That;
std::chrono::milliseconds now(25);
That = std::chrono::steady_clock::now();
auto a = std::chrono::steady_clock::now();
while ((std::chrono::steady_clock::now() - a) <= std::chrono::milliseconds(20)) { game.render(); };
*/
