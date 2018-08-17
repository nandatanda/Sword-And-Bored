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
	int player_conditions = 0;
	int player_evasion = 0;
	int player_attack = 0;
	int player_current_health = 0;
	int player_defense = 0;
	int player_power = 0;
	int player_maximum_health = 0;
	int player_condition_damage = 0;
	int enemy_level = 0;
	int enemy_conditions = 0;
	int enemy_evasion = 0;
	int enemy_current_health = 0;
	int enemy_attack = 0;
	int enemy_defense = 0;
	int enemy_power = 0;
	int enemy_maximum_health = 0;
	int enemy_condition_damage = 0;
	int damage_this_turn = 0;
	int physical_damage = 0;
	int damage_roll = 0;
	int story_chapter = 0;
	int story_stage = 0;
	int story_scene = 0;
	int crit_counter = 0;
	int player_counter = 0;
	std::string player_name;
	std::string enemy_name;
	std::string enemy_profession;
	std::string player_profession;
	std::string player_move_selection;
	std::string enemy_move_selection = "none";
	std::string player_parameter = "none";
	std::string enemy_parameter;
	bool attack_succeeds = true;
	bool is_player_turn = true;
	bool player_wins = false;
	bool enemy_wins = false;
	bool combat_continues = true;
	bool story_continues = true;
	bool game_clear = false;

	srand((unsigned int)time(NULL));

	player_name = get_player_name();
	make_space(2);
	player_profession = get_player_profession();
	make_space(5);

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
		story_scene++;

		enemy_name = "Goblin Recruit";
		enemy_profession = "goblin";

		player_level = 20;
		player_evasion = get_evasion(player_profession, player_level);
		player_attack = get_attack(player_profession, player_level);
		player_maximum_health = get_maximum_health(player_profession, player_level);
		player_defense = get_defense(player_profession, player_level);
		player_power = get_power(player_profession, player_level);
		player_current_health = player_maximum_health;

		enemy_level = 40;
		enemy_evasion = get_evasion(enemy_profession, enemy_level);
		enemy_attack = get_attack(enemy_profession, enemy_level);
		enemy_maximum_health = get_maximum_health(enemy_profession, enemy_level);
		enemy_defense = get_defense(enemy_profession, enemy_level);
		enemy_power = get_power(enemy_profession, enemy_level);
		enemy_current_health = enemy_maximum_health;

		combat_continues = true;
		player_parameter = "none";
		player_counter = 0;
		player_conditions = 0;
		enemy_conditions = 0;
		crit_counter = 0;

		is_player_turn = flip_coin();

		make_space(4);

		while (combat_continues)
		{
			if (is_player_turn)
			{
				make_space(1);
				read_info_bar(player_name, player_level, player_current_health, player_conditions);
				make_space(1);
				read_info_bar(enemy_name, enemy_level, enemy_current_health, enemy_conditions);
				getchar();

				if (player_parameter == "none")
				{
					player_counter = 0;
				}

				make_space(5);
				player_move_selection = get_move_selection(player_name, player_profession, player_parameter);
				player_parameter = get_parameter(player_move_selection, player_parameter);

				player_counter = refresh_player_counter(player_parameter, player_counter);
				crit_counter = refresh_crit_counter(player_move_selection, player_parameter, crit_counter, player_counter);

				std::cout << "\nDIAG  ::  variable player_parameter is equal to '" << player_parameter << "'.\n";
				std::cout << "DIAG  ::  variable player_counter is equal to " << player_counter << ".\n";
				std::cout << "DIAG  ::  variable crit_counter is equal to " << crit_counter << ".\n";
				std::cout << "DIAG  ::  variable enemy_attack is equal to " << enemy_attack << ".";

				attack_succeeds = check_hit(player_attack, enemy_evasion, player_parameter, enemy_parameter);
				damage_roll = get_damage_roll(attack_succeeds, player_power, player_move_selection, crit_counter);
	
				enemy_conditions = check_apply_conditions(player_move_selection, attack_succeeds, enemy_conditions);
				enemy_attack = check_apply_blindness(player_move_selection, attack_succeeds, enemy_attack);

				player_condition_damage = player_conditions;
				enemy_condition_damage = enemy_conditions;

				damage_this_turn = check_damage(damage_roll, enemy_defense, enemy_condition_damage);
				physical_damage = damage_this_turn - enemy_condition_damage;

				player_current_health = reduce_health(player_current_health, player_condition_damage);
				enemy_current_health = reduce_health(enemy_current_health, damage_this_turn);
				player_wins = check_win(enemy_current_health);
				enemy_wins = check_win(player_current_health);
				
				make_space(2);
				read_combat_move(player_name, player_move_selection);
				getchar();

				make_space(1);

				if (attack_succeeds)
				{
					read_player_attack_success(player_name, enemy_name, player_move_selection, physical_damage);
				}
				else
				{
					read_player_attack_failure(player_name, enemy_name, player_move_selection);
				}

				getchar();

				if (player_conditions)
				{
					read_combat_conditions(player_name, player_condition_damage);
					getchar();
				}
				if (enemy_conditions)
				{
					read_combat_conditions(enemy_name, enemy_condition_damage);
					getchar();
				}
				if (player_wins && enemy_wins)
				{
					make_space(1);
					read_combat_draw(player_name, enemy_name);
					combat_continues = false;
					story_continues = false;
				}
				else
				{
					if (player_wins)
					{
						read_combat_win(player_name, enemy_name);
						combat_continues = false;
						getchar();
					}
					if (enemy_wins)
					{
						read_combat_loss(player_name, enemy_name);
						combat_continues = false;
						story_continues = false;
						getchar();
					}
				}

				is_player_turn = false;
			}

			else if (!is_player_turn)
			{
				make_space(1);
				read_info_bar(player_name, player_level, player_current_health, player_conditions);
				make_space(1);
				read_info_bar(enemy_name, enemy_level, enemy_current_health, enemy_conditions);
				getchar();

				make_space(5);
				std::cout << "-  [" << enemy_name << "]";
				getchar();

				attack_succeeds = check_hit(enemy_attack, player_evasion, enemy_parameter, player_parameter);
				damage_roll = get_damage_roll(attack_succeeds, enemy_power, player_move_selection, crit_counter);
				
				player_condition_damage = player_conditions;
				enemy_condition_damage = enemy_conditions;

				damage_this_turn = check_damage(damage_roll, player_defense, player_condition_damage);
				physical_damage = damage_this_turn - enemy_condition_damage;

				player_current_health = reduce_health(player_current_health, damage_this_turn);
				enemy_current_health = reduce_health(enemy_current_health, enemy_condition_damage);
				player_wins = check_win(enemy_current_health);
				enemy_wins = check_win(player_current_health);

				if (attack_succeeds)
				{
					make_space(1);
					read_enemy_attack_success(player_name, enemy_name, enemy_move_selection, physical_damage);
				}
				else
				{
					make_space(1);
					read_enemy_attack_failure(player_name, enemy_name, enemy_move_selection);
				}

				getchar();
				
				if (enemy_conditions)
				{
					read_combat_conditions(enemy_name, enemy_condition_damage);
					getchar();
				}
				if (player_conditions)
				{
					read_combat_conditions(player_name, player_condition_damage);
					getchar();
				}
				if (player_wins && enemy_wins)
				{
					make_space(1);
					read_combat_draw(player_name, enemy_name);
					combat_continues = false;
					story_continues = false;
				}
				else
				{
					if (player_wins)
					{
						read_combat_win(player_name, enemy_name);
						combat_continues = false;
						getchar();
					}
					if (enemy_wins)
					{
						read_combat_loss(player_name, enemy_name);
						combat_continues = false;
						story_continues = false;
						getchar();
					}
				}

				is_player_turn = true;
			}
		}

		make_space(5);
		(story_continues)
			? read_story_scene(story_chapter, story_stage, story_scene)
			: read_game_over(player_name, enemy_profession);
		story_scene++;
		make_space(5);
	}
}
