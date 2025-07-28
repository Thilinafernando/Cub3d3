/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:41:28 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/28 21:30:43 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	update_weapon_timers(t_game *game)
{
	if (game->is_using_hand)
	{
		game->hand_timer--;
		if (game->hand_timer <= 0)
		{
			game->is_using_hand = 0;
			game->hand_timer = 0;
		}
	}
	else if (game->is_shooting)
	{
		game->shoot_timer--;
		if (game->shoot_timer <= 0)
		{
			game->is_shooting = 0;
			game->shoot_timer = 0;
		}
	}
}

static t_texture	*get_current_texture(t_game *game)
{
	int	frame;

	update_weapon_timers(game);
	if (game->is_using_hand)
		return (&game->hand_texture);
	else if (game->is_shooting)
	{
		frame = (game->shoot_timer / 5) % 2;
		return (&game->weapon_fire_textures[frame]);
	}
	else
		return (&game->weapon_texture);
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
	t_texture	*texture;
	int			x_start;
	int			y_start;

	texture = get_current_texture(game);
	if (game->is_using_hand)
	{
		x_start = (WINDOW_WIDTH - texture->width) / 2;
		y_start = WINDOW_HEIGHT - texture->height;
	}
	else
	{
		x_start = WINDOW_WIDTH - texture->width - 30;
		y_start = WINDOW_HEIGHT - texture->height;
	}
	draw_weapon_pixels(game, texture, x_start, y_start);
}
