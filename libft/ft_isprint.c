/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:28:14 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/30 20:14:59 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
int     main(void)
{
        printf("%d", ft_isprint('\n'));
        return (0);
}*/

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
