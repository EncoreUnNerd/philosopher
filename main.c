/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:02:09 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/13 17:20:54 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

//? Free tout quand ca se fini
//? faire le cas ou le philo est alone
//? mettre a la norme

int main(int ac, char **av)
{
	int				i;
	int				number_of_philo;
	pthread_mutex_t	*locks;
	pthread_t		*list_threads;
	t_info			*list_infos;
	t_global_info	global_info;
	
	if (check_args_validity(ac, av) == 0 || !(ac == 5 || ac == 6))
		exit(-1);
	number_of_philo = ft_atoi(av[1]);
	list_threads = malloc((number_of_philo + 1) * sizeof(pthread_t));
	list_infos = malloc(number_of_philo * sizeof(t_info));
	i = 0;
	create_locks(&locks, number_of_philo);
	create_global_info(&global_info, ft_atoi(av[2]), ft_atoi(av[3]), ft_atoi(av[4]));
	global_info.total_philo = number_of_philo;
	if (ac == 5)
		global_info.n_eat = -1;
	else
		global_info.n_eat = ft_atoi(av[5]);
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
	pthread_create(&list_threads[i], NULL, monitoring, list_infos);
	i = 0;
	while (i < number_of_philo + 1)
	{
		pthread_join(list_threads[i], NULL);
		i++;
	}
	free_everything(&list_threads, &list_infos, &locks);
	return (0);
}

void	free_everything(pthread_t **list_threads, t_info **list_info, pthread_mutex_t **locks)
{
	write(1, "a", 1);
	free(*list_threads);
	write(1, "b", 1);
	// while (i < number_of_philo)
	// {
	// 	pthread_mutex_destroy(&list_info[i]->read_l);
	// 	i++;
	// }
	// write(1, "c", 1);
	free(*list_info);
	write(1, "d", 1);
	free(*locks);
}
