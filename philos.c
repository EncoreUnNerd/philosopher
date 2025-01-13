/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:07:56 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/13 12:56:14 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philo_pair(void *data)
{
	t_info *info = (t_info *)data;

	while (is_stoped(info) == 0 && (info->i_eat < info->global_info->n_eat || info->global_info->n_eat == -1))
	{
		if (is_stoped(info) == 0 && pthread_mutex_lock(info->fork_left) == 0)
		{
			print_fork(info);
			while (is_stoped(info) == 0)
			{
				if (is_stoped(info) == 0 && pthread_mutex_lock(info->fork_right) == 0)
				{
					print_fork(info);
					eating(info);
					sleeping(info);
					thinking(info->global_info, *info, 1);
					break;
				}
			}
		}
	}
	return (NULL);
}

void	*philo_impair(void *data)
{
	t_info *info = (t_info *)data;

	thinking(info->global_info, *info, 0);
	while (is_stoped(info) == 0 && (info->i_eat < info->global_info->n_eat || info->global_info->n_eat == -1))
	{
		if (is_stoped(info) == 0 && pthread_mutex_lock(info->fork_right) == 0)
		{
			print_fork(info);
			while (is_stoped(info) == 0)
			{
				if (is_stoped(info) == 0 && pthread_mutex_lock(info->fork_left) == 0)
				{
					print_fork(info);
					eating(info);
					sleeping(info);
					thinking(info->global_info, *info, 1);
					break;
				}
			}
		}
	}
	return (NULL);
}

void	eating(t_info *info)
{
	if (is_stoped(info) == 0)
	{
		print_eating(info);
		my_usleep(info->global_info->time_eat * 1000);
		pthread_mutex_lock(&info->read_l);
		info->last_meal = get_timestamp(0);
		pthread_mutex_unlock(&info->read_l);
	}
	pthread_mutex_unlock(info->fork_left);
	pthread_mutex_unlock(info->fork_right);
}

void	sleeping(t_info *info)
{
	if (is_stoped(info) == 0)
	{
		print_sleeping(info);
		my_usleep(info->global_info->time_sleep * 1000);
		info->i_eat++;
	}
}