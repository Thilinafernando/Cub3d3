/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 03:01:07 by tkurukul          #+#    #+#             */
/*   Updated: 2025/07/03 19:42:54 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_lines(char *map)
{
	int		fd;
	char	*tmp;
	int		i;

	i = 0;
	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (ft_printf(2, "Error: Open failed.\n"));
	tmp = get_next_line(fd);
	while (tmp)
	{
		i++;
		free (tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
	return (i);
}

bool	map_only(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2)
		|| !ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "EA", 2)
		|| !ft_strncmp(str, "F", 1) || !ft_strncmp(str, "C", 1)
		|| str[0] == '\n' || !str)
		return (false);
	while (str[i] != '\0')
	{
		if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
		else if (str[i] == '1')
		{
			i++;
			flag = 1;
		}
		else
			i++;
	}
	if (!flag)
		return (false);
	return (true);
}

char	*ft_mapdup(const char *s, t_info *info)
{
	int		i;
	char	*str;

	i = -1;
	str = malloc((info->max + 3) * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = 'X';
	while (++i < (info->max + 2))
	{
		if (s[i + 1] == '\0')
		{
			str[i + 1] = 'X';
			while (++i < (info->max))
				str[i + 1] = 'X';
			str[i + 1] = '\n';
			str[i + 2] = '\0';
			break ;
		}
		else if ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
			str[i + 1] = 'L';
		else
			str[i + 1] = s[i];
	}
	return (str);
}

char	*x_fill(t_info *info)
{
	int		i;
	int		len;
	char	*str;

	i = -1;
	info->max = 0;
	len = 0;
	while (info->map[++i])
	{
		len = ft_strlen(info->map[i]);
		if (len > info->max)
			info->max = len + 1;
	}
	str = malloc((info->max + 3) * sizeof(char));
	if (!str)
		return (ft_printf(2, "Error: Malloc failed.\n"), NULL);
	i = -1;
	while (++i < (info->max + 1))
		str[i] = 'X';
	str[i] = '\n';
	str[i + 1] = '\0';
	return (str);
}

int	fill_tmp(t_info *info)
{
	int	i;

	i = -1;
	info->tmp = malloc((info->count + 3) * sizeof (char *));
	if (!info->tmp)
		return (ft_printf(2, "Error: Malloc failed.\n"));
	info->tmp[0] = x_fill(info);
	while (info->map[++i])
	{
		info->tmp[i + 1] = ft_mapdup(info->map[i], info);
		if (!info->map[i + 1])
			info->tmp[i + 2] = x_fill(info);
	}
	info->tmp[i + 2] = NULL;
	return (0);
}
