/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:33:38 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/13 20:54:35 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
	if (load_texture(game, &game->weapon_texture, "xpm/weapon.xpm") == -1)
	{
		ft_printf(2, "Error: Could not load weapon texture\n");
		return (-1);
	}
	if (load_texture(game, &game->textures[4], "xpm/door.xpm") == -1)
		return (-1);
	if (load_texture(game, &game->weapon_fire_textures[0],
			"xpm/weapon1.xpm") == -1)
		return (-1);
	if (load_texture(game, &game->weapon_fire_textures[1],
			"xpm/weapon2.xpm") == -1)
		return (-1);
	return (0);
}

int	get_texture_color(t_texture *texture, int x, int y)
{
	char	*dst;

	if (x >= 0 && x < texture->width && y >= 0 && y < texture->height)
	{
		dst = texture->addr + (y * texture->line_length + x
				* (texture->bits_per_pixel / 8));
		return (*(unsigned int *)dst);
	}
	return (0);
}
