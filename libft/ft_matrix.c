/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:56:49 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/30 15:18:15 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**matrix_tmp(char **matrix)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	while (matrix[i])
		i++;
	new = malloc((i + 1) * sizeof(char *));
	if (!new)
		return ;
	while (matrix[j])
	{
		new[j] = ft_strdup(matrix[j]);
		j++;
	}
	new[j] = NULL;
	return ;
}

int	exisit(char **matrix, char *arg, char character_at_end)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	while (matrix[i])
	{
		if (ft_strncmp(matrix[i], arg, len) == 0
			&& (matrix[i][len] == character_at_end || matrix[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

void	process_join(char **arg1, char **arg2, char ***new)
{
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (arg1[j])
	{
		(*new)[i] = ft_strdup(arg1[j]);
		i++;
		j++;
	}
	j = 0;
	while (arg2[j])
	{
		if (append((*new), arg2[j]) != 1)
		{
			(*new)[i] = ft_strdup(arg2[j]);
			i++;
		}
		j++;
	}
}

char	**matrix_join(char **arg1, char **args, int size)
{
	int		x;
	char	**new;

	x = 0;
	new = malloc((size + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	while (x <= size)
	{
		new[x] = NULL;
		x++;
	}
	process_join(arg1, args, &new);
	free_mat(arg1);
	new[size] = NULL;
	return (new);
}

void	free_mat(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i])
		i++;
	i--;
	while (i >= 0 && matrix[i])
	{
		free(matrix[i]);
		i--;
	}
	free(matrix);
	matrix = NULL;
	return ;
}
