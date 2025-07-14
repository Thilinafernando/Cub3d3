/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 23:28:51 by tkurukul          #+#    #+#             */
/*   Updated: 2025/07/14 20:06:23 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	put_tile_block(t_game *game, int map_x, int map_y,
				int color)
{
	int	dx;
	int	dy;
	int	screen_x;
	int	screen_y;

	dy = 0;
	while (dy < game->minimap->h)
	{
		dx = 0;
		while (dx < (game->minimap->w))
		{
			screen_x = map_x * game->minimap->w + dx;
			screen_y = map_y * game->minimap->h + dy;
			if (screen_x < WINDOW_WIDTH && screen_y < WINDOW_HEIGHT / 2)
				my_mlx_pixel_put(game, screen_x, screen_y, color);
			dx++;
		}
		dy++;
	}
}

void	draw_halfscreen_map(t_game *game)
{
	int		map_x;
	int		map_y;
	char	tile;
	int		color;

	game->minimap->w = WINDOW_WIDTH / ft_strlen(game->info->map[0]);
	game->minimap->h = (WINDOW_HEIGHT / 2) / game->info->count;
	map_y = 0;
	while (map_y < game->info->count)
	{
		map_x = 0;
		while (game->info->map[map_y][map_x])
		{
			tile = game->info->map[map_y][map_x];
			color = get_tile_color(tile);
			put_tile_block(game, map_x, map_y, color);
			map_x++;
		}
		map_y++;
	}
}

void	draw_player_on_half_map(t_game *game)
{
	int		tile_w;
	int		tile_h;
	int		radius;

	set_zero_mini(game->minimap);
	radius = 3;
	tile_w = WINDOW_WIDTH / ft_strlen(game->info->map[0]);
	tile_h = (WINDOW_HEIGHT / 2) / game->info->count;
	game->minimap->px = game->player.x * tile_w;
	game->minimap->py = game->player.y * tile_h;
	game->minimap->dy = -radius;
	while (game->minimap->dy <= radius)
	{
		game->minimap->dx = -radius;
		while (game->minimap->dx <= radius)
		{
			if (game->minimap->dx * game->minimap->dx + game->minimap->dy
				* game->minimap->dy <= radius * radius)
				my_mlx_pixel_put(game, game->minimap->px + game->minimap->dx,
					game->minimap->py + game->minimap->dy, 0x00FF00);
			game->minimap->dx++;
		}
		game->minimap->dy++;
	}
	set_zero_mini(game->minimap);
}

void draw_minimap(t_game *game)
{
	if (game->minimap->full)
	{
		draw_halfscreen_map(game);
		draw_player_on_half_map(game);
	}
	else
	{
		set_zero_mini(game->minimap);
		draw_minimap_background_circle(game);
		draw_moving_minimap_tiles(game);
		draw_accurate_player_dot(game);
	}
}
