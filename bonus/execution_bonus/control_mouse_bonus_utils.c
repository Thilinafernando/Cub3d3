/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_mouse_bonus_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:01:01 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/13 22:01:57 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	mouse_press(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1 && !game->is_shooting)
	{
		game->is_shooting = 1;
		game->shoot_timer = 5;
	}
	else if (button == 3)
	{
		game->mouse_enabled = !game->mouse_enabled;
		if (game->mouse_enabled)
			printf("Mouse look enabled\n");
		else
			printf("Mouse look disabled\n");
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_game *game)
{
	(void)button;
	(void)x;
	(void)y;
	(void)game;
	return (0);
}
