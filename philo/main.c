/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:02:09 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/17 17:32:53 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/philosopher.h"

int	main(int ac, char **av)
{
	int		i;
	t_bin	bin;

	if (check_args_validity(ac, av) == 0 || !(ac == 5 || ac == 6))
		return (-1);
	if (ac == 5)
		bin.global_info.n_eat = -1;
	else
		bin.global_info.n_eat = ft_atoi(av[5]);
	if (ft_atoi(av[1]) > 200)
		return (-1);
	if (mall_init(&bin, av) == -1)
		return (-1);
	i = initialize(av, &bin.locks, &bin.global_info);
	if (i == -1)
	{
		free_all(&bin.list_threads, &bin.list_infos, &bin.locks);
		return (-1);
	}
	i = optization(i, av, &bin);
	if (check_if_enough(i, av, &bin) == -1)
		return (-1);
	monitor_n_wait(av, &bin, i);
	free_everything(&bin.list_threads, &bin.list_infos, &bin.locks);
	return (0);
}

int	check_if_enough(int i, char **av, t_bin *bin)
{
	if (i < ft_atoi(av[1]) && i != 0)
	{
		free_opti(i, bin, av);
		return (-1);
	}
	return (0);
}
