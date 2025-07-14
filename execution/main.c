/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:20:43 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/12 21:06:19 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	validate_input(int ac, char **av, t_info *info)
{
	if (ac != 2)
		return (ft_printf(2, "Error: Invalid number of arguments.\n"), 1);
	if (!extention_check(av[1]))
		return (1);
	if (fill_file(av[1], info))
		return (free_all(info), 1);
	if (paths(info))
		return (free_all(info), 1);
	if (fill_map(info))
		return (free_all(info), 1);
	if (validate_map(info))
		return (free_all(info), 1);
	return (0);
}

static int	initialize_game(t_game *game, t_info *info)
{
	ft_memset(game, 0, sizeof(t_game));
	game->info = info;
	game->prev_mouse_x = -1;
	game->mouse_enabled = 1;
	if (init_mlx(game) == -1)
	{
		free_all(info);
		return (1);
	}
	if (load_textures(game) == -1)
	{
		free_game_resources(game);
		free_all(info);
		return (1);
	}
	init_player(game);
	return (0);
}

static void	setup_event_handlers(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

int	main(int ac, char **av)
{
	t_info	info;
	t_game	game;

	init_struct(&info);
	if (validate_input(ac, av, &info))
		return (1);
	if (initialize_game(&game, &info))
		return (1);
	setup_event_handlers(&game);
	mlx_loop(game.mlx);
	free_game_resources(&game);
	free_all(&info);
	return (0);
}
