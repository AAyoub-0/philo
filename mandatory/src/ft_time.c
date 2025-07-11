/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:21:08 by aboumall          #+#    #+#             */
/*   Updated: 2025/07/05 01:39:23 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_get_time(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

long	ft_get_delay(long start_time)
{
	return (ft_get_time() - start_time);
}

void	ft_usleep(long delay)
{
	long	start_time;

	start_time = ft_get_time();
	while (ft_get_delay(start_time) < delay)
		usleep(100); 
}
