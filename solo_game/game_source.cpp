#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <limits>
#include <fstream>

#include "game_functions.h"

void main()
{
	int player_experience = 0;
	int player_level = 0;
	int player_conditions = 1;
	int player_evasion = 0;
	int player_attack = 0;
	int player_current_health = 0;
	int player_defense = 0;
	int player_strength = 0;
	int player_maximum_health = 0;
	int player_condition_damage = 0;
	int enemy_level = 0;
	int enemy_conditions = 1;
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
	enemy_level = 40;
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
			player_wins = check_win(enemy_current_health);
			enemy_wins = check_win(player_current_health);

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
				std::cout << "\n-  In a twist of fate, " << player_name << " and " << enemy_name << " have slain one another! With this, the quest is no more. ";
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
			player_wins = check_win(enemy_current_health);
			enemy_wins = check_win(player_current_health);

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
				std::cout << "\n-  In a twist of fate, " << player_name << " and " << enemy_name << " have slain one another! With this, the quest is no more. ";
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