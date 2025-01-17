/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:32:18 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/17 17:11:39 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

size_t	get_last_meal(t_info *info)
{
	size_t	last_eat;	

	usleep(VALOPTI);
	pthread_mutex_lock(&info->read_l);
	last_eat = info->last_meal;
	pthread_mutex_unlock(&info->read_l);
	return (last_eat);
}

void	say_stop(t_info	*info)
{
	usleep(VALOPTI);
	pthread_mutex_lock(&info->global_info->read_s);
	info->global_info->stop = 1;
	pthread_mutex_unlock(&info->global_info->read_s);
}

int	check_and_update(t_info **list_info, size_t actual_time, int i)
{
	size_t	last_eat;

	last_eat = get_last_meal(&(*list_info)[i]);
	if ((actual_time - last_eat > (*list_info)[0].global_info->time_die) \
		&& (actual_time >= last_eat) && \
		(((*list_info)[i].i_eat < list_info[0]->global_info->n_eat) || \
			list_info[0]->global_info->n_eat == -1))
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
	if ((*list_info)[0].global_info->total_philo != 1)
	{
		while (i < (*list_info)[0].global_info->total_philo)
		{
			pthread_mutex_lock(&(*list_info)[i].read_nm);
			if ((*list_info)[i].i_eat == list_info[0]->global_info->n_eat)
				e++;
			pthread_mutex_unlock(&(*list_info)[i].read_nm);
			i++;
		}
		if (e == (*list_info)[0].global_info->total_philo)
			return (1);
	}
	return (0);
}
