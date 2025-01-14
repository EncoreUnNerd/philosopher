/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:32:18 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/14 14:49:58 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

size_t	get_last_meal(t_info *info)
{
	size_t	last_eat;	

	usleep(100);
	pthread_mutex_lock(&info->read_l);
	last_eat = info->last_meal;
	pthread_mutex_unlock(&info->read_l);
	return (last_eat);
}

void	say_stop(t_info	*info)
{
	usleep(100);
	pthread_mutex_lock(&info->global_info->read_s);
	info->global_info->stop = 1;
	pthread_mutex_unlock(&info->global_info->read_s);
}

int	check_and_update(t_info **list_info, size_t actual_time, int i)
{
	size_t	last_eat;

	last_eat = get_last_meal(&(*list_info)[i]);
	if ((actual_time - last_eat > (*list_info)[0].global_info->time_die + 5) \
		&& (actual_time >= last_eat) && \
		((*list_info)[i].i_eat < list_info[0]->global_info->n_eat))
	{
		say_stop(&(*list_info)[i]);
		print_dead(&(*list_info)[i]);
		return (0);
	}
	return (1);
}

int	check_end_eat(t_info **list_info)
{
	size_t	i;
	size_t	e;

	i = 0;
	e = 0;
	while (i < (*list_info)[0].global_info->total_philo)
	{
		if ((*list_info)[i].i_eat == list_info[0]->global_info->n_eat)
			e++;
		i++;
	}
	if (e == (*list_info)[0].global_info->total_philo - 1)
		return (1);
	return (0);
}
