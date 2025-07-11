/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_mouse_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 23:13:24 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/07/11 18:27:50 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int mouse_move(int x, int y, t_game *game)
{
    (void)y;

    // Initialize mouse position on first call
    if (game->prev_mouse_x == -1)
    {
        game->prev_mouse_x = x;
        game->mouse_x = x;
        game->mouse_y = y;
        return (0);
    }

    // Calculate mouse movement
    int dx = x - game->prev_mouse_x;

    // Only process significant movement
    if (abs(dx) < 2)
        return (0);

    // Apply mouse sensitivity
    double mouse_sensitivity = 0.003;
    double rotation_angle = dx * mouse_sensitivity;

    // Limit rotation speed
    if (rotation_angle > 0.1)
        rotation_angle = 0.1;
    if (rotation_angle < -0.1)
        rotation_angle = -0.1;

    // Apply rotation
    double old_dir_x = game->player.dir_x;
    double old_plane_x = game->player.plane_x;

    game->player.dir_x = game->player.dir_x * cos(rotation_angle) - game->player.dir_y * sin(rotation_angle);
    game->player.dir_y = old_dir_x * sin(rotation_angle) + game->player.dir_y * cos(rotation_angle);
    game->player.plane_x = game->player.plane_x * cos(rotation_angle) - game->player.plane_y * sin(rotation_angle);
    game->player.plane_y = old_plane_x * sin(rotation_angle) + game->player.plane_y * cos(rotation_angle);

    // Update mouse position
    game->prev_mouse_x = x;
    game->mouse_x = x;
    game->mouse_y = y;

    return (0);
}

int mouse_press(int button, int x, int y, t_game *game)
{
    (void)x;
    (void)y;

    if (button == 1) // Left mouse button
    {
        // You can add shooting or interaction here
        printf("Left mouse pressed at (%d, %d)\n", x, y);
    }
    else if (button == 3) // Right mouse button
    {
        // Toggle mouse look on/off
        game->mouse_enabled = !game->mouse_enabled;
        if (game->mouse_enabled)
            printf("Mouse look enabled\n");
        else
            printf("Mouse look disabled\n");
    }

    return (0);
}

int mouse_release(int button, int x, int y, t_game *game)
{
    (void)button;
    (void)x;
    (void)y;
    (void)game;

    return (0);
}
