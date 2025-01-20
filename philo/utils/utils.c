/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenin <mhenin@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:44:45 by mhenin            #+#    #+#             */
/*   Updated: 2025/01/20 16:01:03 by mhenin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

size_t	get_timestamp(size_t start_time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - start_time);
}

int	my_usleep(size_t usec)
{
	size_t	start;

	start = get_timestamp(0);
	usleep((usec * 90) / 100);
	while ((get_timestamp(0) - start) < (usec / 1000))
		usleep(1);
	return (1);
}

int	is_stoped(t_info *info)
{
	int	res;

	pthread_mutex_lock(&info->global_info->read_s);
	res = info->global_info->stop;
	pthread_mutex_unlock(&info->global_info->read_s);
	return (res);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				signe;
	unsigned long	result;

	i = 0;
	signe = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return ((int)(signe * result));
}
