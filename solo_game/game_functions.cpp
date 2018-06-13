#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <limits>
#include <fstream>
#include "game_functions.h"

int roll_die(int die_sides)
{
	int die_result = rand() % die_sides + 1;
	return die_result;
}
bool check_hit(int attack, int evasion)
{
	bool hit_result;
	int attack_roll = (roll_die(100) + attack);
	(attack_roll > evasion) ? hit_result = true : hit_result = false;
	return hit_result;
}
bool check_win(int health)
{
	bool win_occurs;
	if (health <= 0)
	{
		win_occurs = true;
	}
	else
	{
		win_occurs = false;
	}
	return win_occurs;
}
int check_damage(int damage, int defense, int condition_damage)
{
	int damage_result = (damage / defense) + condition_damage;
	return damage_result;
}
int reduce_health(int health, int damage)
{
	int health_result = health - damage;
	return health_result;
}
std::string get_profession(void)
{
	int player_profession_selection = 0;
	std::string player_profession;
	std::cin >> player_profession_selection;
	while (!std::cin >> player_profession_selection || player_profession_selection < 1 || player_profession_selection > 4)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "\n>  ";
		std::cin >> player_profession_selection;
	}

	switch (player_profession_selection)
	{
	case 1: player_profession = "warrior";
		break;
	case 2: player_profession = "rogue";
		break;
	case 3: player_profession = "mage";
		break;
	}
	return player_profession;
}
std::string get_story(int line_number)
{
	std::string line_contents;
	std::ifstream game_story;

	game_story.open("game_story.txt");
	if (game_story.is_open())
	{
		for (int i = 0; i < line_number; i++)
		{
			std::getline(game_story, line_contents);
		}
		game_story.close();
		return line_contents;
	}
	else
	{
		std::cout << "-  Please check if all files are included in game drectory.";
		return "File not found.";
	}
}
void read_story_block(int starting_line, int ending_line)
{
	for (int i = starting_line; i < ending_line + 1; i++)
	{
		std::cout << "\n" << get_story(i) << " ";
	}
	std::cin.get();
}
int get_evasion(std::string profession, int level)
{
	int evasion_result = 0;
	if (profession == "warrior")
	{
		evasion_result = 10 + (2 * level);
	}
	else if (profession == "mage")
	{
		evasion_result = 10 + (1 * level);
	}
	else if (profession == "rogue")
	{
		evasion_result = 10 + (4 * level);
	}
	else if (profession == "goblin")
	{
		evasion_result = 10 + (3 * (level / 2));
	}
	return evasion_result;
}
int get_attack(std::string profession, int level)
{
	int attack_result = 0;
	if (profession == "warrior")
	{
		attack_result = 10 + (2 * level);
	}
	else if (profession == "mage")
	{
		attack_result = 10 + (3 * level);
	}
	else if (profession == "rogue")
	{
		attack_result = 10 + (4 * level);
	}
	else if (profession == "goblin")
	{
		attack_result = 10 + (3 * (level / 2));
	}
	return attack_result;
}
int get_maximum_health(std::string profession, int level)
{
	int get_maximum_health = 0;
	if (profession == "warrior")
	{
		get_maximum_health = 10 + (4 * level);
	}
	else if (profession == "mage")
	{
		get_maximum_health = 10 + (2 * level);
	}
	else if (profession == "rogue")
	{
		get_maximum_health = 10 + (3 * level);
	}
	else if (profession == "goblin")
	{
		get_maximum_health = 10 + (3 * (level / 2));
	}
	return get_maximum_health;
}
int get_defense(std::string profession, int level)
{
	int get_player_defense = 0;
	if (profession == "warrior")
	{
		get_player_defense = 10 + (4 * level);
	}
	else if (profession == "mage")
	{
		get_player_defense = 10 + (2 * level);
	}
	else if (profession == "rogue")
	{
		get_player_defense = 10 + (1 * level);
	}
	else if (profession == "goblin")
	{
		get_player_defense = 10 + (3 * (level / 2));
	}
	return get_player_defense;
}
int get_strength(std::string profession, int level)
{
	int get_strength = 0;
	if (profession == "warrior")
	{
		get_strength = 10 + (2 * level);
	}
	else if (profession == "mage")
	{
		get_strength = 10 + (4 * level);
	}
	else if (profession == "rogue")
	{
		get_strength = 10 + (1 * level);
	}
	else if (profession == "goblin")
	{
		get_strength = 10 + (3 * (level / 2));
	}
	return get_strength;
}