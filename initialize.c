/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:19:47 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/13 16:20:19 by mhenin           ###   ########.fr       */
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