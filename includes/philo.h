/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:28:02 by aboumall          #+#    #+#             */
/*   Updated: 2025/03/04 23:39:25 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_bool
{
	false,
	true,
	null
}						t_bool;

typedef enum e_philo_state
{
	eating,
	sleeping,
	thinking,
	none,
	dead
}						t_philo_state;

typedef struct s_fork
{
	t_bool				is_used;
	pthread_mutex_t		*fork_lock;
	pthread_mutexattr_t	*attr;
}						t_fork;

typedef struct s_philo
{
	unsigned int		id;
	t_philo_state		state;
	t_fork				*fork;
	struct s_philo		*prev;
	struct s_philo		*next;
}						t_philo;

typedef struct s_game
{
	size_t				nb_philo;
	size_t				time_die;
	size_t				time_eat;
	size_t				time_sleep;
	int					nb_max_eat;
	t_philo				*philos;
	pthread_t			*threads;
}						t_game;

typedef struct s_thread
{
	pthread_mutex_t		*id_lock;
	unsigned int	id;
	t_game	*game;
}						t_thread;

void					set_null_philo(t_philo *philo);
void					init_philo(t_game *game, t_philo *philo);
void					init_philos(t_game *game);

void					set_null_game(t_game *game);
void					init_setup(int ac, char **av, t_game *game);
t_game					*init_game(int ac, char **av);

void					start_threads(t_game *game);

size_t					mini_atoi(char *str);
void					print_philo(t_philo *philo);
void					print_game(t_game *game);

#endif