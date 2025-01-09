/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:18:46 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/09 12:54:23 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct global_info
{
	size_t			time_eat;
	size_t			time_sleep;
	size_t			time_die;
	size_t			start_time;
	size_t			total_philo;
	int				n_eat;
	int				stop;
}	t_global_info;

typedef struct info
{
	size_t			number;
	size_t			last_meal;
	t_global_info	*global_info;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
}	t_info;

void	create_locks(pthread_mutex_t **lock_list, size_t number_of_philo);
void	create_infos(t_info	*il, size_t p, pthread_mutex_t *ll, size_t mp);
size_t	get_timestamp(size_t start_time);
int		print_thinking(t_global_info *t_global_info, t_info info, int e);
int		my_usleep(size_t usec);
int		create_global_info(t_global_info *g, size_t td, size_t te, size_t ts);
int		ft_atoi(const char *str);
int		check_args_validity(int number, char **value);
void 	*philo_pair(void *data);
void 	*philo_impair(void *data);

#endif