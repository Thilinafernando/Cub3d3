/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_controls_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:19:27 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/11 18:17:35 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void free_game_resources(t_game *game)
{
    if (game->mlx)
    {
        // Free textures first
        free_textures(game);
        
        // Free main image
        if (game->img)
        {
            mlx_destroy_image(game->mlx, game->img);
            game->img = NULL;
        }
        
        // Free window
        if (game->win)
        {
            mlx_destroy_window(game->mlx, game->win);
            game->win = NULL;
        }
        
        // Free MLX display
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        game->mlx = NULL;
    }
}

void free_textures(t_game *game)
{
    int i;
    
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

int key_press(int keycode, t_game *game)
{
    if (keycode >= 0 && keycode < 256)
        game->keys[keycode] = 1;

    if (keycode == 65307) // ESC
        close_game(game);

    if (keycode == 'e' || keycode == 'E') // Door interaction key
        try_toggle_door(game);
    return (0);
}

void try_toggle_door(t_game *game)
{
    int target_x = (int)(game->player.x + game->player.dir_x);
    int target_y = (int)(game->player.y + game->player.dir_y);

    // Only proceed if the tile is actually a door ('D') in the map
    if (game->info->map[target_y][target_x] != 'D')
        return;

    // Toggle the door open/closed
    for (int i = 0; i < game->door_count; i++)
    {
        if (game->doors[i].x == target_x && game->doors[i].y == target_y)
        {
            game->doors[i].is_open = !game->doors[i].is_open;
            return;
        }
    }

    // Optional: If the tile is 'D' but the door wasn't added to the list yet
    if (game->door_count < MAX_DOORS)
    {
        game->doors[game->door_count].x = target_x;
        game->doors[game->door_count].y = target_y;
        game->doors[game->door_count].is_open = 1;
        game->door_count++;
    }
}


void try_open_close_door(t_game *game)
{
    int check_x = (int)(game->player.x + game->player.dir_x);
    int check_y = (int)(game->player.y + game->player.dir_y);

    if (check_y >= 0 && check_y < game->info->count &&
        check_x >= 0 && check_x < (int)ft_strlen(game->info->map[check_y]))
    {
        if (game->info->map[check_y][check_x] == 'D')
        {
            game->info->map[check_y][check_x] = '0'; // Open door (make it walkable)
        }
        else if (game->info->map[check_y][check_x] == '0')
        {
            game->info->map[check_y][check_x] = 'D'; // Close door
        }
    }
}

int is_wall_or_closed_door(t_game *game, double x, double y)
{
    int map_x = (int)x;
    int map_y = (int)y;
    char tile = game->info->map[map_y][map_x];

    if (tile == '1')
        return 1;
    if (tile == 'D' && !is_door_open(game, map_x, map_y))
        return 1;
    return 0;
}

int key_release(int keycode, t_game *game)
{
    if (keycode >= 0 && keycode < 256)
        game->keys[keycode] = 0;
    return (0);
}

void move_player(t_game *game)
{
    double new_x, new_y;

    // W key - move forward
    if (game->keys[119] || game->keys[87])
    {
        new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
        new_y = game->player.y + game->player.dir_y * MOVE_SPEED;

        if (!is_wall_or_closed_door(game, game->player.x, new_y))
            game->player.y = new_y;
        if (!is_wall_or_closed_door(game, new_x, game->player.y))
            game->player.x = new_x;
    }

    // S key - move backward
    if (game->keys[115] || game->keys[83])
    {
        new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
        new_y = game->player.y - game->player.dir_y * MOVE_SPEED;

        if (!is_wall_or_closed_door(game, game->player.x, new_y))
            game->player.y = new_y;
        if (!is_wall_or_closed_door(game, new_x, game->player.y))
            game->player.x = new_x;
    }

    // A key - rotate left
    if (game->keys[97] || game->keys[65])
    {
        double old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(ROT_SPEED) - game->player.dir_y * sin(ROT_SPEED);
        game->player.dir_y = old_dir_x * sin(ROT_SPEED) + game->player.dir_y * cos(ROT_SPEED);
        double old_plane_x = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(ROT_SPEED) - game->player.plane_y * sin(ROT_SPEED);
        game->player.plane_y = old_plane_x * sin(ROT_SPEED) + game->player.plane_y * cos(ROT_SPEED);
    }

    // D key - rotate right
    if (game->keys[100] || game->keys[68])
    {
        double old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED) - game->player.dir_y * sin(-ROT_SPEED);
        game->player.dir_y = old_dir_x * sin(-ROT_SPEED) + game->player.dir_y * cos(-ROT_SPEED);
        double old_plane_x = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED) - game->player.plane_y * sin(-ROT_SPEED);
        game->player.plane_y = old_plane_x * sin(-ROT_SPEED) + game->player.plane_y * cos(-ROT_SPEED);
    }
}

int game_loop(t_game *game)
{
    move_player(game);
    raycast(game);
    draw_minimap(game);
    draw_weapon(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}

void free_mat(char **matrix)
{
    int i;
    
    if (!matrix)
        return;
    
    i = 0;
    while (matrix[i])
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
}

int close_game(t_game *game)
{
    free_game_resources(game);
    free_all(game->info);
    exit(0);
    return (0);
}

int init_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (ft_printf(2, "Error: MLX initialization failed\n"), -1);
    
    game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
    if (!game->win)
        return (ft_printf(2, "Error: Window creation failed\n"), -1);
    
    game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!game->img)
        return (ft_printf(2, "Error: Image creation failed\n"), -1);
    
    game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
                                   &game->line_length, &game->endian);
    if (!game->addr)
        return (ft_printf(2, "Error: Getting image data failed\n"), -1);
    
    return (0);
}