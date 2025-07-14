/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_bonus_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:34:58 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/14 20:45:06 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	get_door_texture(t_game *game, t_ray *ray,
			int *tex_num, double *wall_x)
{
	*tex_num = 4;
	if (ray->side == 0)
		*wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		*wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
}

static void	get_vertical_wall_texture(t_ray *ray, int *tex_num)
{
	if (ray->step_x > 0)
		*tex_num = 3;
	else
		*tex_num = 2;
}

static void	get_horizontal_wall_texture(t_ray *ray, int *tex_num)
{
	if (ray->step_y > 0)
		*tex_num = 1;
	else
		*tex_num = 0;
}

void	get_regular_wall_texture(t_game *game, t_ray *ray,
			int *tex_num, double *wall_x)
{
	if (ray->side == 0)
	{
		get_vertical_wall_texture(ray, tex_num);
		*wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		get_horizontal_wall_texture(ray, tex_num);
		*wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	}
}

void	draw_texture_column(t_game *game, t_ray *ray, t_draw_params *params)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	step = 1.0 * game->textures[params->tex_num].height / ray->line_height;
	tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2
			+ ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (game->textures[params->tex_num].height - 1);
		tex_pos += step;
		color = get_texture_color(&game->textures[params->tex_num],
				params->tex_x, tex_y);
		if (color != 0)
			my_mlx_pixel_put(game, params->x, y, color);
		y++;
	}
}
