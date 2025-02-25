/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:28:02 by aboumall          #+#    #+#             */
/*   Updated: 2025/02/25 18:33:34 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>

typedef enum e_bool
{
	false,
	true,
	null
}	t_bool;

typedef struct s_fork
{
	t_bool				is_used;
	pthread_mutex_t		*f_restrict;
	pthread_mutexattr_t	*attr;
}	t_fork;

typedef struct s_philo
{
	size_t	id;
	t_fork	*fork;
	struct s_philo	*prev;
	struct s_philo	*next;
}	t_philo;

typedef struct s_game
{
	size_t		nb_philo;
	size_t		time_die;
	size_t		time_eat;
	size_t		time_sleep;
	size_t		nb_max_eat;
	t_philo		*philos;
	pthread_t	*threads;
}	t_game;

#endif