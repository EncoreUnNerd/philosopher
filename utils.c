/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:44:45 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/13 12:55:22 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	create_locks(pthread_mutex_t **lock_list, size_t number_of_philo)
{
	size_t	i;

	i = 0;
	*lock_list = malloc(sizeof(pthread_mutex_t) * number_of_philo);
	while (i < number_of_philo)
	{
		pthread_mutex_init(&(*lock_list)[i], NULL);
		i++;
	}
}

void	create_infos(t_info	*il, size_t p, pthread_mutex_t *ll, size_t mp)
{
	il[p].number = p;
	il[p].i_eat = 0;
	pthread_mutex_init(&il[p].read_l, NULL);
	il[p].last_meal = il[p].global_info->start_time;
	if (p != 0 && p != mp)
	{
		il[p].fork_left = &ll[p - 1];
		il[p].fork_right = &ll[p];
	}
	else
	{
		if (p == 0)
		{
			il[p].fork_left = &ll[mp];
			il[p].fork_right = &ll[p];
		}
		else if (p == mp)
		{
			il[p].fork_left = &ll[p - 1];
			il[p].fork_right = &ll[p];
		}
	}
}

size_t	get_timestamp(size_t start_time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - start_time);
}

int	thinking(t_global_info *global_info, t_info info, int e)
{
	if (e == 1)
	{
		if ((global_info->total_philo % 2 != 0) && (global_info->time_eat > global_info->time_sleep))
		{
			print_thinking(&info);
			my_usleep(((global_info->time_eat * 1.2) - global_info->time_sleep) * 1000);
		}
		else if (global_info->time_sleep <= global_info->time_eat && (global_info->total_philo % 2 != 0))
			print_thinking(&info);
		else if (global_info->time_sleep < global_info->time_eat)
			print_thinking(&info);
	}
	else
	{
		if ((global_info->total_philo % 2 == 0) && (global_info->time_eat > global_info->time_sleep))
		{
			print_thinking(&info);
			my_usleep((global_info->time_eat - global_info->time_sleep) * 1000);
		}
		if ((global_info->total_philo % 2 == 0) && (global_info->time_eat <= global_info->time_sleep))
		{
			print_thinking(&info);
			my_usleep(global_info->time_eat * 1000);
		}
		if (global_info->total_philo % 2 != 0)
		{
			print_thinking(&info);
			if (global_info->time_eat > global_info->time_sleep)
				my_usleep(((global_info->time_eat * 1.2) - global_info->time_sleep) * 1000);
			else
				my_usleep((global_info->time_eat * 1.2) * 1000);
		}
	}
	return (1);
}

int	my_usleep(size_t usec)
{
	size_t	start;

	start = get_timestamp(0);
	usleep((usec * 90) / 100);
	while ((get_timestamp(0) - start) < (usec / 1000))
		usleep(1);
	return (1);
}

int	create_global_info(t_global_info *g, size_t td, size_t te, size_t ts)
{
	g->time_eat = te;
	g->time_sleep = ts;
	g->time_die = td;
	pthread_mutex_init(&g->read_s, NULL);
	pthread_mutex_init(&g->print, NULL);
	g->start_time = get_timestamp(0);
	g->stop = 0;
	return (1);
}
