/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:41:51 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/13 16:21:45 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '\0' || str[i] == '-')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	verif_atoi(const char *str)
{
	int		i;
	long	result;

	if (!is_valid_number(str))
		return (0);
	i = 0;
	result = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	check_args_validity(int number, char **value)
{
	int	i;

	i = 1;
	while (i <= number - 1)
	{
		if (verif_atoi(value[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
