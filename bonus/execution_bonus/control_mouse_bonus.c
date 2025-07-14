/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_mouse_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 23:13:24 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/13 22:03:36 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	init_mouse_position(t_game *game, int x, int y)
{
	if (game->prev_mouse_x == -1)
	{
		game->prev_mouse_x = x;
		game->mouse_x = x;
		game->mouse_y = y;
		return (1);
	}
	return (0);
}

static double	calculate_rotation_angle(int dx)
{
	double	mouse_sensitivity;
	double	rotation_angle;

	mouse_sensitivity = 0.003;
	rotation_angle = dx * mouse_sensitivity;
	if (rotation_angle > 0.1)
		rotation_angle = 0.1;
	if (rotation_angle < -0.1)
		rotation_angle = -0.1;
	return (rotation_angle);
}

static void	apply_rotation(t_game *game, double rotation_angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(rotation_angle)
		- game->player.dir_y * sin(rotation_angle);
	game->player.dir_y = old_dir_x * sin(rotation_angle)
		+ game->player.dir_y * cos(rotation_angle);
	game->player.plane_x = game->player.plane_x * cos(rotation_angle)
		- game->player.plane_y * sin(rotation_angle);
	game->player.plane_y = old_plane_x * sin(rotation_angle)
		+ game->player.plane_y * cos(rotation_angle);
}

int	mouse_move(int x, int y, t_game *game)
{
	int		dx;
	double	rotation_angle;

	(void)y;
	if (init_mouse_position(game, x, y))
		return (0);
	dx = x - game->prev_mouse_x;
	if (ft_abs(dx) < 2)
		return (0);
	rotation_angle = calculate_rotation_angle(dx);
	apply_rotation(game, rotation_angle);
	game->prev_mouse_x = x;
	game->mouse_x = x;
	game->mouse_y = y;
	return (0);
}
