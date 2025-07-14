/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:35:09 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/13 22:07:33 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	get_wall_texture(t_game *game, t_ray *ray,
				int *tex_num, double *wall_x)
{
	char	hit_tile;

	hit_tile = game->info->map[ray->map_y][ray->map_x];
	if (hit_tile == 'D')
		get_door_texture(game, ray, tex_num, wall_x);
	else
		get_regular_wall_texture(game, ray, tex_num, wall_x);
	*wall_x -= floor(*wall_x);
}

static int	get_texture_x(t_game *game, t_ray *ray, int tex_num, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)game->textures[tex_num].width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = game->textures[tex_num].width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = game->textures[tex_num].width - tex_x - 1;
	return (tex_x);
}

void	draw_wall(t_game *game, t_ray *ray, int x)
{
	int				tex_num;
	double			wall_x;
	int				tex_x;
	t_draw_params	params;

	get_wall_texture(game, ray, &tex_num, &wall_x);
	tex_x = get_texture_x(game, ray, tex_num, wall_x);
	params.tex_num = tex_num;
	params.tex_x = tex_x;
	params.x = x;
	draw_texture_column(game, ray, &params);
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
