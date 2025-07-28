/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:34:42 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/25 16:54:27 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	raycast(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		calculate_ray(game, &ray, x);
		perform_dda(game, &ray);
		if (ray.side == 0)
			ray.perp_wall_dist = (ray.map_x - game->player.x
					+ (1 - ray.step_x) / 2) / ray.ray_dir_x;
		else
			ray.perp_wall_dist = (ray.map_y - game->player.y
					+ (1 - ray.step_y) / 2) / ray.ray_dir_y;
		ray.line_height = (int)(WINDOW_HEIGHT / ray.perp_wall_dist);
		ray.draw_start = -ray.line_height / 2 + WINDOW_HEIGHT / 2;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = ray.line_height / 2 + WINDOW_HEIGHT / 2;
		if (ray.draw_end >= WINDOW_HEIGHT)
			ray.draw_end = WINDOW_HEIGHT - 1;
		draw_floor_ceiling(game, &ray, x);
		draw_wall(game, &ray, x);
		x++;
	}
}

static int	check_hit_tile(t_game *game, t_ray *ray)
{
	char	tile;

	if (ray->map_y < 0 || ray->map_y >= game->info->count
		|| ray->map_x < 0
		|| ray->map_x >= (int)ft_strlen(game->info->map[ray->map_y]))
	{
		return (1);
	}
	tile = game->info->map[ray->map_y][ray->map_x];
	if (tile == '1' || (tile == 'D'
			&& !is_door_open(game, ray->map_x, ray->map_y)))
		return (1);
	return (0);
}

void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (check_hit_tile(game, ray))
			ray->hit = 1;
	}
}
