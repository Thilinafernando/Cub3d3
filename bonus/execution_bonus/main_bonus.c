/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:20:43 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/14 19:15:10 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	init_game_struct(t_game *game)
{
	game->minimap = malloc(sizeof(t_minimap));
	if (!game->minimap)
		return ((void)ft_printf(2, "Error: Minimap\n"));
	game->weapon_texture.img = NULL;
	game->weapon_texture.addr = NULL;
	game->weapon_texture.width = 0;
	game->weapon_texture.height = 0;
	game->minimap->full = 0;
	game->prev_mouse_x = -1;
	game->mouse_enabled = 1;
}

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

static int	initialize_game(t_game *game)
{
	if (init_mlx(game) == -1)
	{
		free_all(game->info);
		return (1);
	}
	if (load_textures(game) == -1)
	{
		free_game_resources(game);
		free_all(game->info);
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
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_hook(game->win, 4, 1L << 2, mouse_press, game);
	mlx_hook(game->win, 5, 1L << 3, mouse_release, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

int	main(int ac, char **av)
{
	t_info	info;
	t_game	game;

	init_struct(&info);
	if (validate_input(ac, av, &info))
		return (1);
	ft_memset(&game, 0, sizeof(t_game));
	game.info = &info;
	init_game_struct(&game);
	if (initialize_game(&game))
		return (1);
	setup_event_handlers(&game);
	mlx_loop(game.mlx);
	free_game_resources(&game);
	free_all(&info);
	return (0);
}
