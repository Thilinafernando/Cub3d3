/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 23:28:51 by tkurukul          #+#    #+#             */
/*   Updated: 2025/07/13 23:55:58 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_zero_mini(t_minimap *minimap)
{
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
	int i;
	int	j;

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

int	get_tile_color(char tile)
{
	if (tile == '1')
		return (0x888888); // Wall
	else if (tile == '0')
		return (0xFFFFFF); // Floor
	else if (tile == 'D')
		return (0xFFA500); // Door_dash
	else if (tile == ' ')
		return (0x000000); // Spacess
	return (0x222222);     //UNKOWN
}

void	draw_moving_minimap_tiles(t_game *game)
{
	int	map_x;
	int	map_y;
	int	color;
	char	tile;

	game->px = (int)game->player.x;
	game->py = (int)game->player.y;
	map_y = (game->py - MINIMAP_RADIUS_TILES) - 1;
	while (++map_y <= (game->py + MINIMAP_RADIUS_TILES))
	{
		map_x = (game->px - MINIMAP_RADIUS_TILES) - 1;
		while (++map_x <= (game->px + MINIMAP_RADIUS_TILES))
		{
			if (map_y >= 0 && map_x >= 0 && map_y < game->info->count
				&& map_x < (int)ft_strlen(game->info->map[map_y]))
			{
				tile = game->info->map[map_y][map_x];
				color = get_tile_color(tile);
				draw_tile_if_in_circle(game, map_x - game->px
					+ MINIMAP_RADIUS_TILES, map_y - game->py
					+ MINIMAP_RADIUS_TILES, color);
			}
		}
	}
	set_zero_mini(game->minimap);
}

void	draw_accurate_player_dot(t_game *game)
{
	double	offset_x;
	double	offset_y;
	int		player_pixel_x;
	int		player_pixel_y;

	offset_x = game->player.x - (int)game->player.x;
	offset_y = game->player.y - (int)game->player.y;
	player_pixel_x = MINIMAP_RADIUS_TILES * MINIMAP_SCALE\
		+ (int)(offset_x * MINIMAP_SCALE);
	player_pixel_y = MINIMAP_RADIUS_TILES * MINIMAP_SCALE\
		+ (int)(offset_y * MINIMAP_SCALE);
	draw_player_body(game, player_pixel_x, player_pixel_y);
	draw_player_arrow(game, player_pixel_x, player_pixel_y);
	set_zero_mini(game->minimap);
}

void	draw_minimap_background_circle(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	while (++x < MINIMAP_DIAMETER)
	{
		y = -1;
		while (++y < MINIMAP_DIAMETER)
		{
			game->minimap->dx = x - MINIMAP_RADIUS_PIXELS;
			game->minimap->dy = y - MINIMAP_RADIUS_PIXELS;
			if (game->minimap->dx * game->minimap->dx + game->minimap->dy
				* game->minimap->dy <= MINIMAP_RADIUS_PIXELS
				* MINIMAP_RADIUS_PIXELS)
				my_mlx_pixel_put(game, MINIMAP_OFFSET_X + x,
					MINIMAP_OFFSET_Y + y, 0x000000);
		}
	}
	set_zero_mini(game->minimap);
}

void draw_minimap(t_game *game)
{
	draw_minimap_background_circle(game);
	draw_moving_minimap_tiles(game);
	draw_accurate_player_dot(game);
}
