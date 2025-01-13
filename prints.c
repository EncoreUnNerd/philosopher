/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:18:50 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/13 16:25:53 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_thinking(t_info *info)
{
	pthread_mutex_lock(&info->global_info->print);
	if (is_stoped(info) == 0)
		printf("%lu %zu is thinking\n", get_timestamp(info->global_info->start_time), info->number);
	pthread_mutex_unlock(&info->global_info->print);
}

void	print_eating(t_info *info)
{
	pthread_mutex_lock(&info->global_info->print);
	if (is_stoped(info) == 0)
		printf("%lu %zu is eating\n", get_timestamp(info->global_info->start_time), info->number);
	pthread_mutex_unlock(&info->global_info->print);
}

void	print_sleeping(t_info *info)
{
	pthread_mutex_lock(&info->global_info->print);
	if (is_stoped(info) == 0)
		printf("%lu %zu is sleeping\n", get_timestamp(info->global_info->start_time), info->number);
	pthread_mutex_unlock(&info->global_info->print);
}

void	print_fork(t_info *info)
{
	pthread_mutex_lock(&info->global_info->print);
	if (is_stoped(info) == 0)
		printf("%lu %zu has taken a fork\n", get_timestamp(info->global_info->start_time), info->number);
	pthread_mutex_unlock(&info->global_info->print);
}

void	print_dead(t_info *info)
{
	pthread_mutex_lock(&info->global_info->print);
	printf("%zu %zu is dead\n", get_timestamp(info->global_info->start_time), info->number);
	pthread_mutex_unlock(&info->global_info->print);
}