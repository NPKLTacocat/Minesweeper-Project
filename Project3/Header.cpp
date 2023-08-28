#include "Header.h"

void import_config(vector<string> &config_data)
{
	fstream read_file("files/board_config.cfg", ios_base::in | ios_base::binary);
	if (read_file.is_open())
	{
		for (int i = 0; i < 3; i++)
		{
			string singleLine;
			getline(read_file, singleLine);
			config_data.push_back(singleLine);
		}
	}
	else
	{
		cout << "file is not open" << endl;
	}
}
void setText(sf::Text& text, float x, float y)
{
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
	textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(x, y));
}
map<string, sf::Texture> load_texture()
{
	map<string, sf::Texture> texture;
	sf::Texture temp_texture;

	texture["tile_revealed"] = temp_texture;
	texture["tile_revealed"].loadFromFile("files/images/tile_revealed.png");

	texture["tile_hidden"] = temp_texture;
	texture["tile_hidden"].loadFromFile("files/images/tile_hidden.png");

	texture["play"] = temp_texture;
	texture["play"].loadFromFile("files/images/play.png");

	texture["pause"] = temp_texture;
	texture["pause"].loadFromFile("files/images/pause.png");

	texture["number_8"] = temp_texture;
	texture["number_8"].loadFromFile("files/images/number_8.png");

	texture["number_7"] = temp_texture;
	texture["number_7"].loadFromFile("files/images/number_7.png");

	texture["number_6"] = temp_texture;
	texture["number_6"].loadFromFile("files/images/number_6.png");

	texture["number_5"] = temp_texture;
	texture["number_5"].loadFromFile("files/images/number_5.png");

	texture["number_4"] = temp_texture;
	texture["number_4"].loadFromFile("files/images/number_4.png");

	texture["number_3"] = temp_texture;
	texture["number_3"].loadFromFile("files/images/number_3.png");

	texture["number_2"] = temp_texture;
	texture["number_2"].loadFromFile("files/images/number_2.png");

	texture["number_1"] = temp_texture;
	texture["number_1"].loadFromFile("files/images/number_1.png");

	texture["mine"] = temp_texture;
	texture["mine"].loadFromFile("files/images/mine.png");

	texture["leaderboard"] = temp_texture;
	texture["leaderboard"].loadFromFile("files/images/leaderboard.png");

	texture["flag"] = temp_texture;
	texture["flag"].loadFromFile("files/images/flag.png");

	texture["face_win"] = temp_texture;
	texture["face_win"].loadFromFile("files/images/face_win.png");

	texture["face_lose"] = temp_texture;
	texture["face_lose"].loadFromFile("files/images/face_lose.png");

	texture["face_happy"] = temp_texture;
	texture["face_happy"].loadFromFile("files/images/face_happy.png");

	texture["digits"] = temp_texture;
	texture["digits"].loadFromFile("files/images/digits.png");

	texture["debug"] = temp_texture;
	texture["debug"].loadFromFile("files/images/debug.png");

	return texture;
}

WelcomeWindow::WelcomeWindow()
{
	vector<string> config_data;
	import_config(config_data);

	width = stoi(config_data[0]) * 32;
	height = stoi(config_data[1]) * 32 + 100;
}

void WelcomeWindow::Display()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close | sf::Style::Titlebar);
	sf::RectangleShape shape;
	shape.setFillColor(sf::Color::Blue);
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(0, 0);	

	sf::Font font;
	font.loadFromFile("files/font.ttf");

	sf::Text welcome_text;
	welcome_text.setFont(font);
	welcome_text.setStyle(sf::Text::Underlined | sf::Text::Bold);
	welcome_text.setString("WELCOME TO MINESWEEPER!");
	welcome_text.setCharacterSize(24);
	welcome_text.setFillColor(sf::Color::White);
	setText(welcome_text, width / 2, height / 2 - 150);

	sf::Text input_prompt;
	input_prompt.setFont(font);
	input_prompt.setStyle(sf::Text::Bold);
	input_prompt.setString("Enter your name:");
	input_prompt.setCharacterSize(20);
	input_prompt.setFillColor(sf::Color::White);
	setText(input_prompt, width / 2, height / 2 - 75);
	
	string temp_string = "";
	sf::Text input_text;
	input_text.setFont(font);
	input_text.setStyle(sf::Text::Bold);
	input_text.setString(temp_string);
	input_text.setCharacterSize(18);
	input_text.setFillColor(sf::Color::Yellow);
	setText(input_text, width / 2, height / 2 - 45);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::TextEntered)
			{
				unsigned char temp_text = event.text.unicode;
				if (isalpha(temp_text) && temp_string.size() <= 10)
				{
					if (temp_string.size() == 0)
					{
						temp_text = toupper(temp_text);
					}
					else
					{
						temp_text = tolower(temp_text);
					}
					temp_string += temp_text;
					temp_string += "|";
					input_text.setString(temp_string);
					temp_string.pop_back();
					setText(input_text, width / 2, height / 2 - 45);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) && event.type == sf::Event::KeyPressed)
			{
				if (temp_string.size() > 0)
				{
					temp_string.pop_back();
					temp_string += "|";
					input_text.setString(temp_string);
					temp_string.pop_back();
					setText(input_text, width / 2, height / 2 - 45);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && temp_string.size() > 0)
			{
				window.close();
				GameWindow game(rand_time1, temp_string);
				game.Display();
			}
		}
		window.clear();
		window.draw(shape);
		window.draw(welcome_text);
		window.draw(input_prompt);
		window.draw(input_text);
		window.display();
	}
}

GameWindow::GameWindow(chrono::steady_clock::time_point& rand_time, string name)
{
	this->name = name;
	vector<string> config_data;
	import_config(config_data);
	rand_time1 = rand_time;
	col = stoi(config_data[0]);
	row = stoi(config_data[1]);
	width = stoi(config_data[0]) * 32;
	height = stoi(config_data[1]) * 32 + 100;
	num_mine = stoi(config_data[2]);
	texture = load_texture();
	num_remain = num_mine;
	num_flag = num_mine;
	pause_state = false;
	end_game = false;
	win = false;
	debug = false;
	time_elasped = 0;
	min = 0;
	sec = 0;
	pause_time = 0;
	leader_active = false;
	leader_needed = true;
	pause_start = chrono::high_resolution_clock::now();
	leader_start = chrono::high_resolution_clock::now();
	time_point1 = chrono::high_resolution_clock::now();
	for (int i = 0; i < col; i++)
	{
		vector<Tiles> temp_vec;
		vector<bool> temp_mine;
		for (int j = 0; j < row; j++)
		{
			Tiles temp_tiles(i * 32, j * 32, texture["tile_hidden"]);
			temp_vec.push_back(temp_tiles);
			temp_mine.push_back(false);
		}
		mine_vec.push_back(temp_vec);
		mine_map.push_back(temp_mine);
	}

	auto rand_time2 = chrono::high_resolution_clock::now();
	unsigned int rand_seed = chrono::duration_cast<chrono::milliseconds>(rand_time2 - rand_time1).count();
	srand(rand_seed);
	for (int i = 0; i < num_mine; i++)
	{
		GenerateMine();
	}
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			if (mine_map[i][j])
			{
				mine_vec[i][j].mine_state = true;
			}
		}
	}
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			if (mine_vec[i][j].mine_state)
			{
				if (i > 0 && i < col - 1 && j > 0 && j < row - 1)
				{
					mine_vec[i - 1][j].counter += 1;
					mine_vec[i - 1][j - 1].counter += 1;
					mine_vec[i - 1][j + 1].counter += 1;
					mine_vec[i][j - 1].counter += 1;
					mine_vec[i][j + 1].counter += 1;
					mine_vec[i + 1][j].counter += 1;
					mine_vec[i + 1][j - 1].counter += 1;
					mine_vec[i + 1][j + 1].counter += 1;
				}
				else if (i == 0 && i < col - 1 && j > 0 && j < row - 1)
				{
					mine_vec[i][j - 1].counter += 1;
					mine_vec[i][j + 1].counter += 1;
					mine_vec[i + 1][j].counter += 1;
					mine_vec[i + 1][j - 1].counter += 1;
					mine_vec[i + 1][j + 1].counter += 1;
				}
				else if (i > 0 && i == col - 1 && j > 0 && j < row - 1)
				{
					mine_vec[i - 1][j].counter += 1;
					mine_vec[i - 1][j - 1].counter += 1;
					mine_vec[i - 1][j + 1].counter += 1;
					mine_vec[i][j - 1].counter += 1;
					mine_vec[i][j + 1].counter += 1;
				}
				else if (i == 0 && i < col - 1 && j == 0 && j < row - 1)
				{
					mine_vec[i][j + 1].counter += 1;
					mine_vec[i + 1][j].counter += 1;
					mine_vec[i + 1][j + 1].counter += 1;
				}
				else if (i == 0 && i < col - 1 && j > 0 && j == row - 1)
				{
					mine_vec[i][j - 1].counter += 1;
					mine_vec[i + 1][j].counter += 1;
					mine_vec[i + 1][j - 1].counter += 1;
				}
				else if (i > 0 && i == col - 1 && j == 0 && j < row - 1)
				{
					mine_vec[i - 1][j].counter += 1;
					mine_vec[i - 1][j + 1].counter += 1;
					mine_vec[i][j + 1].counter += 1;
				}
				else if (i > 0 && i == col - 1 && j > 0 && j == row - 1)
				{
					mine_vec[i - 1][j].counter += 1;
					mine_vec[i - 1][j - 1].counter += 1;
					mine_vec[i][j - 1].counter += 1;
				}
				else if (i > 0 && i < col - 1 && j == 0 && j < row - 1)
				{
					mine_vec[i - 1][j].counter += 1;
					mine_vec[i - 1][j + 1].counter += 1;
					mine_vec[i][j + 1].counter += 1;
					mine_vec[i + 1][j].counter += 1;
					mine_vec[i + 1][j + 1].counter += 1;
				}
				else if (i > 0 && i < col - 1 && j > 0 && j == row - 1)
				{
					mine_vec[i - 1][j].counter += 1;
					mine_vec[i - 1][j - 1].counter += 1;
					mine_vec[i][j - 1].counter += 1;
					mine_vec[i + 1][j].counter += 1;
					mine_vec[i + 1][j - 1].counter += 1;
				}
			}
		}
	}
}

void GameWindow::GenerateMine()
{
	int temp_x = rand() % col;
	int temp_y = rand() % row;
	if (!mine_map[temp_x][temp_y])
	{
		mine_map[temp_x][temp_y] = true;
	}
	else
	{
		GenerateMine();
	}
}

void GameWindow::RevealMine(int x, int y)
{	
	if (!mine_vec[x][y].reveal_state && !mine_vec[x][y].flag_state)
	{
		mine_vec[x][y].reveal_tile(texture["tile_revealed"]);
		sf::Sprite reveal_sprite;
		reveal_sprite.setTexture(texture["tile_revealed"]);
		reveal_sprite.setPosition(x * 32, y * 32);
		extra_sprite.push_back(reveal_sprite);
		if (mine_vec[x][y].mine_state)
		{
			sf::Sprite temp_sprite;
			temp_sprite.setTexture(texture["mine"]);
			temp_sprite.setPosition(x * 32, y * 32);
			extra_sprite.push_back(temp_sprite);
		}
		else
		{
			sf::Sprite temp_sprite;
			if (mine_vec[x][y].counter == 1)
			{
				temp_sprite.setTexture(texture["number_1"]);
				temp_sprite.setPosition(x * 32, y * 32);
				extra_sprite.push_back(temp_sprite);
			}
			else if (mine_vec[x][y].counter == 2)
			{
				temp_sprite.setTexture(texture["number_2"]);
				temp_sprite.setPosition(x * 32, y * 32);
				extra_sprite.push_back(temp_sprite);
			}
			else if (mine_vec[x][y].counter == 3)
			{
				temp_sprite.setTexture(texture["number_3"]);
				temp_sprite.setPosition(x * 32, y * 32);
				extra_sprite.push_back(temp_sprite);
			}
			else if (mine_vec[x][y].counter == 4)
			{
				temp_sprite.setTexture(texture["number_4"]);
				temp_sprite.setPosition(x * 32, y * 32);
				extra_sprite.push_back(temp_sprite);
			}
			else if (mine_vec[x][y].counter == 5)
			{
				temp_sprite.setTexture(texture["number_5"]);
				temp_sprite.setPosition(x * 32, y * 32);
				extra_sprite.push_back(temp_sprite);
			}
			else if (mine_vec[x][y].counter == 6)
			{
				temp_sprite.setTexture(texture["number_6"]);
				temp_sprite.setPosition(x * 32, y * 32);
				extra_sprite.push_back(temp_sprite);
			}
			else if (mine_vec[x][y].counter == 7)
			{
				temp_sprite.setTexture(texture["number_7"]);
				temp_sprite.setPosition(x * 32, y * 32);
				extra_sprite.push_back(temp_sprite);
			}
			else if (mine_vec[x][y].counter == 8)
			{
				temp_sprite.setTexture(texture["number_8"]);
				temp_sprite.setPosition(x * 32, y * 32);
				extra_sprite.push_back(temp_sprite);
			}
			else if (mine_vec[x][y].counter == 0)
			{
				if (x > 0 && x < col - 1 && y > 0 && y < row - 1)
				{
					RevealMine(x - 1, y);
					RevealMine((x - 1), (y - 1));
					RevealMine(x - 1, y + 1);
					RevealMine(x, y - 1);
					RevealMine(x, y + 1);
					RevealMine(x + 1, y);
					RevealMine(x + 1, y - 1);
					RevealMine(x + 1, y + 1);

				}
				else if (x == 0 && x < col - 1 && y > 0 && y < row - 1)
				{
					RevealMine(x, y - 1);
					RevealMine(x, y + 1);
					RevealMine(x + 1, y);
					RevealMine(x + 1, y - 1);
					RevealMine(x + 1, y + 1);
				}
				else if (x > 0 && x == col - 1 && y > 0 && y < row - 1)
				{
					RevealMine(x - 1, y);
					RevealMine((x - 1), (y - 1));
					RevealMine(x - 1, y + 1);
					RevealMine(x, y - 1);
					RevealMine(x, y + 1);
				}
				else if (x == 0 && x < col - 1 && y == 0 && y < row - 1)
				{
					RevealMine(x, y + 1);
					RevealMine(x + 1, y);
					RevealMine(x + 1, y + 1);
				}
				else if (x == 0 && x < col - 1 && y > 0 && y == row - 1)
				{
					RevealMine(x, y - 1);
					RevealMine(x + 1, y);
					RevealMine(x + 1, y - 1);
				}
				else if (x > 0 && x == col - 1 && y == 0 && y < row - 1)
				{
					RevealMine(x - 1, y);
					RevealMine(x - 1, y + 1);
					RevealMine(x, y + 1);
				}
				else if (x > 0 && x == col - 1 && y > 0 && y == row - 1)
				{

					RevealMine(x - 1, y);
					RevealMine((x - 1), (y - 1));
					RevealMine(x, y - 1);
				}
				else if (x > 0 && x < col - 1 && y == 0 && y < row - 1)
				{
					RevealMine(x - 1, y);
					RevealMine(x - 1, y + 1);
					RevealMine(x, y + 1);
					RevealMine(x + 1, y);
					RevealMine(x + 1, y + 1);
				}
				else if (x > 0 && x < col - 1 && y > 0 && y == row - 1)
				{
					RevealMine(x - 1, y);
					RevealMine((x - 1), (y - 1));
					RevealMine(x, y - 1);
					RevealMine(x + 1, y);
					RevealMine(x + 1, y - 1);
				}
			}
		}
	}
}

bool GameWindow::CheckWin()
{
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			if (!mine_vec[i][j].mine_state && !mine_vec[i][j].reveal_state)
			{
				return false;
			}
		}
	}
	return true;
}

void GameWindow::DigitUpdate(int temp_digit, sf::Sprite &temp_sprite)
{
	temp_sprite.setTextureRect(sf::IntRect(temp_digit * 21, 0, 21, 32));
}

void GameWindow::Display()
{
	Leaderboard leader;

	sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close | sf::Style::Titlebar);
	sf::RectangleShape shape;
	shape.setFillColor(sf::Color::White);
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(0, 0);

	sf::RectangleShape background;
	background.setFillColor(sf::Color::White);
	background.setSize(sf::Vector2f(width, height));
	background.setPosition(0, 0);

	sf::Sprite happy_face;
	happy_face.setTexture(texture["face_happy"]);
	happy_face.setPosition(col / 2 * 32 - 32, 32 * (row + 0.5));

	sf::Sprite debug_button;
	debug_button.setTexture(texture["debug"]);
	debug_button.setPosition(col * 32 - 304, 32 * (row + 0.5));

	sf::Sprite pause_play;
	pause_play.setTexture(texture["pause"]);
	pause_play.setPosition(col * 32 - 240, 32 * (row + 0.5));

	sf::Sprite leaderboard;
	leaderboard.setTexture(texture["leaderboard"]);
	leaderboard.setPosition(col * 32 - 176, 32 * (row + 0.5));

	sf::Sprite counter_1;
	counter_1.setTexture(texture["digits"]);
	DigitUpdate(floor(abs(num_flag) / 100), counter_1);
	counter_1.setPosition(33, 32 * (row + 0.5) + 16);

	sf::Sprite counter_2;
	counter_2.setTexture(texture["digits"]);
	int update_num = floor(abs(num_flag) / 10);
	if (update_num > 9)
	{
		DigitUpdate(update_num % 10, counter_2);
	}
	else
	{
		DigitUpdate(update_num, counter_2);
	}
	counter_2.setPosition(54, 32 * (row + 0.5) + 16);

	sf::Sprite counter_3;
	counter_3.setTexture(texture["digits"]);
	DigitUpdate(abs(num_flag) % 10 % 10, counter_3);
	counter_3.setPosition(75, 32 * (row + 0.5) + 16);

	sf::Sprite counter_4;
	counter_4.setTexture(texture["digits"]);
	counter_4.setTextureRect(sf::IntRect(210, 0, 21, 32));
	counter_4.setPosition(12, 32 * (row + 0.5) + 16);

	sf::RectangleShape neg_cover;
	neg_cover.setFillColor(sf::Color::White);
	neg_cover.setSize(sf::Vector2f(21, 32));
	neg_cover.setPosition(12, 32 * (row + 0.5) + 16);

	sf::Sprite timer_1;
	timer_1.setTexture(texture["digits"]);
	timer_1.setTextureRect(sf::IntRect(0, 0, 21, 32));
	timer_1.setPosition(col * 32 - 97, 32 * (row + 0.5) + 16);

	sf::Sprite timer_2;
	timer_2.setTexture(texture["digits"]);
	timer_2.setTextureRect(sf::IntRect(0, 0, 21, 32));
	timer_2.setPosition(col * 32 - 76, 32 * (row + 0.5) + 16);

	sf::Sprite timer_3;
	timer_3.setTexture(texture["digits"]);
	timer_3.setTextureRect(sf::IntRect(0, 0, 21, 32));
	timer_3.setPosition(col * 32 - 54, 32 * (row + 0.5) + 16);

	sf::Sprite timer_4;
	timer_4.setTexture(texture["digits"]);
	timer_4.setTextureRect(sf::IntRect(0, 0, 21, 32));
	timer_4.setPosition(col * 32 - 33, 32 * (row + 0.5) + 16);

	while (window.isOpen())
	{
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				if (localPosition.x > 0 && localPosition.x <= width && localPosition.y > 0 && localPosition.y <= height && !end_game)
				{
					if ((float)localPosition.x / 32.0f <= col && (float)localPosition.y / 32.0f <= row && !mine_vec[floor(localPosition.x / 32.0f)][floor(localPosition.y / 32.0f)].flag_state && !pause_state)
					{
						try
						{
							RevealMine(floor(localPosition.x / 32.0f), floor(localPosition.y / 32.0f));
							if (mine_vec[floor(localPosition.x / 32.0f)][floor(localPosition.y / 32.0f)].mine_state)
							{
								end_game = true;
								win = false;
								for (int i = 0; i < col; i++)
								{
									for (int j = 0; j < row; j++)
									{
										if (mine_vec[i][j].mine_state)
										{
											RevealMine(i, j);
										}
									}
								}
							}
						}
						catch (...) {}
					}
				}
				if (localPosition.x <= pause_play.getPosition().x + pause_play.getLocalBounds().width && localPosition.x >= pause_play.getPosition().x && !end_game)
				{
					if (localPosition.y <= pause_play.getPosition().y + pause_play.getLocalBounds().height && localPosition.y >= pause_play.getPosition().y)
					{
						if (!pause_state )
						{
							pause_start = chrono::high_resolution_clock::now();
							pause_state = true;
							pause_play.setTexture(texture["play"]);
						}
						else
						{
							auto pause_end = chrono::high_resolution_clock::now();
							pause_time += chrono::duration_cast<chrono::seconds>(pause_end - pause_start).count();
							pause_state = false;
							pause_play.setTexture(texture["pause"]);
						}
					}
				}
				if (localPosition.x <= debug_button.getPosition().x + debug_button.getLocalBounds().width && localPosition.x >= debug_button.getPosition().x && !end_game)
				{
					if (localPosition.y <= debug_button.getPosition().y + debug_button.getLocalBounds().height && localPosition.y >= debug_button.getPosition().y)
					{
						if (!pause_state)
						{
							if (!debug)
							{
								debug = true;
							}
							else
							{
								debug = false;
							}
						}
					}
				}
				if (localPosition.x <= happy_face.getPosition().x + happy_face.getLocalBounds().width && localPosition.x >= happy_face.getPosition().x)
				{
					if (localPosition.y <= happy_face.getPosition().y + happy_face.getLocalBounds().height && localPosition.y >= happy_face.getPosition().y)
					{
						num_remain = num_mine;
						num_flag = num_mine;
						pause_state = false;
						end_game = false;
						win = false;
						debug = false;
						mine_vec = {};
						mine_map = {};
						extra_sprite = {};
						time_elasped = 0;
						min = 0;
						sec = 0;
						pause_time = 0;
						leader_active = false;
						leader_needed = true;
						pause_start = chrono::high_resolution_clock::now();
						leader_start = chrono::high_resolution_clock::now();
						time_point1 = chrono::high_resolution_clock::now();

						happy_face.setTexture(texture["face_happy"]);
						debug_button.setTexture(texture["debug"]);
						pause_play.setTexture(texture["pause"]);
						leaderboard.setTexture(texture["leaderboard"]);
						DigitUpdate(floor(abs(num_flag) / 100), counter_1);
						DigitUpdate(abs(num_flag) % 10 % 10, counter_3);
						counter_4.setTextureRect(sf::IntRect(210, 0, 21, 32));
						neg_cover.setPosition(12, 32 * (row + 0.5) + 16);
						timer_1.setTextureRect(sf::IntRect(0, 0, 21, 32));
						timer_2.setTextureRect(sf::IntRect(0, 0, 21, 32));
						timer_3.setTextureRect(sf::IntRect(0, 0, 21, 32));
						timer_4.setTextureRect(sf::IntRect(0, 0, 21, 32));

						int update_num = floor(abs(num_flag) / 10);
						if (update_num > 9)
						{
							DigitUpdate(update_num % 10, counter_2);
						}
						else
						{
							DigitUpdate(update_num, counter_2);
						}

						for (int i = 0; i < col; i++)
						{
							vector<Tiles> temp_vec;
							vector<bool> temp_mine;
							for (int j = 0; j < row; j++)
							{
								Tiles temp_tiles(i * 32, j * 32, texture["tile_hidden"]);
								temp_vec.push_back(temp_tiles);
								temp_mine.push_back(false);
							}
							mine_vec.push_back(temp_vec);
							mine_map.push_back(temp_mine);
						}

						auto rand_time2 = chrono::high_resolution_clock::now();
						int rand_seed = chrono::duration_cast<chrono::milliseconds>(rand_time2 - rand_time1).count();
						srand(rand_seed);
						for (int i = 0; i < num_mine; i++)
						{
							GenerateMine();
						}
						for (int i = 0; i < col; i++)
						{
							for (int j = 0; j < row; j++)
							{
								if (mine_map[i][j])
								{
									mine_vec[i][j].mine_state = true;
								}
							}
						}
						for (int i = 0; i < col; i++)
						{
							for (int j = 0; j < row; j++)
							{
								if (mine_vec[i][j].mine_state)
								{
									if (i > 0 && i < col - 1 && j > 0 && j < row - 1)
									{
										mine_vec[i - 1][j].counter += 1;
										mine_vec[i - 1][j - 1].counter += 1;
										mine_vec[i - 1][j + 1].counter += 1;
										mine_vec[i][j - 1].counter += 1;
										mine_vec[i][j + 1].counter += 1;
										mine_vec[i + 1][j].counter += 1;
										mine_vec[i + 1][j - 1].counter += 1;
										mine_vec[i + 1][j + 1].counter += 1;
									}
									else if (i == 0 && i < col - 1 && j > 0 && j < row - 1)
									{
										mine_vec[i][j - 1].counter += 1;
										mine_vec[i][j + 1].counter += 1;
										mine_vec[i + 1][j].counter += 1;
										mine_vec[i + 1][j - 1].counter += 1;
										mine_vec[i + 1][j + 1].counter += 1;
									}
									else if (i > 0 && i == col - 1 && j > 0 && j < row - 1)
									{
										mine_vec[i - 1][j].counter += 1;
										mine_vec[i - 1][j - 1].counter += 1;
										mine_vec[i - 1][j + 1].counter += 1;
										mine_vec[i][j - 1].counter += 1;
										mine_vec[i][j + 1].counter += 1;
									}
									else if (i == 0 && i < col - 1 && j == 0 && j < row - 1)
									{
										mine_vec[i][j + 1].counter += 1;
										mine_vec[i + 1][j].counter += 1;
										mine_vec[i + 1][j + 1].counter += 1;
									}
									else if (i == 0 && i < col - 1 && j > 0 && j == row - 1)
									{
										mine_vec[i][j - 1].counter += 1;
										mine_vec[i + 1][j].counter += 1;
										mine_vec[i + 1][j - 1].counter += 1;
									}
									else if (i > 0 && i == col - 1 && j == 0 && j < row - 1)
									{
										mine_vec[i - 1][j].counter += 1;
										mine_vec[i - 1][j + 1].counter += 1;
										mine_vec[i][j + 1].counter += 1;
									}
									else if (i > 0 && i == col - 1 && j > 0 && j == row - 1)
									{
										mine_vec[i - 1][j].counter += 1;
										mine_vec[i - 1][j - 1].counter += 1;
										mine_vec[i][j - 1].counter += 1;
									}
									else if (i > 0 && i < col - 1 && j == 0 && j < row - 1)
									{
										mine_vec[i - 1][j].counter += 1;
										mine_vec[i - 1][j + 1].counter += 1;
										mine_vec[i][j + 1].counter += 1;
										mine_vec[i + 1][j].counter += 1;
										mine_vec[i + 1][j + 1].counter += 1;
									}
									else if (i > 0 && i < col - 1 && j > 0 && j == row - 1)
									{
										mine_vec[i - 1][j].counter += 1;
										mine_vec[i - 1][j - 1].counter += 1;
										mine_vec[i][j - 1].counter += 1;
										mine_vec[i + 1][j].counter += 1;
										mine_vec[i + 1][j - 1].counter += 1;
									}
								}
							}
						}
					}
				}
				if (localPosition.x <= leaderboard.getPosition().x + leaderboard.getLocalBounds().width && localPosition.x >= leaderboard.getPosition().x)
				{
					if (localPosition.y <= leaderboard.getPosition().y + leaderboard.getLocalBounds().height && localPosition.y >= leaderboard.getPosition().y)
					{
						if (!leader_active)
						{	
							leader_active = true;
							for (int i = 0; i < col; i++)
							{
								for (int j = 0; j < row; j++)
								{
									sf::Sprite temp_cover;
									temp_cover.setTexture(texture["tile_revealed"]);
									temp_cover.setPosition(i * 32, j * 32);
									window.draw(temp_cover);
								}
							}
							leader_start = chrono::high_resolution_clock::now();
							pause_time += chrono::duration_cast<chrono::seconds>(leader.Display() - leader_start).count();
							window.display();
							leader_active = false;
						}
					}
				}
			}
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
			{
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				if (localPosition.x > 0 && localPosition.x <= width && localPosition.y > 0 && localPosition.y <= height)
				{
					if ((float)localPosition.x / 32.0f <= col && (float)localPosition.y / 32.0f <= row && !mine_vec[floor(localPosition.x / 32.0f)][floor(localPosition.y / 32.0f)].reveal_state && !pause_state && !end_game)
					{
						try
						{
							sf::Sprite temp_sprite;
							if (!mine_vec[floor(localPosition.x / 32.0f)][floor(localPosition.y / 32.0f)].flag_state)
							{
								temp_sprite.setTexture(texture["flag"]);
								temp_sprite.setPosition(floor(localPosition.x / 32.0f) * 32, floor(localPosition.y / 32.0f) * 32);
								mine_vec[floor(localPosition.x / 32.0f)][floor(localPosition.y / 32.0f)].flag_state = true;
								extra_sprite.push_back(temp_sprite);
								num_flag -= 1;
								DigitUpdate(floor(abs(num_flag) / 100), counter_1);
								DigitUpdate(abs(num_flag) % 10 % 10, counter_3);
								if (num_flag < 0)
								{
									update_num = floor(-num_flag / 10);
									neg_cover.move(0, 32);
								}
								else
								{
									update_num = floor(num_flag / 10);
									neg_cover.setPosition(12, 32 * (row + 0.5) + 16);
								}
								if (update_num > 9)
								{
									DigitUpdate(update_num % 10, counter_2);
								}
								else
								{
									DigitUpdate(update_num, counter_2);
								}
							}
							else
							{
								temp_sprite.setTexture(texture["tile_hidden"]);
								temp_sprite.setPosition(floor(localPosition.x / 32.0f) * 32, floor(localPosition.y / 32.0f) * 32);
								mine_vec[floor(localPosition.x / 32.0f)][floor(localPosition.y / 32.0f)].flag_state = false;
								extra_sprite.push_back(temp_sprite);
								num_flag += 1;
								DigitUpdate(floor(abs(num_flag) / 100), counter_1);
								DigitUpdate(abs(num_flag) % 10 % 10, counter_3);
								if (num_flag < 0)
								{
									update_num = floor(-num_flag / 10);
									neg_cover.move(0, 32);
								}
								else
								{
									update_num = floor(num_flag / 10);
									neg_cover.setPosition(12, 32 * (row + 0.5) + 16);
								}
								if (update_num > 9)
								{
									DigitUpdate(update_num % 10, counter_2);
								}
								else
								{
									DigitUpdate(update_num, counter_2);
								}
							}
						}
						catch (...) {}
					}
				}
			}
		}
		auto temp_time = chrono::high_resolution_clock::now();
		time_elasped = chrono::duration_cast<chrono::seconds>(temp_time - time_point1).count() - pause_time;
		sec = time_elasped % 60;
		min = floor(time_elasped / 60);

		if (!end_game && !pause_state)
		{
			DigitUpdate(floor(min / 10.0f), timer_1);
			DigitUpdate(min % 10, timer_2);
			DigitUpdate(floor(sec / 10.0f), timer_3);
			DigitUpdate(sec % 10, timer_4);
		}
		else if (end_game)
		{
			DigitUpdate(0, counter_1);
			DigitUpdate(0, counter_2);
			DigitUpdate(0, counter_3);
			DigitUpdate(0, counter_4);
		}

		window.clear();
		window.draw(background);
		window.draw(happy_face);
		window.draw(debug_button);
		window.draw(pause_play);
		window.draw(leaderboard);
		window.draw(counter_1);
		window.draw(counter_2);
		window.draw(counter_3);
		window.draw(counter_4);
		window.draw(neg_cover);
		window.draw(timer_1);
		window.draw(timer_2);
		window.draw(timer_3);
		window.draw(timer_4);
		for (int i = 0; i < col; i++)
		{
			for (int j = 0; j < row; j++)
			{
				window.draw(mine_vec[i][j].sprite);
			}
		}
		for (auto iter = extra_sprite.begin(); iter < extra_sprite.end(); iter++)
		{
			window.draw(*iter);
		}
		if (pause_state)
		{
			for (int i = 0; i < col; i++)
			{
				for (int j = 0; j < row; j++)
				{
					sf::Sprite temp_cover;
					temp_cover.setTexture(texture["tile_revealed"]);
					temp_cover.setPosition(i * 32, j * 32);
					window.draw(temp_cover);
				}
			}
		}
		win = CheckWin();
		if (end_game && !win)
		{
			happy_face.setTexture(texture["face_lose"]);
			for (int i = 0; i < col; i++)
			{
				for (int j = 0; j < row; j++)
				{
					if (mine_vec[i][j].mine_state)
					{
						sf::Sprite cover_mine;
						cover_mine.setTexture(texture["mine"]);
						cover_mine.setPosition(i * 32, j * 32);
						window.draw(cover_mine);
					}
				}
			}
		}
		else if (win)
		{
			end_game = true;
			happy_face.setTexture(texture["face_win"]);

			for (int i = 0; i < col; i++)
			{
				for (int j = 0; j < row; j++)
				{
					if (mine_vec[i][j].mine_state)
					{
						sf::Sprite cover_flag;
						cover_flag.setTexture(texture["flag"]);
						cover_flag.setPosition(i * 32, j * 32);
						window.draw(cover_flag);
					}
				}
			}

			if (leader_needed)
			{
				vector<string> temp_record;
				if (min < 10)
				{
					temp_record.push_back("0" + to_string(min));
				}
				else
				{
					temp_record.push_back(to_string(min));
				}
				if (sec < 10)
				{
					temp_record.push_back("0" + to_string(sec));
				}
				else
				{
					temp_record.push_back(to_string(sec));
				}
				temp_record.push_back(name);
				leader.leader_string.push_back(temp_record);

				window.draw(happy_face);
				window.display();
				leader.Display();
				leader_needed = false;
			}

		}
		if (debug)
		{
			for (int i = 0; i < col; i++)
			{
				for (int j = 0; j < row; j++)
				{
					if (mine_vec[i][j].mine_state)
					{
						sf::Sprite cover_mine;
						cover_mine.setTexture(texture["mine"]);
						cover_mine.setPosition(i * 32, j * 32);
						window.draw(cover_mine);
					}
				}
			}
		}
		window.display();
	}
}

Leaderboard::Leaderboard()
{
	vector<string> config_data;
	import_config(config_data);
	ifstream read_file("files/leaderboard.txt");

	width = stoi(config_data[0]) * 16;
	height = stoi(config_data[1]) * 16 + 50;

	for (int i = 0; i < 5; i++)
	{
		vector<string> temp_leader;
		string singleLine;
		getline(read_file, singleLine);
		istringstream stream(singleLine);
		string token;
		string time;
		string min;
		string sec;
		string name;

		getline(stream, token, ',');
		time = token;
		istringstream time_stream(time);
		string temp_time;
		getline(time_stream, temp_time, ':');
		min = temp_time;
		getline(time_stream, temp_time, ':');
		sec = temp_time;

		getline(stream, token, ',');
		name = token;

		temp_leader.push_back(min);
		temp_leader.push_back(sec);
		temp_leader.push_back(name);
		leader_string.push_back(temp_leader);
	}
}

void Leaderboard::leader_sort()
{
	if (leader_string.size() > 5)
	{
		for (int i = 0; i < leader_string.size() - 1; i++)
		{
			if (leader_string[5][2] == leader_string[i][2])
			{
				int temp_time1 = stoi(leader_string[i][0]) * 60 + stoi(leader_string[i][1]);
				int temp_time2 = stoi(leader_string[5][0]) * 60 + stoi(leader_string[5][1]);
				if (temp_time2 < temp_time1)
				{
					leader_string[i][0] = leader_string[5][0];
					leader_string[i][1] = leader_string[5][1];
					leader_string.pop_back();
					break;
				}
				else
				{
					leader_string.pop_back();
					break;
				}
			}
		}
	}
	if (leader_string.size() > 5)
	{
		leader_string[5][2] += "*";
	}
	bool stop_sort = false;
	while (!stop_sort)
	{
		stop_sort = true;
		for (int i = 0; i < leader_string.size() - 1; i++)
		{
			int temp_time1 = stoi(leader_string[i][0]) * 60 + stoi(leader_string[i][1]);
			int temp_time2 = stoi(leader_string[i + 1][0]) * 60 + stoi(leader_string[i + 1][1]);
			if (temp_time2 < temp_time1)
			{
				vector<string> temp_vec = leader_string[i + 1];
				leader_string[i + 1] = leader_string[i];
				leader_string[i] = temp_vec;
				stop_sort = false;
			}
		}
	}
	if (leader_string.size() > 5)
	{
		leader_string.pop_back();
	}
}

chrono::steady_clock::time_point Leaderboard::Display()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close | sf::Style::Titlebar);
	sf::RectangleShape shape;
	shape.setFillColor(sf::Color::Blue);
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(0, 0);

	leader_sort();
	string temp_text = "1.\t" + leader_string[0][0] + ":" + leader_string[0][1] + '\t' + leader_string[0][2];
	temp_text += "\n\n2.\t" + leader_string[1][0] + ":" + leader_string[1][1] + '\t' + leader_string[1][2];
	temp_text += "\n\n3.\t" + leader_string[2][0] + ":" + leader_string[2][1] + '\t' + leader_string[2][2];
	temp_text += "\n\n4.\t" + leader_string[3][0] + ":" + leader_string[3][1] + '\t' + leader_string[3][2];
	temp_text += "\n\n5.\t" + leader_string[4][0] + ":" + leader_string[4][1] + '\t' + leader_string[4][2];


	sf::Font font;
	font.loadFromFile("files/font.ttf");

	sf::Text leader_title;
	leader_title.setFont(font);
	leader_title.setStyle(sf::Text::Underlined | sf::Text::Bold);
	leader_title.setString("LEADERBOARD");
	leader_title.setCharacterSize(20);
	leader_title.setFillColor(sf::Color::White);
	setText(leader_title, width / 2, height / 2 - 120);

	sf::Text leader_text1;
	leader_text1.setFont(font);
	leader_text1.setStyle(sf::Text::Bold);
	leader_text1.setString(temp_text);
	leader_text1.setCharacterSize(18);
	leader_text1.setFillColor(sf::Color::White);
	setText(leader_text1, width / 2, height / 2 + 20);

	for (int i = 0; i < 5; i++)
	{
		if (leader_string[i][2].substr(leader_string[i][2].size()-1, 1) == "*")
		{
			leader_string[i][2].pop_back();
		}
	}

	ofstream write_file("files/leaderboard.txt");
	for (int i = 0; i < 5; i++)
	{
		string temp_write = leader_string[i][0] + ":" + leader_string[i][1] + "," + leader_string[i][2];
		write_file << temp_write << endl;
	}
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				auto leader_end = chrono::high_resolution_clock::now();
				return leader_end;
			}
		}
		window.clear();
		window.draw(shape);
		window.draw(leader_title);
		window.draw(leader_text1);
		window.display();
	}
}

Tiles::Tiles(float x, float y, sf::Texture &temp_texture)
{
	mine_state = 0;
	counter = 0;
	flag_state = 0;
	reveal_state = 0;
	sprite.setTexture(temp_texture);
	sprite.setPosition(x, y);
}

void Tiles::reveal_tile(sf::Texture& temp_texture)
{
	sprite.setTexture(temp_texture);
	reveal_state = true;
}
