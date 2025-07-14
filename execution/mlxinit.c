/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxinit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:19:56 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/12 21:39:00 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	init_wall_vars(t_wall_vars *vars, t_game *game, t_ray *ray, int tex_num)
{
	vars->wall_x = calculate_wall_x(game, ray);
	vars->tex_x = calculate_tex_x(game, ray, vars->wall_x, tex_num);
	vars->step = 1.0 * game->textures[tex_num].height / ray->line_height;
	vars->tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2 + ray->line_height / 2)
		* vars->step;
	vars->y = ray->draw_start;
}
