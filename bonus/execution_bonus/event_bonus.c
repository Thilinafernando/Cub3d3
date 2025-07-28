/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 23:31:13 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/28 21:28:23 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
	int	target_x;
	int	target_y;

	if (keycode >= 0 && keycode < 256)
		game->keys[keycode] = 1;
	if (keycode == 65361)
		game->left_arrow = 1;
	if (keycode == 65363)
		game->right_arrow = 1;
	if (keycode == 65307)
		close_game(game);
	if (keycode == 'e' || keycode == 'E')
	{
		target_x = (int)(game->player.x + game->player.dir_x);
		target_y = (int)(game->player.y + game->player.dir_y);
		if (target_y >= 0 && target_y < game->info->count && target_x
			>= 0 && target_x < (int)ft_strlen(game->info->map[target_y])
			&& game->info->map[target_y][target_x] == 'D')
		{
			game->is_using_hand = 1;
			game->hand_timer = 20;
		}
		try_toggle_door(game);
	}
	return (0);
}
