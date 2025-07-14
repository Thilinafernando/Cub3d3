/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 23:31:13 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/14 19:06:41 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	key_release(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->keys[keycode] = 0;
	return (0);
}

int	game_loop(t_game *game)
{
	move_player(game);
	raycast(game);
	draw_minimap(game);
	draw_weapon(game);
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

int	key_press(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->keys[keycode] = 1;
	if (keycode == 65307)
		close_game(game);
	if (keycode == 'e' || keycode == 'E')
		try_toggle_door(game);
	return (0);
}
