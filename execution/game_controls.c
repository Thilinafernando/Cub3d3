/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:19:27 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/28 20:08:59 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
	if (game->info->map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->info->map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
}

static void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
	if (game->info->map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->info->map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
}

static void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED)
		- game->player.dir_y * sin(-ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(-ROT_SPEED)
		+ game->player.dir_y * cos(-ROT_SPEED);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED)
		- game->player.plane_y * sin(-ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(-ROT_SPEED)
		+ game->player.plane_y * cos(-ROT_SPEED);
}

static void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(ROT_SPEED)
		- game->player.dir_y * sin(ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(ROT_SPEED)
		+ game->player.dir_y * cos(ROT_SPEED);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(ROT_SPEED)
		- game->player.plane_y * sin(ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(ROT_SPEED)
		+ game->player.plane_y * cos(ROT_SPEED);
}

void	move_player(t_game *game)
{
	if (game->keys[119] || game->keys[87])
		move_forward(game);
	if (game->keys[115] || game->keys[83])
		move_backward(game);
	if (game->keys[97] || game->keys[65])
		move_left(game);
	if (game->keys[100] || game->keys[68])
		move_right(game);
	if (game->left_arrow)
		rotate_left(game);
	if (game->right_arrow)
		rotate_right(game);
}
