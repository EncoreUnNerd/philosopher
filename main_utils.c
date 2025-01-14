/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:23:53 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/14 14:48:27 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	monitor_n_wait(char **av, pthread_t **l_t, t_info **l_i, int i)
{
	write(1, "a", 1);
	pthread_create(&(*l_t)[i], NULL, monitoring, *l_i);
	write(1, "b", 1);
	i = 0;
	write(1, "c", 1);
	while (i < ft_atoi(av[1]) + 1)
	{
		pthread_join((*l_t)[i], NULL);
		i++;
	}
}

int	initialize(char **av, pthread_mutex_t **locks, t_global_info *g_i)
{
	create_locks(locks, ft_atoi(av[1]));
	create_global_info(g_i, ft_atoi(av[2]), \
						ft_atoi(av[3]), ft_atoi(av[4]));
	g_i->total_philo = ft_atoi(av[1]);
	return (0);
}

void	free_everything(pthread_t **l_t, t_info **l_i, pthread_mutex_t **locks)
{
	size_t	i;
	size_t	number_philo;

	i = 0;
	number_philo = l_i[0]->global_info->total_philo;
	pthread_mutex_destroy(&(*l_i)[0].global_info->read_s);
	pthread_mutex_destroy(&(*l_i)[0].global_info->print);
	while (i < number_philo)
	{
		pthread_mutex_destroy(&(*l_i)[i].read_l);
		i++;
	}
	i = 0;
	while (i < number_philo)
	{
		pthread_mutex_destroy(&(*locks)[i]);
		i++;
	}
	free(*l_t);
	free(*l_i);
	free(*locks);
}
