/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:59:05 by tkurukul          #+#    #+#             */
/*   Updated: 2025/07/24 21:43:26 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	extention_check(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '.')
		i++;
	if (str[i] == '\0')
	{
		ft_printf(2, "Error: Invalid map, \".cub\" extention needed.\n");
		return (false);
	}
	else
	{
		str = &str[i + 1];
		if (ft_strcmp(str, "cub"))
		{
			ft_printf(2, "Error: Incorrect extention.\n");
			return (false);
		}
	}
	return (true);
}

int	fill_file(char *map, t_info *info)
{
	int	fd;
	int	i;
	int	size;

	i = -1;
	fd = open(map, O_RDONLY | O_EXCL);
	if (fd == -1)
		return (ft_printf(2, "Error: Open failed.\n"));
	size = count_lines(map);
	info->file = malloc((size + 1) * sizeof(char *));
	if (!info->file)
		return (ft_printf(2, "Error: Malloc failed.\n"));
	info->file[0] = get_next_line(fd);
	while (info->file[++i])
		info->file[i + 1] = get_next_line(fd);
	info->file[i] = NULL;
	close(fd);
	return (0);
}

int	fill_map(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	info->count = 0;
	while (info->file[i] && !map_only(info->file[i]))
		i++;
	if (!info->file[i])
		return (ft_printf(2, "Error: File is missing the map.\n"));
	j = i - 1;
	while (info->file[++j])
		info->count++;
	info->map = malloc((info->count + 1) * sizeof(char *));
	if (!info->map)
		return (ft_printf(2, "Error: Malloc failed.\n"));
	j = 0;
	while (info->file[i])
	{
		info->map[j] = ft_strdup(info->file[i]);
		i++;
		j++;
	}
	info->map[j] = NULL;
	return (0);
}

int	validate_map(t_info *info)
{
	if (check_playable(info))
		return (-1);
	if (check_characters(info))
		return (-1);
	if (fill_tmp(info))
		return (-1);
	if (check_spaces(info))
		return (-1);
	flood_fill(0, 0, info);
	if (info->flood_flag == -42)
		return (ft_printf(2, "Error: Map not closed.\n"));
	print_matrix(info->tmp);
	free_mat(info->tmp);
	info->tmp = NULL;
	ft_printf(1, "Map is closed!\n");
	return (0);
}

/* int	main(int ac, char **av)
{
	t_info	info;

	init_struct(&info);
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
	free_all(&info);
} */
