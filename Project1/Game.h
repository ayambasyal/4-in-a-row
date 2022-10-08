#pragma once
//#include<iostream>
//#include <chrono>
#include "maintain.h"
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include"Position2.h"
#include <thread>
#include <fstream>


// to manage states

enum class StateType {
	Intro = 1, MainMenu, Game, Options, GameOver, Score
};

//  this is a mini game engine 
class Game
{
	private:
		//variables    windows
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::Event ev;
		Position2 position;
		sf::Music music;

		

		//chrono time variable 
		//std::chrono::steady_clock clock_game;     may use later

		sf::Sprite player_Sprite[2];   // why is player sprite 2 private?

		//private functions
		void init_variables(); // initializes pointers to null so that problemn does not arise later on
		
		void init_window();// initializes the window dynamically by using videomode variable manually
		bool volume,pvp;

		
	
	public:

		// to store the complete input sequence
		std::string sequence;
		//string corresponding to the board
		std::string string_for_board;
		StateType statetype = StateType::MainMenu;
		//public variables
		sf::Texture texture1, texture2;



		//file handling 
		std::ofstream fout;
		std::ifstream in_sequence;


		//Constructors / Destructors
		Game();											// to intialize things 
		virtual ~Game();								// to remove initialized things especially dinamically initialized things

		// Acessors
		const bool running() const;

		// Functions
		void pollEvents();
		void update();
		void render();

		//display functions
		void draw_Background_Image(sf::RenderWindow& window);
		void draw_Player_Chip(sf::RenderWindow& window);
			 
		//game related functions 
		void player_Click();
		void player_Scroll();
		bool try_To_Play(int col);
		void game_End(sf::RenderWindow& window);

		//calling it shows every position on the board in console
		void show_Board();
		void reset_Board();

		//      menu
		void main_Menu(sf::RenderWindow& window);
		void main_Menu_Options(sf::RenderWindow& window);
		void main_Menu_Score();



		int best_move(std::string seq);
		void game_over_animation();





	};

