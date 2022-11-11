#include "Game.h"


void Game::init_variables()
{
	this->window = nullptr;
	font.loadFromFile("GOUDYSTO.ttf");
	;
}

void Game::init_window()
{
	this->videoMode.height = 600;
	this->videoMode.width = 700;
	this->window = new sf::RenderWindow(videoMode, "4 in a row",sf::Style::Close|sf::Style::Titlebar);

	music.openFromFile("Assets/Audio/audio.ogg");
	music_game_end.openFromFile("Assets/Audio/gameend2.ogg");
	music.setVolume(50);
	music_game_end.setVolume(50);
	music.play();
	volume = true;
	pvp = false;
	
}

Game::Game()
{
	this->init_variables();
	this->init_window();
}

Game::~Game()
{
	delete this->window;
	std::cout << "destructor called" << std::endl;
}

void Game::update()
{
	
	this->pollEvents();
	//std::cout << sequence << std::endl;
	switch (statetype)
	{
	case StateType::Intro:
		break;
	case StateType::MainMenu:
		main_Menu(*window);
		break;
	case StateType::Game:
		this->window->clear(sf::Color::White);
		draw_Background_Image(*window);
		draw_Player_Chip(*window);
		if (pvp == false) {
			if ((1 + position.moves % 2 == 2) ) 
			{
				try_To_Play(best_move(sequence)); 
			}
		}
		break;
	case StateType::Options:
		main_Menu_Options(*window);
		break;
	case StateType::GameOver:
		game_End(*window);
		//this->window->clear();
		//std::cout << "is this looping ?0" << std::endl;
		break;
	case StateType::Score:
		main_Menu_Score(*window);
		//window->clear();
		statetype = StateType::Score;
		break;
	default:
		break;
	}
	

}

void Game::render()
{

	
	window->setVerticalSyncEnabled(false);
	//window->setFramerateLimit(150);
	sf::Vector2i mouse_Position = sf::Mouse::getPosition(*window);
	std::chrono::steady_clock::time_point This,That;
	std::chrono::nanoseconds now;
	sf::Sprite sprite_ending, sprite_ending_button,sprite_end_button_backg;
	bool switch_animation = true;
	sf::Texture texture,texture_button,texture_button_background;
	static int j = 1;
	if (j > 10) switch_animation = false;
	else switch_animation = true;
	//std::cout << "is this loading then if  bool = "<<  switch_animation << std::endl;

	switch (statetype)
	{
	case StateType::Intro:
		break;
	case StateType::MainMenu:
		this->window->display();
		break;
	case StateType::Game:
		this->window->display();
		break;
	case StateType::Options:
		this->window->display();
		break;
	case StateType::GameOver:
		
		texture_button.loadFromFile("Assets/gameend/mainmenu_button.png");
		texture_button_background.loadFromFile("Assets/gameend/text_background.png");
		sprite_ending_button.setTexture(texture_button);
		sprite_ending_button.setPosition(sf::Vector2f(125, 380));
		sprite_end_button_backg.setTexture(texture_button_background);
		sprite_end_button_backg.setPosition(sf::Vector2f(125, 380));
		//std::chrono::duration_cast<std::chrono::milliseconds>(now).count()) >= (40 * j) &&
		This = std::chrono::steady_clock::now();
		while (j < 11 && switch_animation || j>0 && (switch_animation==0)) {
			That = std::chrono::steady_clock::now();
			now = That - This;
			if (((switch_animation) || (switch_animation==0))) {
				if (switch_animation == 0 ) { j--; }
				else j ++;
				//std::cout << "next = "<< j << std::endl;
				if (j!=0 && texture.loadFromFile("Assets/gameend2/" + std::to_string(j) + ".png")) {};
				sprite_ending.setTexture(texture);
			}
			window->draw(sprite_ending);
			if (mouse_Position.x >= 125 && mouse_Position.x <= 530 && mouse_Position.y >= 380 && mouse_Position.y <= 600)
			{
				window->draw(sprite_end_button_backg);
			}
			window->draw(sprite_ending_button);
			
			this->window->display();
			pollEvents();
			//std::cout << j<<std::endl;
		}
		break;
	case StateType::Score:
		this->window->display();
		break;
	default:
		break;
	}
}

const bool Game::running() const
{
	return window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {
		if (this->ev.type == sf::Event::Closed) {
			this->window->close();
		}
		else if (this->ev.type == sf::Event::MouseButtonReleased) {
			player_Click();
		}
		/*
			else if (this->ev.type == sf::Event::MouseWheelScrolled) {
				player_Scroll();
				render();
				sf::sleep(sf::milliseconds(400));
			}
		*/
	}
}


//Useful but dumb things

void Game::draw_Background_Image(sf::RenderWindow& window)
{
	sf::Texture texture;
	//std::cout << "Draw background image called" << std::endl;
	if (!texture.loadFromFile("Assets/board/board_final.png")) {
		// could not load texture error
		std::cout << "the texture could not be loaded" << std::endl;
	}
	sf::Sprite sprite;
	sprite.setTexture(texture);
	window.draw(sprite);
	//std::cout << "the sprite has been displayed"<<std::endl;
}

void Game::draw_Player_Chip(sf::RenderWindow& window)
{	
	if (!texture1.loadFromFile("Assets/board/player.png")) {
		//to check loading error
		std::cout << "could not load image from file ai_piece" << std::endl;
	}
	if (pvp) {
		if (!texture2.loadFromFile("Assets/board/player_2.png")) {
			//to check loading error
			std::cout << "could not load image from file sup_piece" << std::endl;
		}
	}
	else{
		if (!texture2.loadFromFile("Assets/board/ai.png")) {
			//to check loading error
			std::cout << "could not load image from file sup_piece" << std::endl;
		}
	}
	player_Sprite[0].setTexture(texture1);
	player_Sprite[1].setTexture(texture2);


	for (int row = 0; row < 6; row++) {
		for (int column = 0; column < 7; column++) {
			
			if (position.board[column][row] == 1) {
				player_Sprite[0].setPosition(23 + 96 * column ,490 - 93 * row);
				window.draw(player_Sprite[0]); 
			}
			else if (position.board[column][row] == 2) {
				player_Sprite[1].setPosition(23 + 96 * column, 490 - 93 * row);
				window.draw(player_Sprite[1]);	
			}
			else {}
		}
	}
}

void Game::player_Click()
{
	sf::Vector2i mouse_Position = sf::Mouse::getPosition(*window);
	//what to do on player click
	// if in runnning game what to do ??
	switch (statetype)
	{
	case StateType::Intro:
		break;
	case StateType::MainMenu:
		std::cout << "mouse button released" << std::endl;
		std::cout << "mouse button coordinates are " << std::endl;
		std::cout << "coordinate =  (" << mouse_Position.x << " , " << mouse_Position.y << ")" << std::endl;


		// what do do after click in certain coordinate
		if (mouse_Position.y >= 347 && mouse_Position.y <= 407 && mouse_Position.x >= 219 && mouse_Position.x <= 504)
		{
			//std::this_thread::sleep_for(std::chrono::microseconds(10000));
			statetype = StateType::Game;

		}
		else if (mouse_Position.y >= 415 && mouse_Position.y <= 455 && mouse_Position.x >= 285 && mouse_Position.x <= 408)
		{
			this->window->clear(sf::Color::White);
			//this->in_sequence("Assets/score/past.txt");
			//in_sequence.open("Assets/score.past.txt");
			main_Menu_Score(*window);
			statetype = StateType::Score;

		}
		else if (mouse_Position.y >= 462 && mouse_Position.y <= 502 && mouse_Position.x >= 285 && mouse_Position.x <= 408)
		
		{
			statetype = StateType::Options;
		
		}
		else if (mouse_Position.y >= 508 && mouse_Position.y <= 568 && mouse_Position.x >= 285 && mouse_Position.x <= 408)
		{
			window->close();

		}
		else {

		}
		break;

	case StateType::Game:
		
		if (1 + position.moves % 2 == 1) {
			std::cout << "mouse button released" << std::endl;
			std::cout << "mouse button coordinates are " << std::endl;
			std::cout << "coordinate =  (" << mouse_Position.x << " , " << mouse_Position.y << ")" << std::endl;

			if (mouse_Position.x >= 15 && mouse_Position.x <= 105) {
				std::cout << "column 1" << std::endl;
				try_To_Play(0);
			}
			else if (mouse_Position.x >= 115 && mouse_Position.x <= 200) {
				std::cout << "column 2" << std::endl;
				try_To_Play(1);
			}
			else if (mouse_Position.x >= 215 && mouse_Position.x <= 295) {
				std::cout << "column 3" << std::endl;
				try_To_Play(2);
			}
			else if (mouse_Position.x >= 310 && mouse_Position.x <= 390) {
				std::cout << "column 4" << std::endl;
				try_To_Play(3);
			}
			else if (mouse_Position.x >= 405 && mouse_Position.x <= 485) {
				std::cout << "column 5" << std::endl;
				try_To_Play(4);
			}
			else if (mouse_Position.x >= 501 && mouse_Position.x <= 581) {
				std::cout << "column 6" << std::endl;
				try_To_Play(5);
			}
			else if (mouse_Position.x >= 598 && mouse_Position.x <= 680) {
				std::cout << "column 7" << std::endl;
				try_To_Play(6);
			}
		}
		else if(pvp) 
		{
			std::cout << "mouse button released" << std::endl;
			std::cout << "mouse button coordinates are " << std::endl;
			std::cout << "coordinate =  (" << mouse_Position.x << " , " << mouse_Position.y << ")" << std::endl;

			if (mouse_Position.x >= 15 && mouse_Position.x <= 105) {
				std::cout << "column 1" << std::endl;
				try_To_Play(0);
			}
			else if (mouse_Position.x >= 115 && mouse_Position.x <= 200) {
				std::cout << "column 2" << std::endl;
				try_To_Play(1);
			}
			else if (mouse_Position.x >= 215 && mouse_Position.x <= 295) {
				std::cout << "column 3" << std::endl;
				try_To_Play(2);
			}
			else if (mouse_Position.x >= 310 && mouse_Position.x <= 390) {
				std::cout << "column 4" << std::endl;
				try_To_Play(3);
			}
			else if (mouse_Position.x >= 405 && mouse_Position.x <= 485) {
				std::cout << "column 5" << std::endl;
				try_To_Play(4);
			}
			else if (mouse_Position.x >= 501 && mouse_Position.x <= 581) {
				std::cout << "column 6" << std::endl;
				try_To_Play(5);
			}
			else if (mouse_Position.x >= 598 && mouse_Position.x <= 680) {
				std::cout << "column 7" << std::endl;
				try_To_Play(6);
			}

		}
		render();
		show_Board();
		break;
	case StateType::Score:
		statetype = StateType::MainMenu;
		break;
	case StateType::GameOver:
		if (mouse_Position.x >= 125 && mouse_Position.x <= 530 && mouse_Position.y >= 380 && mouse_Position.y <= 600) {
			window->clear();
			statetype = StateType::MainMenu;
			std::cout << "button pressed" << std::endl;
			music_game_end.stop();
			music.play();
		}

		break;
	case StateType::Options:
		std::cout << "mouse button released" << std::endl;
		std::cout << "mouse button coordinates are " << std::endl;
		std::cout << "coordinate =  (" << mouse_Position.x << " , " << mouse_Position.y << ")" << std::endl;


		// what do do after click in certain coordinate
		if (mouse_Position.y >= 347 && mouse_Position.y <= 407 && mouse_Position.x >= 219 && mouse_Position.x <= 504)
		{
			//std::this_thread::sleep_for(std::chrono::microseconds(10000));
			statetype = StateType::MainMenu;

		}
		else if (mouse_Position.y >= 415 && mouse_Position.y <= 455 && mouse_Position.x >= 285 && mouse_Position.x <= 408)
		{
			pvp = false;
			std::cout << "pvp =  false" << std::endl;

		}
		else if (mouse_Position.y >= 462 && mouse_Position.y <= 502 && mouse_Position.x >= 285 && mouse_Position.x <= 408)

		{
			pvp = true;
			std::cout << "pvp =  true" << std::endl;

		}
		else if (mouse_Position.y >= 508 && mouse_Position.y <= 568 && mouse_Position.x >= 285 && mouse_Position.x <= 408)
		{
			if (volume == true) {
				volume = false;
				music.pause();
			}
			else
			{
				volume = true;
				music.play();
			}

		}
		else {

		}
		break;
	default:
		break;
	}
	
}

bool Game::try_To_Play(int col)
{
	if (this->position.canPlay(col)) {
		
			if (this->position.isWinningMove(col)) {
				this->position.play(col);
				//std::cout << "sequence is : " << sequence << std::endl;
				draw_Player_Chip(*(this -> window));
				render();
				
				if (statetype == StateType::Game){
					sequence += std::to_string(col + 1);
					addtowin();
					music.stop();
					music_game_end.play();
					game_over_animation();
					game_End(*window); 
					statetype = StateType::GameOver;
				}
				else if(statetype == StateType::Score){
				//
				}
			}
			else{
				if (statetype == StateType::Game) {
					sequence += std::to_string(col + 1);
				}
				this->position.play(col);
				std::cout << "column " << col << "  played" << std::endl;
				std::cout << "try to play called" << std::endl;
				std::cout << "sequence is : " << sequence << std::endl;
				std::cout << "sequence size = " << sequence.size() << std::endl;
			}
		}
		else 
		{
			std::cout << "ya you can't play that move" << std::endl;
		}
	return false;
}

void Game::main_Menu(sf::RenderWindow& window)
{
	sf::Texture texture;
	sf::Texture texture2;

	if (!texture.loadFromFile("Assets/menu/menu_background_2.png")) {
		// could not load texture error
		std::cout << "the texture could not be loaded" << std::endl;
	}

	sf::Sprite sprite;
	sprite.setTexture(texture);
	
	if (!texture2.loadFromFile("Assets/menu/menu_options_spritesheet.png")) {
		// could not load texture error
		std::cout << "the texture could not be loaded" << std::endl;
	}
	
	sf::Sprite sprite2(texture2,sf::IntRect(0,0,700,350));
	sprite2.setPosition(sf::Vector2f(0, 350));
	window.draw(sprite2);
	
	sf::Vector2i mouse_Position = sf::Mouse::getPosition(window);
	
	window.draw(sprite);
	

	if (mouse_Position.y >= 347 && mouse_Position.y <= 407 && mouse_Position.x >= 219 && mouse_Position.x <= 504)
	{
		sf::Sprite sprite3(texture2, sf::IntRect(0, 280, 700, 340));
		//std::cout << "mouse in position start game" << std::endl;
		sprite3.setPosition(sf::Vector2f(0, 344));
		window.draw(sprite3);
		
	}
	else if (mouse_Position.y >= 415 && mouse_Position.y <= 455 && mouse_Position.x >= 285 && mouse_Position.x <= 408)
	{
		//std::cout << "mouse in position score" << std::endl;

		sf::Sprite sprite3(texture2, sf::IntRect(0, 300, 700, 460));
		//std::cout << "mouse in position start game" << std::endl;
		sprite3.setPosition(sf::Vector2f(0, 412));
		window.draw(sprite3);
	}
	else if (mouse_Position.y >= 462 && mouse_Position.y <= 502 && mouse_Position.x >= 285 && mouse_Position.x <= 408)
	{
		//std::cout << "mouse in position options" << std::endl;

		sf::Sprite sprite3(texture2, sf::IntRect(0, 300, 700, 460));
		//std::cout << "mouse in position start game" << std::endl;
		sprite3.setPosition(sf::Vector2f(0, 458));
		window.draw(sprite3);

	}
	else if (mouse_Position.y >= 508 && mouse_Position.y <= 568 && mouse_Position.x >= 285 && mouse_Position.x <= 408)
	{
		//std::cout << "mouse in position exit" << std::endl;

		sf::Sprite sprite3(texture2, sf::IntRect(0, 280, 700, 340));
		//std::cout << "mouse in position start game" << std::endl;
		sprite3.setPosition(sf::Vector2f(0, 505));
		window.draw(sprite3);

	}
	else {
		
	}
	window.draw(sprite2);
	
	//std::cout << "the sprite has been displayed"<<std::endl;

}

int Game::best_move(std::string seq)  //returns 0 based index of best move
{

	if (seq.size() == 1) 
	{
		return 3;
	}
	else if (seq == "445") {
		return 5;
	}
	else if (seq == "444") {
		return 3;
	}
	else if (seq == "443") {
		return 1;
	}
	else if (seq == "446") {
		return 4;
	}
	else if (seq == "442") {
		return 2;
	}
	else if (seq == "441") {
		return 2;
	}
	else if (seq == "447") {
		return 4;
	}
	else if (seq.size() == 3) {
		return 3;
	}
	else if (seq == "44444") {
		return 1;
	}

	else if (seq == "4444424") {
		return 1;
	}
	else if (seq == "444442423") {
		return 2;
	}
	else
	{
		if (position.isWinningMove(0)) {
			return 0;
		}
		int bestmove = 1,bestscore= maintain(seq + '1');
		render();
		for (int j = 2; j <= 7; j++) 
		{
			if (position.isWinningMove(j - 1) && position.canPlay(j-1)){
				return j - 1;
			}
			int score = maintain(seq + std::to_string(j));
			if (score < bestscore) {
				bestscore = score;
				bestmove = j;
				
			}
			
		}
		return bestmove - 1;
	}
}

void Game::main_Menu_Options(sf::RenderWindow& window)
{

	sf::Texture texture;
	sf::Texture texture2;

	if (!texture.loadFromFile("Assets/menu/menu_background_2.png")) {
		// could not load texture error
		std::cout << "the texture could not be loaded" << std::endl;
	}

	sf::Sprite sprite;
	sprite.setTexture(texture);

	if (!texture2.loadFromFile("Assets/menu/options_spritesheet.png")) {
		// could not load texture error
		std::cout << "the texture could not be loaded" << std::endl;
	}

	sf::Sprite sprite2(texture2, sf::IntRect(0, 0, 700, 350));
	sprite2.setPosition(sf::Vector2f(0, 350));
	window.draw(sprite2);

	sf::Vector2i mouse_Position = sf::Mouse::getPosition(window);

	window.draw(sprite);


	if (mouse_Position.y >= 347 && mouse_Position.y <= 407 && mouse_Position.x >= 219 && mouse_Position.x <= 504)
	{
		sf::Sprite sprite3(texture2, sf::IntRect(0, 280, 700, 340));
		//std::cout << "mouse in position start game" << std::endl;
		sprite3.setPosition(sf::Vector2f(0, 344));
		window.draw(sprite3);

	}
	else if (mouse_Position.y >= 415 && mouse_Position.y <= 455 && mouse_Position.x >= 285 && mouse_Position.x <= 408)
	{
		//std::cout << "mouse in position score" << std::endl;

		sf::Sprite sprite3(texture2, sf::IntRect(0, 300, 700, 460));
		//std::cout << "mouse in position start game" << std::endl;
		sprite3.setPosition(sf::Vector2f(0, 412));
		window.draw(sprite3);
	}
	else if (mouse_Position.y >= 462 && mouse_Position.y <= 502 && mouse_Position.x >= 285 && mouse_Position.x <= 408)
	{
		//std::cout << "mouse in position options" << std::endl;

		sf::Sprite sprite3(texture2, sf::IntRect(0, 300, 700, 460));
		//std::cout << "mouse in position start game" << std::endl;
		sprite3.setPosition(sf::Vector2f(0, 458));
		window.draw(sprite3);

	}
	else if (mouse_Position.y >= 508 && mouse_Position.y <= 568 && mouse_Position.x >= 285 && mouse_Position.x <= 408)
	{
		//std::cout << "mouse in position exit" << std::endl;

		sf::Sprite sprite3(texture2, sf::IntRect(0, 280, 700, 340));
		//std::cout << "mouse in position start game" << std::endl;
		sprite3.setPosition(sf::Vector2f(0, 505));
		window.draw(sprite3);

	}
	else {

	}
	window.draw(sprite2);

	//std::cout << "the sprite has been displayed"<<std::endl;
}

void Game::player_Scroll()
{
	switch (statetype)
	{
	case StateType::Intro:
		break;
	case StateType::MainMenu:
		break;
	case StateType::Game:
		break;
	case StateType::Options:
		break;
	case StateType::GameOver:
		break;
	case StateType::Score:
		//main_Menu_Score();
		break;
	default:
		break;
	}
}

void Game::game_over_animation()
{
	auto a = std::chrono::steady_clock::now();
	std::ofstream file1;
	file1.open("Assets/score/past.txt",std::ios::app);

	//std::ifstream file2("Assets/score/past.txt");
	file1 << sequence+'\n';

	while ((std::chrono::steady_clock::now() - a) <= std::chrono::milliseconds(2000)) { continue; };

}

void Game::main_Menu_Score(sf::RenderWindow& window)
{
	/*
	reset_Board();
	static std::ifstream in_sequence("Assets/score/past.txt");
	std::string data;
	in_sequence >> data;
	std::cout << "the sequence is = " << data << std::endl;
	int col;
	for (char const& c : data) {
		col = int(c)-48;
		try_To_Play(col-1);
		std::cout << "played col = " << col-1 << std::endl;
	}
	*/

	sf::Texture texture_score;
	sf::Sprite score_sprite;

	if (!pvp) 
		{	

		texture_score.loadFromFile("Assets/score/score.png");
		score_sprite.setTexture(texture_score);
		window.draw(score_sprite);
		std::ifstream in_sequence("Assets/score/past.txt");
		std::string data;
		std::getline(in_sequence, data);
		int win,loss;
		win = (int(data[0]) - 48)*100+ (int(data[1]) - 48) * 10+ (int(data[2]) - 48) * 1;
		std::getline(in_sequence, data);
		loss = (int(data[0]) - 48)*100+ (int(data[1]) - 48) * 10+ (int(data[2]) - 48) * 1;
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(60);
		if (win > 99)
		{
			text.setPosition(200, 420);
		}
		else
		{
			text.setPosition(220, 420);
		}
		text.setString(std::to_string(win));
		window.draw(text);
		text.setPosition(415, 420);
		text.setString(std::to_string(loss));
		window.draw(text);
		in_sequence.close();
	}
	else
	{
		texture_score.loadFromFile("Assets/score/scorepvp.png");
		score_sprite.setTexture(texture_score);
		window.draw(score_sprite);
		std::ifstream in_sequence2("Assets/score/past2.txt");
		std::string data;
		std::getline(in_sequence2, data);
		int win, loss;
		win = (int(data[0]) - 48) * 100 + (int(data[1]) - 48) * 10 + (int(data[2]) - 48) * 1;
		std::getline(in_sequence2, data);
		loss = (int(data[0]) - 48) * 100 + (int(data[1]) - 48) * 10 + (int(data[2]) - 48) * 1;
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(60);
		if (win > 99)
		{
			text.setPosition(200, 420);
		}
		else
		{
			text.setPosition(220, 420);
		}
		text.setString(std::to_string(win));
		window.draw(text);
		text.setPosition(415, 420);
		text.setString(std::to_string(loss));
		window.draw(text);
		in_sequence2.close();
	}

}

void Game::addtowin()
{


	//recieve previous win or loss data
	std::cout << position.moves << std::endl;
	std::ifstream in_sequence;
	if (!pvp) {
		in_sequence.open("Assets/score/past.txt");
	}
	else
		in_sequence.open("Assets/score/past2.txt");

	std::string data;
	std::getline(in_sequence, data);
	std::cout << data << std::endl;
	int win, loss;
	win = (int(data[0]) - 48) * 100 + (int(data[1]) - 48) * 10 + (int(data[2]) - 48) * 1;
	std::cout << data << std::endl;
	std::getline(in_sequence, data);
	loss = (int(data[0]) - 48) * 100 + (int(data[1]) - 48) * 10 + (int(data[2]) - 48) * 1;
	std::cout << "win = " << win << " and loss = " << loss << std::endl;
	in_sequence.close();
	if (position.nbMoves() % 2 == 1) {
		win++;
	}
	else loss++;


	//file handling to write  
	std::ofstream fout;
	if (!pvp) {
		fout.open("Assets/score/past.txt");
	}
	else
		fout.open("Assets/score/past2.txt");

	auto new_str = std::string(3 - std::min(3, (int)std::to_string(win).length()), '0') + std::to_string(win);
	auto temp_str = new_str + "\n";
	new_str = std::string(3 - std::min(3, (int)std::to_string(loss).length()), '0') + std::to_string(loss);
	temp_str = temp_str + new_str + "\n";
	fout << temp_str;
	std::cout << temp_str << std::endl;
	fout.close();




}

void Game::game_End(sf::RenderWindow& window)
{
	//std::cout << "game has ended " << std::endl;
	//std::cout << "game has ended " << std::endl;
	//std::cout << "game has ended " << std::endl;
	//std::cout << "game has ended " << std::endl;
	//std::cout << "game has ended " << std::endl;
	//std::cout << "game has ended " << std::endl;
	//std::cout << "game has ended " << std::endl;
	//std::cout << "game has ended " << std::endl;
	//window.display();
	//game_over_animation();

	reset_Board();
	statetype = StateType::GameOver;
}

void Game::show_Board()

{
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			std::cout << position.board[j][i] << "   ";
		}
		std::cout << std::endl;
	}
}

void Game::reset_Board()
{
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			position.board[j][i] = 0;
		}
	}
	sequence = "";
	for (int j = 0; j < 7; j++) {
		position.height[j] = 0;
	}
	position.moves = 0;
}







