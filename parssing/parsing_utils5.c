/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:20:44 by tkurukul          #+#    #+#             */
/*   Updated: 2025/07/28 19:36:54 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	save_path_checks(char *str, char **path, t_info *info)
{
	if (!ft_strcmp(str, "NO") && !info->no)
		info->no = *(path);
	else if (!ft_strcmp(str, "SO") && !info->so)
		info->so = *(path);
	else if (!ft_strcmp(str, "WE") && !info->we)
		info->we = *(path);
	else if (!ft_strcmp(str, "EA") && !info->ea)
		info->ea = *(path);
	else
		return (ft_printf(2, "Error: %s"
				" texture is repeated.\n", str), free(*(path)), -1);
	return (0);
}

int	rgb_next(char **rgb)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while ((*rgb)[++i])
	{
		if ((*rgb)[i] == ',')
			counter++;
	}
	if (counter != 2)
		return (free(*(rgb)), -1);
	return (0);
}
