/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:15:53 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/13 16:56:05 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*monitoring(void *infos)
{
	size_t	i;
	int		run;
	t_info	*list_info;

	list_info = (t_info *)infos;
	i = 0;
	run = 1;
	while (run)
	{
		while (i < list_info[0].global_info->total_philo)
		{
			run = check_and_update(&list_info, get_timestamp(0), i);
			if (run == 0)
				break;
			i++;
		}
		i = 0;
	}
	return (0);
}

void	*philo_pair(void *data)
{
	t_info *info = (t_info *)data;

	while (is_stoped(info) == 0 && (info->i_eat < info->global_info->n_eat || info->global_info->n_eat == -1))
	{
		if (is_stoped(info) == 0)
		{
			usleep(100);
			pthread_mutex_lock(info->fork_left);
			print_fork(info);
			while (is_stoped(info) == 0)
			{
				if (is_stoped(info) == 0)
				{
					usleep(100);
					pthread_mutex_lock(info->fork_right);
					print_fork(info);
					eating(info);
					sleeping(info);
					thinking(info, 1);
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

	thinking(info, 0);
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
					thinking(info, 1);
					break;
				}
			}
		}
	}
	return (NULL);
}