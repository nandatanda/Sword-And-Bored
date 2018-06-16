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
	int player_power = 0;
	int player_maximum_health = 0;
	int player_condition_damage = 0;
	int enemy_level = 0;
	int enemy_conditions = 1;
	int enemy_evasion = 0;
	int enemy_current_health = 0;
	int enemy_attack = 0;
	int enemy_defense = 0;
	int enemy_power = 0;
	int enemy_maximum_health = 0;
	int enemy_condition_damage = 0;
	int damage_this_turn = 0;
	int damage_roll = 0;
	int story_chapter = 0;
	int story_stage = 0;
	int story_scene = 0;
	std::string player_name;
	std::string enemy_name;
	std::string enemy_profession;
	std::string player_profession;
	bool attack_succeeds = true;
	bool is_player_turn = true;
	bool player_wins = false;
	bool enemy_wins = false;
	bool combat_continues = true;
	bool story_continues = true;
	bool game_clear = false;

	srand((unsigned int)time(NULL));

	player_name = get_player_name();
	player_profession = get_player_profession();
	make_space(3);

	story_chapter = 1;
	story_stage = 1;
	story_scene = 1;

	while (story_continues)
	{
		if (story_scene > 2)
		{
			story_scene = 1;
			story_stage++;
		}
		if (story_stage > 10)
		{
			story_stage = 1;
			story_chapter++;
		}

		read_story_scene(story_chapter, story_stage, story_scene);
		make_space(3);
		story_scene++;

		enemy_name = "Goblin Recruit";
		enemy_profession = "goblin";

		player_level = 30;
		player_evasion = get_evasion(player_profession, player_level);
		player_attack = get_attack(player_profession, player_level);
		player_maximum_health = get_maximum_health(player_profession, player_level);
		player_defense = get_defense(player_profession, player_level);
		player_power = get_power(player_profession, player_level);
		player_current_health = player_maximum_health;

		enemy_level = 30;
		enemy_evasion = get_evasion(enemy_profession, enemy_level);
		enemy_attack = get_attack(enemy_profession, enemy_level);
		enemy_maximum_health = get_maximum_health(enemy_profession, enemy_level);
		enemy_defense = get_defense(enemy_profession, enemy_level);
		enemy_power = get_power(enemy_profession, enemy_level);
		enemy_current_health = enemy_maximum_health;

		combat_continues = true;
		is_player_turn = flip_coin();

		while (combat_continues)
		{
			if (is_player_turn)
			{
				std::cout << "\n-  [" << enemy_name << " | " << enemy_level << "]\n\t\t\t\t" << enemy_current_health << "  |  " << enemy_conditions;
				std::cout << "\n\n   [" << player_name << " | " << player_level << "]\n\t\t\t\t" << player_current_health << "  |  " << player_conditions << " ";
				//player attack selection will go here
				attack_succeeds = check_hit(player_attack, enemy_evasion);
				damage_roll = get_damage_roll(attack_succeeds, player_power);
				(attack_succeeds) ? damage_roll = 5 * (roll_die(100) + player_power) : damage_roll = 0;
				player_condition_damage = player_conditions * 2;
				enemy_condition_damage = enemy_conditions * 2;
				damage_this_turn = check_damage(damage_roll, enemy_defense, enemy_condition_damage);

				player_current_health = reduce_health(player_current_health, player_condition_damage);
				enemy_current_health = reduce_health(enemy_current_health, damage_this_turn);
				player_wins = check_win(enemy_current_health);
				enemy_wins = check_win(player_current_health);

				getchar();

				if (attack_succeeds)
				{
					std::cout << "\n\n-  " << player_name << " hit " << enemy_name << " for " << (damage_this_turn - enemy_condition_damage) << " damage. ";
				}
				else
				{
					std::cout << "\n-  " << player_name << " missed " << enemy_name << ", dealing no damage. ";
				}

				getchar();
				if (player_conditions)
				{
					std::cout << "   " << player_name << " took " << player_condition_damage << " damage from status effects. ";
					getchar();
				}
				if (enemy_conditions)
				{
					std::cout << "   " << enemy_name << " took " << enemy_condition_damage << " damage from status effects. ";
					getchar();
				}
				if (player_wins && enemy_wins)
				{
					std::cout << "\n-  In a twist of fate, " << player_name << " and " << enemy_name << " have slain one another! With this, the quest is no more. ";
					combat_continues = false;
					story_continues = false;
				}
				else
				{
					if (player_wins)
					{
						std::cout << "\n-  " << player_name << " has slain " << enemy_name << "! ";
						getchar();
						combat_continues = false;
					}
					if (enemy_wins)
					{
						std::cout << "\n- " << player_name << " has been slain by " << enemy_name << "! ";
						getchar();
						combat_continues = false;
						story_continues = false;
					}
				}

				is_player_turn = false;

			}
			else
			{
				std::cout << "\n\n-  [" << enemy_name << " | " << enemy_level << "]\n\t\t\t\t" << enemy_current_health << "  |  " << enemy_conditions;
				std::cout << "\n\n   [" << player_name << " | " << player_level << "]\n\t\t\t\t" << player_current_health << "  |  " << player_conditions << " \n";
				getchar();
				//enemy attack selection will go here
				attack_succeeds = check_hit(enemy_attack, player_evasion);
				damage_roll = get_damage_roll(attack_succeeds, enemy_power);
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

				getchar();
				if (enemy_conditions)
				{
					std::cout << "   " << enemy_name << " took " << enemy_condition_damage << " damage from status effects. ";
					getchar();
				}
				if (player_conditions)
				{
					std::cout << "   " << player_name << " took " << player_condition_damage << " damage from status effects. ";
					getchar();
				}
				if (player_wins && enemy_wins)
				{
					std::cout << "\n-  In a twist of fate, " << player_name << " and " << enemy_name << " have slain one another! With this, the quest is no more. ";
					getchar();
					combat_continues = false;
					story_continues = false;
				}
				else
				{
					if (player_wins)
					{
						std::cout << "\n-  " << player_name << " has slain " << enemy_name << "! ";
						getchar();
						combat_continues = false;
					}
					if (enemy_wins)
					{
						std::cout << "\n-  " << player_name << " has been slain by " << enemy_name << "! ";
						getchar();
						combat_continues = false;
						story_continues = false;
					}
				}

				is_player_turn = true;
			}
		}

		read_story_scene(story_chapter, story_stage, story_scene);
		story_scene++;
	}
}
