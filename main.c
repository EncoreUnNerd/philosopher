/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:02:09 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/08 12:49:31 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *philo_pair(void *data)
{
	int		t;
	t_info *info = (t_info *)data;

	t = 1;
	while (info->global_info->stop == 0)
	{
		if (pthread_mutex_lock(info->fork_left) == 0)
		{
			printf("%lu %zu has taken a fork\n", get_timestamp(info->global_info->start_time), info->number);
			while (info->global_info->stop == 0)
			{
				if (pthread_mutex_lock(info->fork_right) == 0)
				{
					printf("%lu %zu has taken a fork\n", get_timestamp(info->global_info->start_time), info->number);
					printf("%lu %zu is eating\n", get_timestamp(info->global_info->start_time), info->number);
					my_usleep(info->global_info->time_eat * 1000);
					printf("%lu %zu is sleeping\n", get_timestamp(info->global_info->start_time), info->number);
					pthread_mutex_unlock(info->fork_left);
					pthread_mutex_unlock(info->fork_right);
					my_usleep(info->global_info->time_sleep * 1000);
					print_thinking(info->global_info, *info, 1);
					break;
				}
			}
		}
	}
	return (NULL);
}

void *philo_impair(void *data)
{
	int		t;
	int		d;
	t_info *info = (t_info *)data;

	t = 1;
	d = 0;
	print_thinking(info->global_info, *info, 0);
	while (info->global_info->stop == 0)
	{
		if (pthread_mutex_lock(info->fork_right) == 0)
		{
			printf("%lu %zu has taken a fork\n", get_timestamp(info->global_info->start_time), info->number);
			while (info->global_info->stop == 0)
			{
				if (pthread_mutex_lock(info->fork_left) == 0)
				{
					printf("%lu %zu has taken a fork\n", get_timestamp(info->global_info->start_time), info->number);
					printf("%lu %zu is eating\n", get_timestamp(info->global_info->start_time), info->number);
					my_usleep(info->global_info->time_eat * 1000);
					printf("%lu %zu is sleeping\n", get_timestamp(info->global_info->start_time), info->number);
					pthread_mutex_unlock(info->fork_left);
					pthread_mutex_unlock(info->fork_right);
					my_usleep(info->global_info->time_sleep * 1000);\
					print_thinking(info->global_info, *info, 1);
					break;
				}
			}
		}
	}
	return (NULL);
}

int main()
{
	int				i;
	int				number_of_philo = 8;
	pthread_mutex_t	*locks;
	pthread_t		*list_threads = malloc(number_of_philo * sizeof(pthread_t));
	t_info			*list_infos = malloc(number_of_philo * sizeof(t_info));
	t_global_info	global_info;
	
	i = 0;
	create_locks(&locks, number_of_philo);
	create_global_info(&global_info, 400, 200, 60);
	global_info.total_philo = number_of_philo;
	while (i < number_of_philo)
	{
		list_infos[i].global_info = &global_info;
		create_infos(list_infos, i, locks, number_of_philo - 1);
		if (i % 2 == 0)
			pthread_create(&list_threads[i], NULL, philo_pair, &list_infos[i]);
		else
			pthread_create(&list_threads[i], NULL, philo_impair, &list_infos[i]);
		i++;
	}
	i = 0;
	while (i < number_of_philo)
	{
		pthread_join(list_threads[i], NULL);
		i++;
	}
	return (0);
}