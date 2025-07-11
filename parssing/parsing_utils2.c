/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 03:02:53 by tkurukul          #+#    #+#             */
/*   Updated: 2025/07/03 19:49:57 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_matrix(char **matrix)
{
	int	i;
	int	j;

	i = 0;
	while (matrix[i] != NULL)
	{
		j = 0;
		while (matrix[i][j] != '\0')
		{
			putchar(matrix[i][j]);
			j++;
		}
		i++;
	}
}

int	find_player_pos(char **matrix, t_info *info)
{
	int		y;
	int		x;
	int		flag;

	y = -1;
	flag = 0;
	while (matrix[++y])
	{
		x = -1;
		while (matrix[y][++x])
		{
			if (matrix[y][x] == 'W' || matrix[y][x] == 'E'
				|| matrix[y][x] == 'N' || matrix[y][x] == 'S')
			{
				info->player_y = y;
				info->player_x = x;
				flag++;
			}
		}
	}
	if (flag > 1)
		return (ft_printf(2, "Error: '%d' player positions in map.\n", flag));
	if (flag < 1)
		return (ft_printf(2, "Error: No player starting position.\n"));
	return (0);
}

bool	verify_char(char c)
{
	if (c == '1' || c == 'Z' || c == '\0' || c == '\n' || !c)
		return (false);
	return (true);
}

void	flood_fill(int x, int y, t_info *info)
{
	if (y < 0 || x < 0 || !info->tmp[y] || x >= (int)ft_strlen(info->tmp[y]))
		return ;
	if (info->tmp[y][x] == '0' || info->tmp[y][x] == 'W'
		|| info->tmp[y][x] == 'E'
		|| info->tmp[y][x] == 'S' || info->tmp[y][x] == 'N')
	{
		info->flood_flag = -42;
		return ;
	}
	info->tmp[y][x] = 'Z';
	if (info->tmp[y][x + 1] && verify_char(info->tmp[y][x + 1]))
		flood_fill(x + 1, y, info);
	if (x != 0 && info->tmp[y][x - 1] && verify_char(info->tmp[y][x - 1]))
		flood_fill(x - 1, y, info);
	if (info->tmp[y + 1] && verify_char(info->tmp[y + 1][x]))
		flood_fill(x, y + 1, info);
	if (y != 0 && info->tmp[y - 1] && verify_char(info->tmp[y - 1][x]))
		flood_fill(x, y - 1, info);
	return ;
}

int	check_playable(t_info *info)
{
	if (find_player_pos(info->map, info))
		return (-1);
	if (info->map[info->player_y][info->player_x + 1] != '0'
		&& info->map[info->player_y + 1][info->player_x] != '0'
		&& info->map[info->player_y][info->player_x - 1] != '0'
		&& info->map[info->player_y - 1][info->player_x] != '0')
		return (ft_printf(2, "Error: Map does not contain\
			any player accessable room.\n"));
	return (0);
}
