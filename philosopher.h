/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:18:46 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/14 14:22:57 by mhenin           ###   ########.fr       */
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
	pthread_mutex_t	read_s;
	pthread_mutex_t	print;
}	t_global_info;

typedef struct info
{
	size_t			number;
	size_t			last_meal;
	int				i_eat;
	t_global_info	*global_info;
	pthread_mutex_t	read_l;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
}	t_info;

void	create_locks(pthread_mutex_t **lock_list, size_t number_of_philo);
void	create_infos(t_info	*il, size_t p, pthread_mutex_t *ll, size_t mp);
size_t	get_timestamp(size_t start_time);
int		thinking(t_info *info, int e);
int		my_usleep(size_t usec);
int		create_global_info(t_global_info *g, size_t td, size_t te, size_t ts);
int		ft_atoi(const char *str);
int		check_args_validity(int number, char **value);
void	*philo(void *data);
void	eating(t_info *info);
void	sleeping(t_info *info);
int		is_stoped(t_info *info);
void	print_fork(t_info *info);
void	print_sleeping(t_info *info);
void	print_eating(t_info *info);
void	print_thinking(t_info *info);
void	print_dead(t_info *info);
void	*monitoring(void *infos);
size_t	get_last_meal(t_info *info);
void	say_stop(t_info	*info);
int		check_and_update(t_info **list_info, size_t actual_time, int i);
void	free_everything(pthread_t **l_t, t_info **l_i, pthread_mutex_t **locks);
int		sleepneat(t_info *info);
void	monitor_n_wait(char **av, pthread_t **l_t, t_info **l_i, int i);
int		initialize(char **av, pthread_mutex_t **locks, t_global_info *g_i);
int		check_end_eat(t_info **list_info);

#endif