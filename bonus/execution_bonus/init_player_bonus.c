/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:19:17 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/12 22:20:22 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	set_direction_north(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = -1;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0;
}

static void	set_direction_south(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = 1;
	game->player.plane_x = -0.66;
	game->player.plane_y = 0;
}

static void	set_direction_east(t_game *game)
{
	game->player.dir_x = 1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
}

static void	set_direction_west(t_game *game)
{
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = -0.66;
}

void	init_player(t_game *game)
{
	char	player_dir;

	player_dir = game->info->map[game->info->player_y][game->info->player_x];
	game->player.x = game->info->player_x + 0.5;
	game->player.y = game->info->player_y + 0.5;
	if (player_dir == 'N')
		set_direction_north(game);
	else if (player_dir == 'S')
		set_direction_south(game);
	else if (player_dir == 'E')
		set_direction_east(game);
	else if (player_dir == 'W')
		set_direction_west(game);
}
