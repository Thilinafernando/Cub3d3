/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:20:40 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/09 17:05:43 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void init_player(t_game *game)
{
    char player_dir = game->info->map[game->info->player_y][game->info->player_x];
    
    game->player.x = game->info->player_x + 0.5;
    game->player.y = game->info->player_y + 0.5;
    
    if (player_dir == 'N')
    {
        game->player.dir_x = 0;
        game->player.dir_y = -1;
        game->player.plane_x = 0.66;
        game->player.plane_y = 0;
    }
    else if (player_dir == 'S')
    {
        game->player.dir_x = 0;
        game->player.dir_y = 1;
        game->player.plane_x = -0.66;
        game->player.plane_y = 0;
    }
    else if (player_dir == 'E')
    {
        game->player.dir_x = 1;
        game->player.dir_y = 0;
        game->player.plane_x = 0;
        game->player.plane_y = 0.66;
    }
    else if (player_dir == 'W')
    {
        game->player.dir_x = -1;
        game->player.dir_y = 0;
        game->player.plane_x = 0;
        game->player.plane_y = -0.66;
    }
}

int load_texture(t_game *game, t_texture *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width, &texture->height);
    if (!texture->img)
        return (ft_printf(2, "Error: Failed to load texture %s\n", path), -1);
    texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
                                      &texture->line_length, &texture->endian);
    if (!texture->addr)
        return (ft_printf(2, "Error: Failed to get texture data\n"), -1);
    
    return (0);
}

int load_textures(t_game *game) // with the bonus
{
    if (load_texture(game, &game->textures[0], game->info->no) == -1)
        return (-1);
    if (load_texture(game, &game->textures[1], game->info->so) == -1)
        return (-1);
    if (load_texture(game, &game->textures[2], game->info->we) == -1)
        return (-1);
    if (load_texture(game, &game->textures[3], game->info->ea) == -1)
        return (-1);
    
    // Load weapon texture with error checking
    if (load_texture(game, &game->weapon_texture, "xpm/weapon.xpm") == -1)
    {
        ft_printf(2, "Error: Could not load weapon texture\n");
        return (-1);
    }
    if (load_texture(game, &game->textures[4], "xpm/door.xpm") == -1)
        return (-1);
    // Debug: print weapon texture info
    ft_printf(1, "Weapon texture loaded: %dx%d\n", 
              game->weapon_texture.width, game->weapon_texture.height);
    ft_printf(1, "wall texture loaded: %dx%d\n", 
              game->textures[3].width, game->textures[3].height);
    return (0);
}


void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    char *dst;
    
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
    {
        dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}

int get_texture_color(t_texture *texture, int x, int y)
{
    char *dst;
    
    if (x >= 0 && x < texture->width && y >= 0 && y < texture->height)
    {
        dst = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
        return (*(unsigned int*)dst);
    }
    return (0);
}

void perform_dda(t_game *game, t_ray *ray)
{
    while (ray->hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }

        // Bounds check
        if (ray->map_y >= 0 && ray->map_y < game->info->count && 
            ray->map_x >= 0 && ray->map_x < (int)ft_strlen(game->info->map[ray->map_y]))
        {
            char tile = game->info->map[ray->map_y][ray->map_x];
            if (tile == '1' || (tile == 'D' && !is_door_open(game, ray->map_x, ray->map_y)))
                ray->hit = 1;
        }
        else
        {
            ray->hit = 1;
        }
    }
}


void calculate_ray(t_game *game, t_ray *ray, int x)
{
    ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
    ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
    ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
    
    ray->map_x = (int)game->player.x;
    ray->map_y = (int)game->player.y;
    
    ray->delta_dist_x = (ray->ray_dir_x == 0) ? 1e30 : fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = (ray->ray_dir_y == 0) ? 1e30 : fabs(1 / ray->ray_dir_y);
    
    ray->hit = 0;
    
    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_dist_x;
    }
    
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_dist_y;
    }
}

/* void draw_wall(t_game *game, t_ray *ray, int x)
{
    int tex_num;
    double wall_x;
    int tex_x;
    
    // Determine which texture to use based on wall direction
    if (ray->side == 0)
        tex_num = (ray->step_x > 0) ? 3 : 2; // EA or WE
    else
        tex_num = (ray->step_y > 0) ? 1 : 0; // SO or NO
    
    // Calculate wall hit position
    if (ray->side == 0)
        wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
    else
        wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
    wall_x -= floor(wall_x);
    
    // Calculate texture x coordinate
    tex_x = (int)(wall_x * (double)TEXTURE_SIZE);
    if (ray->side == 0 && ray->ray_dir_x > 0)
        tex_x = TEXTURE_SIZE - tex_x - 1;
    if (ray->side == 1 && ray->ray_dir_y < 0)
        tex_x = TEXTURE_SIZE - tex_x - 1;
    
    // Draw the wall strip
    for (int y = ray->draw_start; y < ray->draw_end; y++)
    {
        int d = y * 256 - WINDOW_HEIGHT * 128 + ray->line_height * 128;
        int tex_y = ((d * TEXTURE_SIZE) / ray->line_height) / 256;
        
        if (tex_y >= 0 && tex_y < TEXTURE_SIZE)
        {
            int color = get_texture_color(&game->textures[tex_num], tex_x, tex_y);
            my_mlx_pixel_put(game, x, y, color);
        }
    }
} */

void draw_weapon(t_game *game)
{
    int weapon_width = game->weapon_texture.width;
    int weapon_height = game->weapon_texture.height;

    // Position weapon at bottom center of screen
    int x_start = (WINDOW_WIDTH - weapon_width) / 2;
    int y_start = WINDOW_HEIGHT - weapon_height;

    for (int y = 0; y < weapon_height; y++)
    {
        for (int x = 0; x < weapon_width; x++)
        {
            int color = get_texture_color(&game->weapon_texture, x, y);
            
            // Better transparency check - black pixels are transparent
            if (color != 0x000000 && (color & 0x00FFFFFF) != 0)
            {
                int screen_x = x_start + x;
                int screen_y = y_start + y;
                
                // Boundary check
                if (screen_x >= 0 && screen_x < WINDOW_WIDTH && 
                    screen_y >= 0 && screen_y < WINDOW_HEIGHT)
                {
                    my_mlx_pixel_put(game, screen_x, screen_y, color);
                }
            }
        }
    }
}

void draw_wall(t_game *game, t_ray *ray, int x)
{
    int tex_num;
    double wall_x;
    int tex_x;
    double step;
    double tex_pos;

    // 1. Detect if ray hit a door
    char hit_tile = game->info->map[ray->map_y][ray->map_x];
    if (hit_tile == 'D')
    {
        tex_num = 4; // index 4: door texture (you must load it!)
    }
    else
    {
        // 2. Determine which texture to use based on wall direction
        if (ray->side == 0)
        {
            tex_num = (ray->step_x > 0) ? 3 : 2; // EA or WE
            wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
        }
        else
        {
            tex_num = (ray->step_y > 0) ? 1 : 0; // SO or NO
            wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
        }
    }

    if (hit_tile != 'D') // only needed if not a door
        wall_x -= floor(wall_x);
    else
        wall_x = (ray->side == 0) ? game->player.y + ray->perp_wall_dist * ray->ray_dir_y
                                  : game->player.x + ray->perp_wall_dist * ray->ray_dir_x,
        wall_x -= floor(wall_x);

    tex_x = (int)(wall_x * (double)game->textures[tex_num].width);

    if (ray->side == 0 && ray->ray_dir_x > 0)
        tex_x = game->textures[tex_num].width - tex_x - 1;
    if (ray->side == 1 && ray->ray_dir_y < 0)
        tex_x = game->textures[tex_num].width - tex_x - 1;

    step = 1.0 * game->textures[tex_num].height / ray->line_height;
    tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2 + ray->line_height / 2) * step;

    for (int y = ray->draw_start; y < ray->draw_end; y++)
    {
        int tex_y = (int)tex_pos & (game->textures[tex_num].height - 1);
        tex_pos += step;

        int color = get_texture_color(&game->textures[tex_num], tex_x, tex_y);
        if (color != 0)
            my_mlx_pixel_put(game, x, y, color);
    }
}

void draw_floor_ceiling(t_game *game, t_ray *ray, int x)
{
    int y;
    
    // Draw ceiling
    for (y = 0; y < ray->draw_start; y++)
        my_mlx_pixel_put(game, x, y, game->info->rgb_c);
    
    // Draw floor
    for (y = ray->draw_end; y < WINDOW_HEIGHT; y++)
        my_mlx_pixel_put(game, x, y, game->info->rgb_f);
}

void raycast(t_game *game)
{
    t_ray ray;
    
    for (int x = 0; x < WINDOW_WIDTH; x++)
    {
        calculate_ray(game, &ray, x);
        perform_dda(game, &ray);
        
        // Calculate distance and wall height
        if (ray.side == 0)
            ray.perp_wall_dist = (ray.map_x - game->player.x + (1 - ray.step_x) / 2) / ray.ray_dir_x;
        else
            ray.perp_wall_dist = (ray.map_y - game->player.y + (1 - ray.step_y) / 2) / ray.ray_dir_y;
        
        ray.line_height = (int)(WINDOW_HEIGHT / ray.perp_wall_dist);
        ray.draw_start = -ray.line_height / 2 + WINDOW_HEIGHT / 2;
        if (ray.draw_start < 0)
            ray.draw_start = 0;
        ray.draw_end = ray.line_height / 2 + WINDOW_HEIGHT / 2;
        if (ray.draw_end >= WINDOW_HEIGHT)
            ray.draw_end = WINDOW_HEIGHT - 1;
        
        draw_floor_ceiling(game, &ray, x);
        draw_wall(game, &ray, x);
    }
}

void init_doors(t_game *game)
{
    game->door_count = 0;

    for (int y = 0; y < game->info->count; y++)
    {
        for (int x = 0; game->info->map[y][x]; x++)
        {
            if (game->info->map[y][x] == 'D')
            {
                game->doors[game->door_count].x = x;
                game->doors[game->door_count].y = y;
                game->doors[game->door_count].is_open = 0;
                game->door_count++;

                if (game->door_count >= MAX_DOORS)
                    return; // prevent overflow
            }
        }
    }
}


int is_door_open(t_game *game, int x, int y)
{
    for (int i = 0; i < game->door_count; i++)
    {
        if (game->doors[i].x == x && game->doors[i].y == y)
            return game->doors[i].is_open;
    }
    return 0; // closed by default
}


