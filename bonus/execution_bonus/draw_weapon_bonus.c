/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:41:28 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/13 20:40:14 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static t_texture	*get_weapon_texture(t_game *game)
{
	t_texture	*weapon;
	int			frame;

	if (game->is_shooting)
	{
		frame = (game->shoot_timer / 5) % 2;
		weapon = &game->weapon_fire_textures[frame];
		game->shoot_timer--;
		if (game->shoot_timer <= 0)
		{
			game->is_shooting = 0;
			game->shoot_timer = 0;
		}
	}
	else
	{
		weapon = &game->weapon_texture;
	}
	return (weapon);
}

static void	draw_weapon_pixels(t_game *game, t_texture *weapon,
						int x_start, int y_start)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < weapon->height)
	{
		x = 0;
		while (x < weapon->width)
		{
			color = get_texture_color(weapon, x, y);
			if (color != 0x000000)
				my_mlx_pixel_put(game, x_start + x, y_start + y, color);
			x++;
		}
		y++;
	}
}

void	draw_weapon(t_game *game)
{
	t_texture	*weapon;
	int			x_start;
	int			y_start;

	weapon = get_weapon_texture(game);
	x_start = (WINDOW_WIDTH - weapon->width) / 2;
	y_start = WINDOW_HEIGHT - weapon->height;
	draw_weapon_pixels(game, weapon, x_start, y_start);
}
