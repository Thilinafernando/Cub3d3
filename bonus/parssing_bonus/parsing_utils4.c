/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:36:26 by tkurukul          #+#    #+#             */
/*   Updated: 2025/07/14 18:26:28 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	paths_conditions(t_info *info, int i, int j, char *str)
{
	while (info->file[i][++j] != '\0')
	{
		if ((info->file[i][j] >= 9 && info->file[i][j] <= 13)
			|| info->file[i][j] == 32)
			j++;
		else
			break ;
	}
	if (info->file[i][j] == '\0')
		return (ft_printf(2, "Error: %s not included in the file.\n", str));
	if (ft_strncmp(info->file[i], "F", 1)
		&& ft_strncmp(info->file[i], "C", 1)
		&& save_path(str, info, i, j))
		return (-1);
	else if ((!ft_strncmp(info->file[i], "F", 1)
			|| !ft_strncmp(info->file[i], "C", 1))
		&& rgb_convertion(info, str, i, j))
		return (-1);
	return (0);
}

bool	xmp_extention_check(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while(i >= 0 && str[i] != '.')
		i--;
	str = &str[i + 1];
	if (ft_strcmp(str, "xpm"))
	{
		ft_printf(2, "Error: Incorrect extention for texture\
			files.\n");
		return (false);
	}
	return (true);
}
