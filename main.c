/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:02:09 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/15 14:54:23 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/philosopher.h"

//? etre sur que les verifs marche bb love <3

int	main(int ac, char **av)
{
	int		i;
	t_bin	bin;

	if (check_args_validity(ac, av) == 0 || !(ac == 5 || ac == 6))
		exit(-1);
	if (ac == 5)
		bin.global_info.n_eat = -1;
	else
		bin.global_info.n_eat = ft_atoi(av[5]);
	mall_init(&bin, av);
	i = initialize(av, &bin.locks, &bin.global_info);
	if (i == -1)
		free_all(&bin.list_threads, &bin.list_infos, &bin.locks);
	i = optization(i, av, &bin);
	if (i < ft_atoi(av[1]) && i != 0)
		free_opti(i, &bin, av);
	monitor_n_wait(av, &bin, i);
	free_everything(&bin.list_threads, &bin.list_infos, &bin.locks);
	return (0);
}
