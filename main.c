/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:02:09 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/09 15:15:23 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*check_if_dead(void *infos)
{
	int		i;
	t_info	*list_info;

	list_info = (t_info *)infos;
	i = 0;
	while (1)
	{
		while (i < list_info[0].global_info->total_philo)
		{
			if (get_timestamp(0) - list_info[i].last_meal >= list_info->global_info->time_die)
			{
				printf("\n\nC DEAD !! ->%d || timing -> %zu\n\n", i, get_timestamp(0) - list_info[i].last_meal);
				exit(-1);
			}
			i++;
		}
		i = 0;
	}
}

int main(int ac, char **av)
{
	int				i;
	int				number_of_philo = 100;
	pthread_mutex_t	*locks;
	pthread_t		*list_threads;
	t_info			*list_infos;
	t_global_info	global_info;
	
	if (check_args_validity(ac, av) == 0 || !(ac == 5 || ac == 4))
		exit(-1);
	list_threads = malloc((number_of_philo + 1) * sizeof(pthread_t));
	list_infos = malloc(number_of_philo * sizeof(t_info));
	i = 0;
	create_locks(&locks, number_of_philo);
	create_global_info(&global_info, ft_atoi(av[1]), ft_atoi(av[2]), ft_atoi(av[3]));
	global_info.total_philo = number_of_philo;
	if (ac == 4)
		global_info.n_eat = -1;
	else
		global_info.n_eat = ft_atoi(av[4]);
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
	pthread_create(&list_threads[i], NULL, check_if_dead, list_infos);
	i = 0;
	while (i < number_of_philo + 1)
	{
		pthread_join(list_threads[i], NULL);
		i++;
	}
	return (0);
}
