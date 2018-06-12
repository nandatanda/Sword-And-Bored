#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <limits>
#include <fstream>

int roll_die(int);
bool check_p1hit(int, int);
bool check_p2hit(int, int);
bool check_win(int, int);
int check_damage(int, int, int);
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
	int player_conditions = 1; //set at one for testing condi system
	int player_evasion = 0;
	int player_attack = 0;
	int player_current_health = 0;
	int player_defense = 0;
	int player_strength = 0;
	int player_maximum_health = 0;
	int enemy_level = 0;
	int enemy_condition = 0;
	int enemy_evasion = 0;
	int enemy_current_health = 0;
	int enemy_attack = 0;
	int enemy_defense = 0;
	int enemy_strength = 0;
	int enemy_maximum_health = 0;
	int damage_this_turn = 0;
	std::string player_name;
	std::string enemy_profession;
	std::string player_profession;
	std::string divider = "\n\n\n\n\n";
	bool attack_succeeds = true;
	bool is_player_turn = true;
	bool combat_continues = true;
	bool player_wins;
	bool enemy_wins;

	srand((unsigned int)time(NULL));

	std::cout << "-  What is your name, brave adventurer?\n\n>  ";
	std::cin >> player_name;
	std::cout << divider;
	std::cout << "-  Which profession strikes your fancy?\n\n1) Warrior\n\n2) Rogue\n\n3) Mage\n\n>  ";
	player_profession = get_profession();
	std::cout << "\n\n\n\n\n" << "-- PROTECC & ATTACC! : A TALE OF TWO LULZ -- ";
	std::cin.get();
	std::cin.ignore();
		
	//game begins
	read_story_block(1, 3);
	read_story_block(4, 4);
	read_story_block(5, 5);
	std::cout << divider;

	//scale the player level
	player_level = 15;
	player_evasion = get_evasion(player_profession, player_level);
	player_attack = get_attack(player_profession, player_level);
	player_maximum_health = get_maximum_health(player_profession, player_level);
	player_defense = get_defense(player_profession, player_level);
	player_strength = get_strength(player_profession, player_level);
	player_current_health = player_maximum_health;

	//enemy scaling will go here
	enemy_profession = "goblin";
	enemy_maximum_health = 10;
	enemy_defense = 5;
	enemy_strength = 30;
	enemy_evasion = 10;
	enemy_attack = 5;
	enemy_current_health = enemy_maximum_health;

	std::cout << "- " << enemy_profession << "   \t\t|\tHealth: " << enemy_current_health << "\tStatus: " << enemy_condition;
	std::cout << "\n\n  " << player_name << "   \t\t|\tHealth: " << player_current_health << "\tStatus: " << player_conditions << " ";
	std::cin.get();

	while (combat_continues)
	{
		if (is_player_turn)
		{
			attack_succeeds = check_p1hit(player_attack, enemy_evasion);
			if (attack_succeeds)
			{
				int damage_roll = (roll_die(20) + player_strength);
				damage_this_turn = check_damage(damage_roll, enemy_defense, enemy_condition);
				std::cout << "\n- You hit " << enemy_profession << " for " << damage_this_turn << " damage.";
			}
			else
			{
				std::cout << "\n- You missed " << enemy_profession << ", dealing no damage.";
			}
			std::cin.get();
			player_wins = check_win(enemy_current_health, damage_this_turn);
			if (player_wins)
			{
				std::cout << "\n- You have slain " << enemy_profession << "! ";
			}
			else if (player_conditions > 0)
			{
				//evaluate condi on player one
				damage_this_turn = player_conditions * 2;
				std::cout << "\n- You take " << damage_this_turn << " damage from status effects.";
			}

			is_player_turn = false;
		}
		else
		{
			attack_succeeds = check_p2hit(enemy_attack, player_evasion);
			if (attack_succeeds)
			{
				int damage_roll = (roll_die(20) + enemy_strength);
				damage_this_turn = check_damage(damage_roll, player_defense, player_conditions);
				std::cout << "\n-  " << enemy_profession << " hit you for " << damage_this_turn << " damage. ";
			}
			else
			{
				std::cout << "\n-  " << enemy_profession << ", missed, dealing no damage.";
			}
			std::cin.get();
			enemy_wins = check_win(player_current_health, damage_this_turn);
			if (enemy_wins)
			{
				std::cout << "\n- You have been slain by " << enemy_profession << "! ";
			}
			else if (player_conditions > 0)
			{
				//evaluate condi on player one
				damage_this_turn = player_conditions * 2;
				std::cout << "\n- You take " << damage_this_turn << " damage from status effects.";
			}

			is_player_turn = true;
		}
		/*

		player two's turn

		*/
	}
	std::cout << "\n\n";

}










int roll_die(int die_sides)
{
	int die_result = rand() % die_sides + 1;
	return die_result;
}
bool check_p1hit(int player_attack, int enemy_evasion)
{
	bool hit_result;
	int attack_roll = (roll_die(20) + player_attack);
	(attack_roll > enemy_evasion) ? hit_result = true : hit_result = false;
	return hit_result;
}
bool check_p2hit(int enemy_attack, int player_evasion)
{
	bool hit_result;
	int attack_roll = (roll_die(20) + enemy_attack);
	(attack_roll > player_evasion) ? hit_result = true : hit_result = false;
	return hit_result;
}
bool check_win(int health, int damage)
{
	bool win_now;
	int health_result = health - damage;
	(health_result <= 0) ? win_now = true : win_now = false;
	return win_now;
}
int check_damage(int damage, int defense, int condi)
{
	int condi_damage = condi * 2;
	int damage_result = (damage / defense) + condi_damage;
	return damage_result;
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
		evasion_result = 10 + (3 * level);
	}
	else if (profession == "goblin")
	{
		evasion_result = 10 + (1 * level);
	}
	return evasion_result;
}
int get_attack(std::string profession, int level)
{
	int attack_result = 0;
	if (profession == "warrior")
	{
		attack_result = 10 + (1 * level);
	}
	else if (profession == "mage")
	{
		attack_result = 10 + (2 * level);
	}
	else if (profession == "rogue")
	{
		attack_result = 10 + (3 * level);
	}
	else if (profession == "goblin")
	{
		attack_result = 10 + (1 * level);
	}
	return attack_result;
}
int get_maximum_health(std::string profession, int level)
{
	int get_maximum_health = 0;
	if (profession == "warrior")
	{
		get_maximum_health = 10 + (9 * level);
	}
	else if (profession == "mage")
	{
		get_maximum_health = 10 + (5 * level);
	}
	else if (profession == "rogue")
	{
		get_maximum_health = 10 + (7 * level);
	}
	else if (profession == "goblin")
	{
		get_maximum_health = 10 + (5 * level);
	}
	return get_maximum_health;
}
int get_defense(std::string profession, int level)
{
	int get_player_defense = 0;
	if (profession == "warrior")
	{
		get_player_defense = 10 + (3 * level);
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
		get_player_defense = 10 + (1 * level);
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
		get_strength = 10 + (3 * level);
	}
	else if (profession == "rogue")
	{
		get_strength = 10 + (1 * level);
	}
	else if (profession == "goblin")
	{
		get_strength = 10 + (1 * level);
	}
	return get_strength;
}