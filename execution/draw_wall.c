/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:47:02 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/12 21:40:51 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	calculate_wall_x(t_game *game, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	calculate_tex_x(t_game *game,
				t_ray *ray, double wall_x, int tex_num)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)game->textures[tex_num].width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = game->textures[tex_num].width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = game->textures[tex_num].width - tex_x - 1;
	return (tex_x);
}

static void	draw_wall_strip(t_game *game, t_ray *ray, int x, int tex_num)
{
	t_wall_vars	vars;
	int			tex_y;
	int			color;

	init_wall_vars(&vars, game, ray, tex_num);
	while (vars.y < ray->draw_end)
	{
		tex_y = (int)vars.tex_pos & (game->textures[tex_num].height - 1);
		vars.tex_pos += vars.step;
		color = get_texture_color(&game->textures[tex_num], vars.tex_x, tex_y);
		if (color != 0)
			my_mlx_pixel_put(game, x, vars.y, color);
		vars.y++;
	}
}

void	draw_wall(t_game *game, t_ray *ray, int x)
{
	int	tex_num;

	tex_num = get_texture_number(ray);
	draw_wall_strip(game, ray, x, tex_num);
}

void	draw_floor_ceiling(t_game *game, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		my_mlx_pixel_put(game, x, y, game->info->rgb_c);
		y++;
	}
	y = ray->draw_end;
	while (y < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(game, x, y, game->info->rgb_f);
		y++;
	}
}
