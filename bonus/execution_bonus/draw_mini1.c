/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:05:18 by tkurukul          #+#    #+#             */
/*   Updated: 2025/07/25 17:30:23 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_zero_mini(t_minimap *minimap)
{
	if (!minimap)
		return ;
	minimap->dx = 0;
	minimap->dy = 0;
	minimap->px = 0;
	minimap->py = 0;
	minimap->perp_x = 0;
	minimap->perp_y = 0;
	minimap->point_x = 0;
	minimap->point_y = 0;
}

void	draw_player_body(t_game *game, int px, int py)
{
	int	i;
	int	j;

	set_zero_mini(game->minimap);
	i = -3;
	while (++i <= 2)
	{
		j = -3;
		while (++j <= 2)
		{
			if (((i * i) + (j * j)) <= 4)
			{
				game->minimap->dx = px + i - MINIMAP_RADIUS_PIXELS;
				game->minimap->dy = py + j - MINIMAP_RADIUS_PIXELS;
				if (game->minimap->dx * game->minimap->dx + game->minimap->dy
					* game->minimap->dy <= MINIMAP_RADIUS_PIXELS
					* MINIMAP_RADIUS_PIXELS)
					my_mlx_pixel_put(game, MINIMAP_OFFSET_X + px + i,
						MINIMAP_OFFSET_Y + py + j, 0x00FF00);
			}
		}
	}
	set_zero_mini(game->minimap);
}

void	process_draw_arrow(t_game *game, int px, int py, int dist)
{
	int	width;
	int	w;

	game->minimap->point_x = px + (int)(game->player.dir_x * dist);
	game->minimap->point_y = py + (int)(game->player.dir_y * dist);
	width = (5 - dist) / 2;
	w = -width - 2;
	while (++w <= width)
	{
		game->minimap->perp_x = game->minimap->point_x
			+ (int)(-game->player.dir_y * w);
		game->minimap->perp_y = game->minimap->point_y
			+ (int)(game->player.dir_x * w);
		game->minimap->dx = game->minimap->perp_x
			- MINIMAP_RADIUS_PIXELS;
		game->minimap->dy = game->minimap->perp_y
			- MINIMAP_RADIUS_PIXELS;
		if (game->minimap->dx * game->minimap->dx
			+ game->minimap->dy * game->minimap->dy
			<= MINIMAP_RADIUS_PIXELS * MINIMAP_RADIUS_PIXELS)
			my_mlx_pixel_put(game, MINIMAP_OFFSET_X
				+ game->minimap->perp_x, MINIMAP_OFFSET_Y
				+ game->minimap->perp_y, 0x00FF00);
	}
	set_zero_mini(game->minimap);
}

void	draw_player_arrow(t_game *game, int px, int py)
{
	int	dist;

	set_zero_mini(game->minimap);
	dist = 0;
	while (++dist <= 4)
		process_draw_arrow(game, px, py, dist);
	set_zero_mini(game->minimap);
}

void	draw_tile_if_in_circle(t_game *game, int tile_x, int tile_y, int color)
{
	int	center;
	int	i;
	int	j;

	set_zero_mini(game->minimap);
	center = MINIMAP_RADIUS_PIXELS;
	i = -1;
	while (++i < MINIMAP_SCALE)
	{
		j = -1;
		while (++j < MINIMAP_SCALE)
		{
			game->minimap->px = tile_x * MINIMAP_SCALE + i;
			game->minimap->py = tile_y * MINIMAP_SCALE + j;
			game->minimap->dx = game->minimap->px - center;
			game->minimap->dy = game->minimap->py - center;
			if (game->minimap->dx * game->minimap->dx + game->minimap->dy
				* game->minimap->dy <= center * center)
				my_mlx_pixel_put(game, MINIMAP_OFFSET_X + game->minimap->px,
					MINIMAP_OFFSET_Y + game->minimap->py, color);
		}
	}
	set_zero_mini(game->minimap);
}
