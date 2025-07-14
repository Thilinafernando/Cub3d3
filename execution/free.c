/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:14:41 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/12 21:16:05 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_game_resources(t_game *game)
{
	if (game->mlx)
	{
		free_textures(game);
		if (game->img)
		{
			mlx_destroy_image(game->mlx, game->img);
			game->img = NULL;
		}
		if (game->win)
		{
			mlx_destroy_window(game->mlx, game->win);
			game->win = NULL;
		}
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
		{
			mlx_destroy_image(game->mlx, game->textures[i].img);
			game->textures[i].img = NULL;
		}
		i++;
	}
}

void	free_mat(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	get_texture_number(t_ray *ray)
{
	int	tex_num;

	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			tex_num = 3;
		else
			tex_num = 2;
	}
	else
	{
		if (ray->step_y > 0)
			tex_num = 1;
		else
			tex_num = 0;
	}
	return (tex_num);
}
