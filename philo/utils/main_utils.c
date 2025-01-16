/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:23:53 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/16 16:20:10 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

void	monitor_n_wait(char **av, t_bin *bin, int i)
{
	pthread_create(&bin->list_threads[i], NULL, monitoring, bin->list_infos);
	i = 0;
	while (i < ft_atoi(av[1]) + 1)
	{
		if (pthread_join(bin->list_threads[i], NULL) != 0)
		{
			say_stop(&bin->list_infos[0]);
			free_everything(&bin->list_threads, &bin->list_infos, &bin->locks);
		}
		i++;
	}
}

int	initialize(char **av, pthread_mutex_t **locks, t_global_info *g_i)
{
	int	result;

	result = create_locks(locks, ft_atoi(av[1]));
	if (result != -1)
	{
		destroy_locks(locks, result);
		return (-1);
	}
	result = create_global_info(g_i, ft_atoi(av[2]), \
						ft_atoi(av[3]), ft_atoi(av[4]));
	if (result != -1)
	{
		destroy_locks(locks, ft_atoi(av[1]));
		return (-1);
	}
	g_i->total_philo = ft_atoi(av[1]);
	return (0);
}

void	mall_init(t_bin *bin, char **av)
{
	bin->locks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!bin->locks)
	{
		printf("Error malloc\n");
		exit(-1);
	}
	bin->list_threads = malloc((ft_atoi(av[1]) + 1) * sizeof(pthread_t));
	if (!bin->list_threads)
	{
		printf("Error malloc\n");
		free(bin->locks);
		exit(-1);
	}
	bin->list_infos = malloc(ft_atoi(av[1]) * sizeof(t_info));
	if (!bin->list_infos)
	{
		printf("Error malloc\n");
		free(bin->locks);
		free(bin->list_threads);
		exit(-1);
	}
}

int	optization(int i, char **av, t_bin *bin)
{
	pthread_mutex_lock(&bin->global_info.starting);
	while (i < ft_atoi(av[1]))
	{
		bin->list_infos[i].global_info = &bin->global_info;
		if (create_infos(bin->list_infos, i, bin->locks, \
			ft_atoi(av[1]) - 1) == -1)
			break ;
		pthread_create(&bin->list_threads[i], NULL, philo, &bin->list_infos[i]);
		i++;
	}
	pthread_mutex_unlock(&bin->global_info.starting);
	return (i);
}
