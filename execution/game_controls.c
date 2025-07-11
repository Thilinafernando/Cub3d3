/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:19:27 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/09 02:43:55 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
        
        // Free MLX display (this is important!)
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
    if (keycode == 65307) // ESC key
        close_game(game);
    return (0);
}

int key_release(int keycode, t_game *game)
{
    if (keycode >= 0 && keycode < 256)
        game->keys[keycode] = 0;
    return (0);
}

void move_player(t_game *game)
{
    // W key - move forward
    if (game->keys[119] || game->keys[87])
    {
        double new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
        double new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
        
        if (game->info->map[(int)new_y][(int)game->player.x] != '1')
            game->player.y = new_y;
        if (game->info->map[(int)game->player.y][(int)new_x] != '1')
            game->player.x = new_x;
    }
    
    // S key - move backward
    if (game->keys[115] || game->keys[83])
    {
        double new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
        double new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
        
        if (game->info->map[(int)new_y][(int)game->player.x] != '1')
            game->player.y = new_y;
        if (game->info->map[(int)game->player.y][(int)new_x] != '1')
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