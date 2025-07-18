/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:20:40 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/12 21:14:57 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	load_texture(t_game *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (ft_printf(2, "Error: Failed to load texture %s\n", path), -1);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	if (!texture->addr)
		return (ft_printf(2, "Error: Failed to get texture data\n"), -1);
	return (0);
}

int	load_textures(t_game *game)
{
	if (load_texture(game, &game->textures[0], game->info->no) == -1)
		return (-1);
	if (load_texture(game, &game->textures[1], game->info->so) == -1)
		return (-1);
	if (load_texture(game, &game->textures[2], game->info->we) == -1)
		return (-1);
	if (load_texture(game, &game->textures[3], game->info->ea) == -1)
		return (-1);
	return (0);
}

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = game->addr + (y * game->line_length
				+ x * (game->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	get_texture_color(t_texture *texture, int x, int y)
{
	char	*dst;

	if (x >= 0 && x < texture->width && y >= 0 && y < texture->height)
	{
		dst = texture->addr + (y * texture->line_length
				+ x * (texture->bits_per_pixel / 8));
		return (*(unsigned int *)dst);
	}
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
		if (ray->map_y >= 0 && ray->map_y < game->info->count
			&& ray->map_x >= 0
			&& ray->map_x < (int)ft_strlen(game->info->map[ray->map_y]))
		{
			if (game->info->map[ray->map_y][ray->map_x] == '1')
				ray->hit = 1;
		}
		else
			ray->hit = 1;
	}
}
