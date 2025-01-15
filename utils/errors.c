/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:34:20 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/15 14:49:05 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

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
	free_all(l_t, l_i, locks);
}

void	free_all(pthread_t **l_t, t_info **l_i, pthread_mutex_t **locks)
{
	free(*l_t);
	free(*l_i);
	free(*locks);
	exit(-1);
}

void	destroy_locks(pthread_mutex_t **locks, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		pthread_mutex_destroy(&(*locks)[i]);
		i++;
	}
}

void	destroy_infos(t_info **l_i, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		pthread_mutex_destroy(&(*l_i)[i].read_l);
		i++;
	}
}

void	free_opti(int i, t_bin *bin, char **av)
{
	say_stop(&bin->list_infos[0]);
	pthread_mutex_destroy(&bin->list_infos[0].global_info->read_s);
	pthread_mutex_destroy(&bin->list_infos[0].global_info->print);
	destroy_locks(&bin->locks, ft_atoi(av[1]));
	destroy_infos(&bin->list_infos, i);
	free_all(&bin->list_threads, &bin->list_infos, &bin->locks);
}
