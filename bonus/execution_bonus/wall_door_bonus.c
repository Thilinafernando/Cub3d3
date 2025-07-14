/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_door_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 23:30:06 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/13 20:38:28 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_wall_or_closed_door(t_game *game, double x, double y)
{
	int		map_x;
	int		map_y;
	char	tile;

	map_x = (int)x;
	map_y = (int)y;
	tile = game->info->map[map_y][map_x];
	if (tile == '1')
		return (1);
	if (tile == 'D' && !is_door_open(game, map_x, map_y))
		return (1);
	return (0);
}

void	try_open_close_door(t_game *game)
{
	int	check_x;
	int	check_y;

	check_x = (int)(game->player.x + game->player.dir_x);
	check_y = (int)(game->player.y + game->player.dir_y);
	if (check_y >= 0 && check_y < game->info->count
		&& check_x >= 0 && check_x < (int)ft_strlen(game->info->map[check_y]))
	{
		if (game->info->map[check_y][check_x] == 'D')
		{
			game->info->map[check_y][check_x] = '0';
		}
		else if (game->info->map[check_y][check_x] == '0')
		{
			game->info->map[check_y][check_x] = 'D';
		}
	}
}

void	try_toggle_door(t_game *game)
{
	int	target_x;
	int	target_y;
	int	i;

	target_x = (int)(game->player.x + game->player.dir_x);
	target_y = (int)(game->player.y + game->player.dir_y);
	if (game->info->map[target_y][target_x] != 'D')
		return ;
	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].x == target_x && game->doors[i].y == target_y)
		{
			game->doors[i].is_open = !game->doors[i].is_open;
			return ;
		}
		i++;
	}
	if (game->door_count < MAX_DOORS)
	{
		game->doors[game->door_count].x = target_x;
		game->doors[game->door_count].y = target_y;
		game->doors[game->door_count].is_open = 1;
		game->door_count++;
	}
}

int	is_door_open(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (game->doors[i].is_open);
		i++;
	}
	return (0);
}
