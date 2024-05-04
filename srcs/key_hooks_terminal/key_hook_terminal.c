/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_terminal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 02:10:15 by alberrod          #+#    #+#             */
/*   Updated: 2024/05/04 02:14:11 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsecube.h"

// TODO: CHECK IF MAINTAIN IT OR NOT / INTEGRATE IT WITH THE MAIN GAME
int	key_hook_terminal(int keycode, t_cube_data *cube_data)
{
	t_player_position *player_position = cube_data->player_position;
	int max_y;
	int max_x;
	char *keycode_str[14];

	if (keycode != LEFT && keycode != RIGHT && keycode != UP && keycode != DOWN)
		return (0);
	max_y = cube_data->max_y;
	max_x = ft_strlen(cube_data->map[player_position->y]);	
	if (keycode == LEFT)
	{
		if (player_position->x == 0 || cube_data->map[player_position->y][player_position->x - 1] == '1')
			return (0);
		move_left(player_position);
	}
	if (keycode == RIGHT)
	{
		if (player_position->x >= max_x - 1 || cube_data->map[player_position->y][player_position->x + 1] == '1')
			return (0);
		move_right(player_position);
	}
	if (keycode == UP)
	{
		if (player_position->y == 0 || cube_data->map[player_position->y - 1][player_position->x] == '1')
			return (0);
		move_up(player_position);
	}
	if (keycode == DOWN)
	{
		if (player_position->y >= max_y - 1 || cube_data->map[player_position->y + 1][player_position->x] == '1')
			return (0);
		move_down(player_position);
	}

	ft_memset(keycode_str, 0, 14);
	keycode_str[0] = "LEFT";
	keycode_str[2] = "RIGHT";
	keycode_str[13] = "UP";
	keycode_str[1] = "DOWN";
	
	print_game_terminal(cube_data);
	printf("Movement: %s\n", keycode_str[keycode]);
	printf("Player position: %d, %d\n", player_position->x, player_position->y);
	printf("\n");
	print_map(cube_data);
	return (0);
}