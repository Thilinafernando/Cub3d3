/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_controls_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:19:27 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/28 20:12:14 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos_angle - game->player.dir_y
		* sin_angle;
	game->player.dir_y = old_dir_x * sin_angle + game->player.dir_y * cos_angle;
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos_angle
		- game->player.plane_y * sin_angle;
	game->player.plane_y = old_plane_x * sin_angle + game->player.plane_y
		* cos_angle;
}

void	toggle_minimap(t_game *game)
{
	static int	i = 1;

	i++;
	if (i % 2 == 0)
		game->minimap->full = 1;
	else
		game->minimap->full = 0;
}

static void	handle_movement_keys(t_game *game)
{
	static int	prev_m_state = 0;

	if (game->keys[119] || game->keys[87])
		move_forward_bonus(game);
	if (game->keys[115] || game->keys[83])
		move_backward_bonus(game);
	if (game->left_arrow)
		rotate_player(game, -ROT_SPEED);
	if (game->right_arrow)
		rotate_player(game, ROT_SPEED);
	if (game->keys[109] && !prev_m_state)
		toggle_minimap(game);
	prev_m_state = game->keys[109];
}

static void	handle_rotation_keys(t_game *game)
{
	if (game->keys[97] || game->keys[65])
		move_left_b(game);
	if (game->keys[100] || game->keys[68])
		move_right_b(game);
}

void	move_player(t_game *game)
{
	handle_movement_keys(game);
	handle_rotation_keys(game);
}
