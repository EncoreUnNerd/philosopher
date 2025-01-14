/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:02:09 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/13 19:07:19 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

//? gerer le fait qu'ils peuvent avoirs fini de manger
//? faire le cas ou le philo est alone
//? mettre a la norme

int	main(int ac, char **av)
{
	int				i;
	pthread_mutex_t	*locks;
	pthread_t		*list_threads;
	t_info			*list_infos;
	t_global_info	global_info;

	if (check_args_validity(ac, av) == 0 || !(ac == 5 || ac == 6))
		exit(-1);
	if (ac == 5)
		global_info.n_eat = -1;
	else
		global_info.n_eat = ft_atoi(av[5]);
	list_threads = malloc((ft_atoi(av[1]) + 1) * sizeof(pthread_t));
	list_infos = malloc(ft_atoi(av[1]) * sizeof(t_info));
	i = initialize(av, &locks, &global_info);
	while (i < ft_atoi(av[1]))
	{
		list_infos[i].global_info = &global_info;
		create_infos(list_infos, i, locks, ft_atoi(av[1]) - 1);
		pthread_create(&list_threads[i], NULL, philo, &list_infos[i]);
		i++;
	}
	monitor_n_wait(av, &list_threads, &list_infos, i);
	free_everything(&list_threads, &list_infos, &locks);
	return (0);
}
