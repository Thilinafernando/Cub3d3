/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_controls_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 23:59:00 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/13 00:05:06 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	move_forward_bonus(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
	if (!is_wall_or_closed_door(game, game->player.x, new_y))
		game->player.y = new_y;
	if (!is_wall_or_closed_door(game, new_x, game->player.y))
		game->player.x = new_x;
}

void	move_backward_bonus(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
	if (!is_wall_or_closed_door(game, game->player.x, new_y))
		game->player.y = new_y;
	if (!is_wall_or_closed_door(game, new_x, game->player.y))
		game->player.x = new_x;
}
