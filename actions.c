/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:17:31 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/13 16:18:01 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	thinking(t_info *info, int e)
{
	if (e == 1)
	{
		if ((info->global_info->total_philo % 2 != 0) && (info->global_info->time_eat > info->global_info->time_sleep))
		{
			print_thinking(info);
			my_usleep(((info->global_info->time_eat * 1.2) - info->global_info->time_sleep) * 1000);
		}
		else if (info->global_info->time_sleep <= info->global_info->time_eat && (info->global_info->total_philo % 2 != 0))
			print_thinking(info);
		else if (info->global_info->time_sleep < info->global_info->time_eat)
			print_thinking(info);
	}
	else
	{
		if ((info->global_info->total_philo % 2 == 0) && (info->global_info->time_eat > info->global_info->time_sleep))
		{
			print_thinking(info);
			my_usleep((info->global_info->time_eat - info->global_info->time_sleep) * 1000);
		}
		if ((info->global_info->total_philo % 2 == 0) && (info->global_info->time_eat <= info->global_info->time_sleep))
		{
			print_thinking(info);
			my_usleep(info->global_info->time_eat * 1000);
		}
		if (info->global_info->total_philo % 2 != 0)
		{
			print_thinking(info);
			if (info->global_info->time_eat > info->global_info->time_sleep)
				my_usleep(((info->global_info->time_eat * 1.2) - info->global_info->time_sleep) * 1000);
			else
				my_usleep((info->global_info->time_eat * 1.2) * 1000);
		}
	}
	return (1);
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