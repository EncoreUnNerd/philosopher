/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:15:53 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/16 16:38:47 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/philosopher.h"

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
			if (check_end_eat(&list_info) == 1)
				run = 0;
			if (run == 0)
				break ;
			i++;
		}
		i = 0;
	}
	return (0);
}

void	*philo(void *data)
{
	t_info	*info;

	info = (t_info *)data;
	solo(info);
	if (info->number % 2 != 0)
		thinking(info, 0);
	while (is_stoped(info) == 0 && (info->i_eat < info->global_info->n_eat || \
		info->global_info->n_eat == -1) && info->fork_left != info->fork_right)
	{
		if (is_stoped(info) == 0)
		{
			usleep(VALOPTI);
			if (info->number % 2 != 0)
				pthread_mutex_lock(info->fork_left);
			else
				pthread_mutex_lock(info->fork_right);
			print_fork(info);
			while (is_stoped(info) == 0)
			{
				if (sleepneat(info) == 1)
					break ;
			}
		}
	}
	return (NULL);
}

void	solo(t_info *info)
{
	pthread_mutex_lock(&info->global_info->starting);
	pthread_mutex_unlock(&info->global_info->starting);
	if (info->fork_left == info->fork_right)
	{
		print_fork(info);
		my_usleep(info->global_info->time_die * 1000);
	}
}
