/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:06:15 by tkurukul          #+#    #+#             */
/*   Updated: 2025/07/14 20:17:29 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int get_tile_color(char tile)
{
	int green_shade;

	if (tile == '1') // Walls
	{
		green_shade = 100 + rand() % 156; // from 100 to 255
		return (green_shade << 20);
	}
	else if (tile == '0')
		return (0x000000);
	else if (tile == 'D')
		return (0x0000FF);
	else if (tile == ' ')
		return (0x000000);
	else if (tile == 'G')
		return (0x808080);
	return (0x121212);
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

	set_zero_mini(game->minimap);
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

	set_zero_mini(game->minimap);
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
