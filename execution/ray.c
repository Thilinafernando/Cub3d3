/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:41:34 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/25 18:57:45 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	set_ray_x_direction(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x)
			* ray->delta_dist_x;
	}
}

static void	set_ray_y_direction(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y)
			* ray->delta_dist_y;
	}
}

static void	calculate_delta_distances(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	calculate_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	calculate_delta_distances(ray);
	ray->hit = 0;
	set_ray_x_direction(game, ray);
	set_ray_y_direction(game, ray);
}

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
