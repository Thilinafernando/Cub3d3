/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 03:04:40 by tkurukul          #+#    #+#             */
/*   Updated: 2025/07/24 21:41:59 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_characters(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (info->map[++i])
	{
		j = -1;
		while (info->map[i][++j])
		{
			if (info->map[i][j] != '\n' && info->map[i][j] != '0'
				&& info->map[i][j] != '1' && info->map[i][j] != 'D' && info->map[i][j] != 'W'
				&& info->map[i][j] != 'N' && info->map[i][j] != 'E'
				&& info->map[i][j] != 'S' && ft_isspace(info->map[i][j]) == 0)
				return (ft_printf(2, "Error: '%c' is not a"
					" valid character for the map.\n", info->map[i][j]));
		}
	}
	return (0);
}

char	*ft_mydup(const char *s)
{
	int		i;
	int		a;
	char	*str;

	i = 0;
	a = 0;
	while (s[a] != '\0' && (!((s[a] >= 9 && s[a] <= 13) || s[a] == 32)))
		a++;
	str = (char *)malloc((a + 1) * (sizeof(char)));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0' && (!((s[i] >= 9 && s[i] <= 13) || s[i] == 32)))
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (&str[0]);
}

void	init_struct(t_info *info)
{
	info->count = 0;
	info->no = NULL;
	info->so = NULL;
	info->ea = NULL;
	info->we = NULL;
	info->file = NULL;
	info->map = NULL;
	info->tmp = NULL;
	info->max = 0;
	info->player_x = -1;
	info->player_y = -1;
	info->flood_flag = 0;
	info->rgb_c = -42;
	info->rgb_f = -42;
}

int	rgb_convertion(t_info *info, char *str, int i, int j)
{
	char	*rgb;
	char	**tmp;
	int		red;
	int		green;
	int		blue;

	rgb = ft_mydup(info->file[i] + (j));
	if (!rgb)
		return (ft_printf(2, "Error: Malloc failed.\n"));
	tmp = ft_split(rgb, ',');
	if (!tmp || !tmp[0] || !tmp[1] || !tmp[2])
		return (ft_printf(2, "Error: Wrong entries for rgb.\n"));
	free(rgb);
	red = ft_atoi(tmp[0]);
	green = ft_atoi(tmp[1]);
	blue = ft_atoi(tmp[2]);
	free_mat(tmp);
	if (red < 0 || red > 255 || green < 0 || green > 255
		|| blue < 0 || blue > 255)
		return (ft_printf(2, "Error: Invalid RGB values.\n"));
	if (!ft_strncmp(str, "F", 1))
		info->rgb_f = (red << 16) | (green << 8) | blue;
	if (!ft_strncmp(str, "C", 1))
		info->rgb_c = (red << 16) | (green << 8) | blue;
	return (0);
}

int	save_path(char *str, t_info *info, int i, int j)
{
	char	*path;
	int		fd;

	if (!str)
		return (ft_printf(2, "Error: ft_strlcpy failed me.\n"));
	path = ft_mydup(info->file[i] + (j - 1));
	if (!xmp_extention_check(path))
		return (free(path), -1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_printf(2, "Error: Invalid %s"
			" texture. PATH: %s\n", str, path));
	close(fd);
	if (!ft_strcmp(str, "NO"))
		info->no = path;
	if (!ft_strcmp(str, "SO"))
		info->so = path;
	if (!ft_strcmp(str, "WE"))
		info->we = path;
	if (!ft_strcmp(str, "EA"))
		info->ea = path;
	return (0);
}
