/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:15:37 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/25 17:34:27 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	init_doors(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	game->door_count = 0;
	while (y < game->info->count)
	{
		x = 0;
		while (game->info->map[y][x])
		{
			if (game->info->map[y][x] == 'D')
			{
				game->doors[game->door_count].x = x;
				game->doors[game->door_count].y = y;
				game->doors[game->door_count].is_open = 0;
				game->door_count++;
				if (game->door_count >= MAX_DOORS)
					return ;
			}
			x++;
		}
		y++;
	}
}

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_printf(2, "Error: MLX initialization failed\n"), -1);
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!game->win)
		return (ft_printf(2, "Error: Window creation failed\n"), -1);
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img)
		return (ft_printf(2, "Error: Image creation failed\n"), -1);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	if (!game->addr)
		return (ft_printf(2, "Error: Getting image data failed\n"), -1);
	return (0);
}

//added condition to skip the green screen we make
void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		if (color == 0x51FF00)
			return ;
		dst = game->addr + (y * game->line_length + x
				* (game->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
