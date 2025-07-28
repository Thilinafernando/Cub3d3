/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 20:45:19 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/28 19:13:29 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	move_left_b(t_game *game)
{
	double	new_x;
	double	new_y;
	double	strafe_x ;
	double	strafe_y;

	strafe_x = game->player.dir_y;
	strafe_y = -game->player.dir_x;
	new_x = game->player.x + strafe_x * MOVE_SPEED;
	new_y = game->player.y + strafe_y * MOVE_SPEED;
	if (game->info->map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->info->map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
}

void	move_right_b(t_game *game)
{
	double	new_x;
	double	new_y;
	double	strafe_x;
	double	strafe_y;

	strafe_x = -game->player.dir_y;
	strafe_y = game->player.dir_x;
	new_x = game->player.x + strafe_x * MOVE_SPEED;
	new_y = game->player.y + strafe_y * MOVE_SPEED;
	if ((int)new_y >= 0 && (int)new_y < game->info->count
		&& (int)game->player.x >= 0
		&& (int)game->player.x < (int)ft_strlen(game->info->map[(int)new_y])
		&& !is_wall_or_closed_door(game, game->player.x, new_y))
		game->player.y = new_y;
	if ((int)game->player.y >= 0 && (int)game->player.y < game->info->count
		&& (int)new_x >= 0
		&& (int)new_x < (int)ft_strlen(game->info->map[(int)game->player.y])
		&& !is_wall_or_closed_door(game, new_x, game->player.y))
		game->player.x = new_x;
}
