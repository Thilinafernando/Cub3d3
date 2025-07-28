/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:17:41 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/28 19:20:26 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->keys[keycode] = 1;
	if (keycode == 65361)
		game->left_arrow = 1;
	if (keycode == 65363)
		game->right_arrow = 1;
	if (keycode == 65307)
		close_game(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->keys[keycode] = 0;
	if (keycode == 65361)
		game->left_arrow = 0;
	if (keycode == 65363)
		game->right_arrow = 0;
	return (0);
}

int	game_loop(t_game *game)
{
	move_player(game);
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	close_game(t_game *game)
{
	free_game_resources(game);
	free_all(game->info);
	exit(0);
	return (0);
}
