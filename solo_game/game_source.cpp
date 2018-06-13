#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <limits>
#include <fstream>

int roll_die(int);
bool check_hit(int, int);
int check_damage(int, int, int);
int reduce_health(int health, int damage);
std::string get_profession(void);
std::string get_story(int);
void read_story_block(int starting_line, int ending_line);
int get_evasion(std::string profession, int level);
int get_attack(std::string profession, int level);
int get_maximum_health(std::string profession, int level);
int get_defense(std::string profession, int level);
int get_strength(std::string profession, int level);


void main()
{
	int player_experience;
	int player_level = 0;
	int player_conditions = 0;
	int player_evasion = 0;
	int player_attack = 0;
	int player_current_health = 0;
	int player_defense = 0;
	int player_strength = 0;
	int player_maximum_health = 0;
	int player_condition_damage = 0;
	int enemy_level = 0;
	int enemy_conditions = 0;
	int enemy_evasion = 0;
	int enemy_current_health = 0;
	int enemy_attack = 0;
	int enemy_defense = 0;
	int enemy_strength = 0;
	int enemy_maximum_health = 0;
	int enemy_condition_damage = 0;
	int damage_this_turn = 0;
	int damage_roll = 0;
	std::string player_name;
	std::string enemy_name;
	std::string enemy_profession;
	std::string player_profession;
	std::string divider = "\n\n\n\n\n";
	bool attack_succeeds = true;
	bool is_player_turn = true;
	bool combat_continues = true;
	bool player_wins = false;
	bool enemy_wins = false;

	srand((unsigned int)time(NULL));

	std::cout << "-  What is your name, brave adventurer?\n\n>  ";
	std::cin >> player_name;
	std::cout << divider;
	std::cout << "-  Which profession strikes your fancy?\n\n1) Warrior\n2) Rogue\n3) Mage\n\n>  ";
	player_profession = get_profession();
	std::cout << divider << "-- ATTACK & PROTECC! : A TALE OF TWO LULZ -- ";
	std::cin.get();
	std::cin.ignore();
	std::cout << "\n";
		
	read_story_block(1, 3);
	read_story_block(4, 4);
	read_story_block(5, 5);
	std::cout << "\n\n\n";

	player_level = 30;
	player_evasion = get_evasion(player_profession, player_level);
	player_attack = get_attack(player_profession, player_level);
	player_maximum_health = get_maximum_health(player_profession, player_level);
	player_defense = get_defense(player_profession, player_level);
	player_strength = get_strength(player_profession, player_level);
	player_current_health = player_maximum_health;

	enemy_name = "Goblin Recruit";
	enemy_profession = "goblin";
	enemy_level = 30;
	enemy_evasion = get_evasion(enemy_profession, enemy_level);
	enemy_attack = get_attack(enemy_profession, enemy_level);
	enemy_maximum_health = get_maximum_health(enemy_profession, enemy_level);
	enemy_defense = get_defense(enemy_profession, enemy_level);
	enemy_strength = get_strength(enemy_profession, enemy_level);
	enemy_current_health = enemy_maximum_health;

	while (combat_continues)
	{
		if (is_player_turn)
		{
			std::cout << "\n\n-  [" << enemy_name << " | " << enemy_level << "]\n\t\t\t\t" << enemy_current_health << "  |  " << enemy_conditions;
			std::cout << "\n\n   [" << player_name << " | " << player_level << "]\n\t\t\t\t" << player_current_health << "  |  " << enemy_conditions << " ";

			attack_succeeds = check_hit(player_attack, enemy_evasion);
			(attack_succeeds) ? damage_roll = 5 * (roll_die(100) + player_strength) : damage_roll = 0;
			player_condition_damage = player_conditions * 2;
			enemy_condition_damage = enemy_conditions * 2;
			damage_this_turn = check_damage(damage_roll, enemy_defense, enemy_condition_damage);

			player_current_health = reduce_health(player_current_health, player_condition_damage);
			enemy_current_health = reduce_health(enemy_current_health, damage_this_turn);
			(enemy_current_health <= 0) ? player_wins = true : player_wins = false;
			(player_current_health <= 0) ? enemy_wins = true : enemy_wins = false;

			std::cin.get();

			if (attack_succeeds)
			{
				std::cout << "\n\n-  " << player_name << " hit " << enemy_name << " for " << (damage_this_turn - enemy_condition_damage) << " damage. ";
			}
			else
			{
				std::cout << "\n-  " << player_name << " missed " << enemy_name << ", dealing no damage. ";
			}
			
			std::cin.get();
			if (player_conditions)
			{
				std::cout << "   " << player_name << " took " << player_condition_damage << " damage from status effects. ";
				std::cin.get();
			}
			if (enemy_conditions)
			{
				std::cout << "   " << enemy_name << " took " << enemy_condition_damage << " damage from status effects. ";
				std::cin.get();
			}
			if (player_wins && enemy_wins)
			{
				std::cout << "\n-  In a twist of fate, you have slain one another! The quest ends with you. ";
				combat_continues = false;
			}
			else
			{
				if (player_wins)
				{
					std::cout << "\n-  " << player_name << " has slain " << enemy_name << "! ";
					combat_continues = false;
				}
				if (enemy_wins)
				{
					std::cout << "\n- " << player_name << " has been slain by " << enemy_name << "! ";
					combat_continues = false;
				}
			}
			
			is_player_turn = false;
			
		}
		else
		{
			attack_succeeds = check_hit(enemy_attack, player_evasion);
			(attack_succeeds) ? damage_roll = 5 * (roll_die(100) + player_strength) : damage_roll = 0;
			player_condition_damage = player_conditions * 2;
			enemy_condition_damage = enemy_conditions * 2;
			damage_this_turn = check_damage(damage_roll, player_defense, player_condition_damage);
 			
			enemy_current_health = reduce_health(enemy_current_health, enemy_condition_damage);
			player_current_health = reduce_health(player_current_health, damage_this_turn);
			(enemy_current_health <= 0) ? player_wins = true : player_wins = false;
			(player_current_health <= 0) ? enemy_wins = true : enemy_wins = false;

			if (attack_succeeds)
			{
				std::cout << "\n\n-  " << enemy_name << " hit " << player_name << " for " << (damage_this_turn - player_condition_damage) << " damage. ";
			}
			else
			{
				std::cout << "\n-  " << enemy_name << " missed " << player_name << ", dealing no damage. ";
			}

			std::cin.get();
			if (enemy_conditions)
			{
				std::cout << "   " << enemy_name << " took " << enemy_condition_damage << " damage from status effects. ";
				std::cin.get();
			}
			if (player_conditions)
			{
				std::cout << "   " << player_name << " took " << player_condition_damage << " damage from status effects. ";
				std::cin.get();
			}
			if (player_wins && enemy_wins)
			{
				std::cout << "\n-  In a twist of fate, you have slain one another! The quest ends with you. ";
				combat_continues = false;
			}
			else
			{
				if (player_wins)
				{
					std::cout << "\n-  " << player_name << " has slain " << enemy_name << "! ";
					combat_continues = false;
				}
				if (enemy_wins)
				{
					std::cout << "\n-  " << player_name << " has been slain by " << enemy_name << "! ";
					combat_continues = false;
				}
			}

			is_player_turn = true;
		}
	}

	std::cout << "\n\n";
}

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