/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:48:50 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/30 14:49:12 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	int			i;
	long long	result;

	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			return (err_parsing(str, 0), exit(1), -1);
		i++;
	}
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			result = (result * 10) + (str[i] - 48);
		else
			return (err_parsing(str, 1), exit(1), -1);
		i++;
	}
	if (result < 0 || result > LONG_MAX)
		return (err_parsing(str, 0), exit(1), -1);
	return ((long)result);
}
