/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:13:01 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/28 21:34:52 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	destroy_text2(t_game *game)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (game->weapon_fire_textures[i].img)
		{
			mlx_destroy_image(game->mlx, game->weapon_fire_textures[i].img);
			game->weapon_fire_textures[i].img = NULL;
		}
		i++;
	}
	if (game->hand_texture.img)
	{
		mlx_destroy_image(game->mlx, game->hand_texture.img);
		game->hand_texture.img = NULL;
	}
}

void	destroy_textures(t_game *game)
{
	int	i;

	if (!game || !game->mlx)
		return ;
	i = 0;
	while (i < 5)
	{
		if (game->textures[i].img)
		{
			mlx_destroy_image(game->mlx, game->textures[i].img);
			game->textures[i].img = NULL;
		}
		i++;
	}
	if (game->weapon_texture.img)
	{
		mlx_destroy_image(game->mlx, game->weapon_texture.img);
		game->weapon_texture.img = NULL;
	}
	
	destroy_text2(game);
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

void	free_game_resources(t_game *game)
{
	if (game->mlx)
	{
		destroy_textures(game);
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
	if (game->minimap)
		free(game->minimap);
}
