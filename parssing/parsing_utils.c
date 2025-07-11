/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 03:05:56 by tkurukul          #+#    #+#             */
/*   Updated: 2025/07/03 19:39:51 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	paths_check(t_info *info, int i, char *str)
{
	int	j;

	if (!ft_strncmp(info->file[i], "NO", 2)
		|| !ft_strncmp(info->file[i], "SO", 2)
		|| !ft_strncmp(info->file[i], "WE", 2)
		|| !ft_strncmp(info->file[i], "EA", 2)
		|| !ft_strncmp(info->file[i], "F", 1)
		|| !ft_strncmp(info->file[i], "C", 1))
	{
		j = 1;
		ft_strlcpy(str, info->file[i], 3);
		if (paths_conditions(info, i, j, str))
			return (-1);
	}
	return (0);
}

int	paths(t_info *info)
{
	int		i;
	char	str[3];

	i = -1;
	ft_bzero(str, 3);
	while (info->file[++i])
	{
		if (paths_check(info, i, str) == -1)
			return (-1);
	}
	if (!info->ea || !info->no || !info->so || !info->we)
		return (ft_printf(2, "Error: Not all textures are\
			 included in the file.\n"));
	return (0);
}

int	accesable(t_info *info, int i, int j)
{
	if (i <= 0 || j <= 0)
		return (-1);
	if (info->tmp[i + 1][j] == '0' || info->tmp[i - 1][j] == '0'
		|| info->tmp[i][j + 1] == '0' || info->tmp[i][j - 1] == '0')
		return (-1);
	if (info->tmp[i + 1][j] == 'N' || info->tmp[i - 1][j] == 'N'
		|| info->tmp[i][j + 1] == 'N' || info->tmp[i][j - 1] == 'N')
		return (-1);
	if (info->tmp[i + 1][j] == 'S' || info->tmp[i - 1][j] == 'S'
		|| info->tmp[i][j + 1] == 'S' || info->tmp[i][j - 1] == 'S')
		return (-1);
	if (info->tmp[i + 1][j] == 'W' || info->tmp[i - 1][j] == 'W'
		|| info->tmp[i][j + 1] == 'W' || info->tmp[i][j - 1] == 'W')
		return (-1);
	if (info->tmp[i + 1][j] == 'E' || info->tmp[i - 1][j] == 'E'
		|| info->tmp[i][j + 1] == 'E' || info->tmp[i][j - 1] == 'E')
		return (-1);
	return (0);
}

int	check_spaces(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (info->tmp[++i])
	{
		j = -1;
		while (info->tmp[i][++j])
		{
			if (info->tmp[i][j] == 'L' && (accesable(info, i, j)))
				return (ft_printf(2, "Error: Found space inside map.\n"));
		}
	}
	return (0);
}

void	free_all(t_info *info)
{
	if (info->file)
		free_mat(info->file);
	if (info->map)
		free_mat(info->map);
	if (info->tmp)
		free_mat(info->tmp);
	if (info->no)
		free(info->no);
	if (info->so)
		free(info->so);
	if (info->ea)
		free(info->ea);
	if (info->we)
		free(info->we);
}
