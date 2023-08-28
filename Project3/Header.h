#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <iterator>
#pragma once

using namespace std;
class WelcomeWindow
{
	float width;
	float height;

public:

	chrono::steady_clock::time_point rand_time1 = chrono::high_resolution_clock::now();
	WelcomeWindow();
	void Display();

};
struct Tiles
{
	bool mine_state;
	int counter;
	bool flag_state;
	bool reveal_state;
	sf::Sprite sprite;

	Tiles(float x, float y, sf::Texture &temp_texture);
	void reveal_tile(sf::Texture &temp_texture);
};
class GameWindow
{
	int col;
	int row;
	float width;
	float height;
	int num_mine;
	int num_remain;
	int num_flag;
	bool pause_state;
	bool end_game;
	bool win;
	bool debug;
	int time_elasped;
	int min;
	int sec;
	int pause_time;
	bool leader_active;
	bool leader_needed;
	string name;
	map<string, sf::Texture> texture;
	vector<vector<Tiles>> mine_vec;
	vector<vector<bool>> mine_map;
	chrono::steady_clock::time_point rand_time1;
	chrono::steady_clock::time_point time_point1;
	chrono::steady_clock::time_point pause_start;
	chrono::steady_clock::time_point leader_start;
	vector<sf::Sprite> extra_sprite;
public:
	GameWindow(chrono::steady_clock::time_point &rand_time, string name);
	void Display();
	void GenerateMine();
	void RevealMine(int x, int y);
	void DigitUpdate(int temp_digit, sf::Sprite &temp_sprite);
	bool CheckWin();
};
struct Leaderboard
{
	float width;
	float height;
	vector<vector<string>>leader_string;

public:
	Leaderboard();
	void leader_sort();
	chrono::steady_clock::time_point Display();
};

void import_config(vector<string> &config_data);
void setText(sf::Text& text, float x, float y);
map<string, sf::Texture> load_texture();


