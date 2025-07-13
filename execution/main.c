/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:20:43 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/13 21:49:00 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int main(int ac, char **av)
{
    t_info info;
    t_game game;
    init_struct(&info);
    t_minimap   minimap;

    // Parse the map (your friend's code)
    game.minimap = &minimap;
    if (ac != 2)
        return (ft_printf(2, "Error: Invalid number of arguments.\n"), 1);
    if (!extention_check(av[1]))
        return (1);
    if (fill_file(av[1], &info))
        return (free_all(&info), 1);
    if (paths(&info))
        return (free_all(&info), 1);
    if (fill_map(&info))
        return (free_all(&info), 1);
    if (validate_map(&info))
        return (free_all(&info), 1);

    // Initialize game
    ft_memset(&game, 0, sizeof(t_game));
    game.info = &info;
    game.prev_mouse_x = -1;      // Initialize mouse tracking
    game.mouse_enabled = 1;      // Enable mouse by default

    // Initialize MLX and load textures
    if (init_mlx(&game) == -1)
    {
        free_all(&info);
        return (1);
    }

    if (load_textures(&game) == -1)
    {
        free_game_resources(&game);
        free_all(&info);
        return (1);
    }

    // Initialize player
    init_player(&game);

    // Set up event handlers with proper masks
    mlx_hook(game.win, 2, 1L<<0, key_press, &game);              // KeyPress
    mlx_hook(game.win, 3, 1L<<1, key_release, &game);            // KeyRelease
    mlx_hook(game.win, 17, 0, close_game, &game);                // DestroyNotify
    mlx_loop_hook(game.mlx, game_loop, &game);

    // Optional: Hide cursor for FPS-style movement
    // mlx_mouse_hide(game.mlx, game.win);

    // Start the game loop
    mlx_loop(game.mlx);

    // This should never be reached, but just in case
    free_game_resources(&game);
    free_all(&info);
    return (0);
}
