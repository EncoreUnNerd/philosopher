/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:07:56 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/09 14:57:11 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philo_pair(void *data)
{
	int		t;
	t_info *info = (t_info *)data;

	t = 0;
	while (info->global_info->stop == 0 && (t < info->global_info->n_eat || info->global_info->n_eat == -1))
	{
		if (pthread_mutex_lock(info->fork_left) == 0)
		{
			printf("%lu %zu has taken a fork\n", get_timestamp(info->global_info->start_time), info->number);
			while (info->global_info->stop == 0)
			{
				if (pthread_mutex_lock(info->fork_right) == 0)
				{
					printf("%lu %zu has taken a fork\n", get_timestamp(info->global_info->start_time), info->number);
					info->last_meal = get_timestamp(0);
					printf("%lu %zu is eating\n", get_timestamp(info->global_info->start_time), info->number);
					my_usleep(info->global_info->time_eat * 1000);
					printf("%lu %zu is sleeping\n", get_timestamp(info->global_info->start_time), info->number);
					info->last_meal = get_timestamp(0);
					t++;
					pthread_mutex_unlock(info->fork_left);
					pthread_mutex_unlock(info->fork_right);
					my_usleep(info->global_info->time_sleep * 1000);
					print_thinking(info->global_info, *info, 1);
					break;
				}
			}
		}
	}
	return (NULL);
}

void	*philo_impair(void *data)
{
	int		t;
	t_info *info = (t_info *)data;

	t = 0;
	print_thinking(info->global_info, *info, 0);
	while (info->global_info->stop == 0 && (t < info->global_info->n_eat || info->global_info->n_eat == -1))
	{
		if (pthread_mutex_lock(info->fork_right) == 0)
		{
			printf("%lu %zu has taken a fork\n", get_timestamp(info->global_info->start_time), info->number);
			while (info->global_info->stop == 0)
			{
				if (pthread_mutex_lock(info->fork_left) == 0)
				{
					printf("%lu %zu has taken a fork\n", get_timestamp(info->global_info->start_time), info->number);
					info->last_meal = get_timestamp(0);
					printf("%lu %zu is eating\n", get_timestamp(info->global_info->start_time), info->number);
					my_usleep(info->global_info->time_eat * 1000);
					printf("%lu %zu is sleeping\n", get_timestamp(info->global_info->start_time), info->number);
					info->last_meal = get_timestamp(0);
					t++;
					pthread_mutex_unlock(info->fork_left);
					pthread_mutex_unlock(info->fork_right);
					my_usleep(info->global_info->time_sleep * 1000);
					print_thinking(info->global_info, *info, 1);
					break;
				}
			}
		}
	}
	return (NULL);
}
