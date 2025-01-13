/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:41:51 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/13 11:48:28 by mhenin           ###   ########.fr       */
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

int	ft_atoi(const char *str)
{
	int				i;
	int				signe;
	unsigned long	result;

	i = 0;
	signe = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return ((int)(signe * result));
}

int	is_stoped(t_info *info)
{
	int res;

	pthread_mutex_lock(&info->global_info->read_s);
	res = info->global_info->stop;
	pthread_mutex_unlock(&info->global_info->read_s);
	return (res);
}

void print_thinking(t_info *info)
{
	pthread_mutex_lock(&info->global_info->print);
	if (is_stoped(info) == 0)
		printf("%lu %zu is thinking\n", get_timestamp(info->global_info->start_time), info->number);
	pthread_mutex_unlock(&info->global_info->print);
}

void print_eating(t_info *info)
{
	pthread_mutex_lock(&info->global_info->print);
	if (is_stoped(info) == 0)
		printf("%lu %zu is eating\n", get_timestamp(info->global_info->start_time), info->number);
	pthread_mutex_unlock(&info->global_info->print);
}

void print_sleeping(t_info *info)
{
	pthread_mutex_lock(&info->global_info->print);
	if (is_stoped(info) == 0)
		printf("%lu %zu is sleeping\n", get_timestamp(info->global_info->start_time), info->number);
	pthread_mutex_unlock(&info->global_info->print);
}

void print_fork(t_info *info)
{
	pthread_mutex_lock(&info->global_info->print);
	if (is_stoped(info) == 0)
		printf("%lu %zu has taken a fork\n", get_timestamp(info->global_info->start_time), info->number);
	pthread_mutex_unlock(&info->global_info->print);
}