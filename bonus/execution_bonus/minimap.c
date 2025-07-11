/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:48:46 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/11 22:09:31 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	draw_tile_if_in_circle(t_game *game, int tile_x, int tile_y, int color)
{
	int	center = MINIMAP_RADIUS_PIXELS;

	// Draw the tile pixel by pixel, checking each pixel individually
	for (int i = 0; i < MINIMAP_SCALE; i++)
	{
		for (int j = 0; j < MINIMAP_SCALE; j++)
		{
			int px = tile_x * MINIMAP_SCALE + i;
			int py = tile_y * MINIMAP_SCALE + j;

			// Check if this pixel is within the circle
			int pixel_dx = px - center;
			int pixel_dy = py - center;
			if (pixel_dx * pixel_dx + pixel_dy * pixel_dy <= MINIMAP_RADIUS_PIXELS * MINIMAP_RADIUS_PIXELS)
			{
				my_mlx_pixel_put(game,
					MINIMAP_OFFSET_X + px,
					MINIMAP_OFFSET_Y + py,
					color);
			}
		}
	}
}

// Draw nearby map tiles relative to the player
static void	draw_moving_minimap_tiles(t_game *game)
{
	int	map_x;
	int	map_y;
	int	px = (int)game->player.x;
	int	py = (int)game->player.y;
	int	color;
	char	tile;

	map_y = py - MINIMAP_RADIUS_TILES;
	while (map_y <= py + MINIMAP_RADIUS_TILES)
	{
		map_x = px - MINIMAP_RADIUS_TILES;
		while (map_x <= px + MINIMAP_RADIUS_TILES)
		{
			if (map_y >= 0 && map_x >= 0
				&& map_y < game->info->count
				&& map_x < (int)ft_strlen(game->info->map[map_y]))
			{
				tile = game->info->map[map_y][map_x];
				if (tile == '1')
					color = 0x888888;
				else if (tile == '0')
					color = 0xFFFFFF;
				else if (tile == 'D')
					color = 0xFFA500;
				else
				{
					map_x++;
					continue;
				}
				draw_tile_if_in_circle(game,
					map_x - px + MINIMAP_RADIUS_TILES,
					map_y - py + MINIMAP_RADIUS_TILES,
					color);
			}
			map_x++;
		}
		map_y++;
	}
}

// Draw the player as a directional arrow/teardrop shape
static void	draw_accurate_player_dot(t_game *game)
{
	int	i;
	int	j;

	// Calculate the exact position of the player within the minimap
	// The center tile is at MINIMAP_RADIUS_TILES in the minimap grid
	double offset_x = game->player.x - (int)game->player.x; // fractional part (0.0 to 1.0)
	double offset_y = game->player.y - (int)game->player.y; // fractional part (0.0 to 1.0)

	// Calculate player position in minimap pixels
	// Center tile starts at MINIMAP_RADIUS_TILES * MINIMAP_SCALE
	int player_pixel_x = MINIMAP_RADIUS_TILES * MINIMAP_SCALE + (int)(offset_x * MINIMAP_SCALE);
	int player_pixel_y = MINIMAP_RADIUS_TILES * MINIMAP_SCALE + (int)(offset_y * MINIMAP_SCALE);

	// Draw the main body of the player (circular part)
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if (i * i + j * j <= 4) // Smaller circle for the body
			{
				int px = player_pixel_x + i;
				int py = player_pixel_y + j;

				// Check if pixel is within minimap circle
				int dx = px - MINIMAP_RADIUS_PIXELS;
				int dy = py - MINIMAP_RADIUS_PIXELS;
				if (dx * dx + dy * dy <= MINIMAP_RADIUS_PIXELS * MINIMAP_RADIUS_PIXELS)
				{
					my_mlx_pixel_put(game,
						MINIMAP_OFFSET_X + px,
						MINIMAP_OFFSET_Y + py,
						0x00FF00); // Green for better visibility
				}
			}
			j++;
		}
		i++;
	}

	// Draw the directional point/arrow
	for (int dist = 1; dist <= 4; dist++)
	{
		int point_x = player_pixel_x + (int)(game->player.dir_x * dist);
		int point_y = player_pixel_y + (int)(game->player.dir_y * dist);

		// Make the point narrower as it extends outward
		int width = (5 - dist) / 2; // Width decreases from 2 to 0

		for (int w = -width; w <= width; w++)
		{
			// Calculate perpendicular offset for width
			int perp_x = point_x + (int)(-game->player.dir_y * w);
			int perp_y = point_y + (int)(game->player.dir_x * w);

			// Check if pixel is within minimap circle
			int dx = perp_x - MINIMAP_RADIUS_PIXELS;
			int dy = perp_y - MINIMAP_RADIUS_PIXELS;
			if (dx * dx + dy * dy <= MINIMAP_RADIUS_PIXELS * MINIMAP_RADIUS_PIXELS)
			{
				my_mlx_pixel_put(game,
					MINIMAP_OFFSET_X + perp_x,
					MINIMAP_OFFSET_Y + perp_y,
					0x00FF00); // Same green color
			}
		}
	}
}

// Clear the circular area of the minimap
static void	draw_minimap_background_circle(t_game *game)
{
	int	x = 0;
	int	y;
	int	dx, dy;

	while (x < MINIMAP_DIAMETER)
	{
		y = 0;
		while (y < MINIMAP_DIAMETER)
		{
			dx = x - MINIMAP_RADIUS_PIXELS;
			dy = y - MINIMAP_RADIUS_PIXELS;
			if (dx * dx + dy * dy <= MINIMAP_RADIUS_PIXELS * MINIMAP_RADIUS_PIXELS)
				my_mlx_pixel_put(game,
					MINIMAP_OFFSET_X + x,
					MINIMAP_OFFSET_Y + y,
					0x000000);
			y++;
		}
		x++;
	}
}

// Main minimap drawing function
void	draw_minimap(t_game *game)
{
	draw_minimap_background_circle(game);
	draw_moving_minimap_tiles(game);
	draw_accurate_player_dot(game);
}
