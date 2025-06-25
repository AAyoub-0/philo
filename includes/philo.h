/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:28:02 by aboumall          #+#    #+#             */
/*   Updated: 2025/06/25 19:10:12 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef enum e_bool
{
	true = 1,
	false = 0
}						t_bool;

typedef enum e_philo_state
{
	eating,
	sleeping,
	thinking,
	dead,
	none
}						t_philo_state;

typedef struct s_fork
{
	t_bool				used;
	pthread_mutex_t		fork_lock;
}						t_fork;

typedef struct s_philo
{
	pthread_t			thread;
	size_t				id;
	size_t				meals_eaten;
	size_t				last_meal;
	t_philo_state		state;
	t_fork				fork;
	struct s_philo		*prev;
	pthread_mutex_t		meals_eaten_lock;
	pthread_mutex_t		last_meal_lock;
	pthread_mutex_t		state_lock;
	struct s_game		*game;
}						t_philo;

typedef struct s_game
{
	size_t				nb_philo;
	size_t				time_die;
	size_t				time_eat;
	size_t				time_sleep;
	int					nb_max_eat;
	t_philo				*philos;
	pthread_mutex_t		print_lock;
	pthread_t			death_thread;
	t_philo				*dead;
}						t_game;

void	init_philos(t_game *game);

void	free_game(t_game *game);
void	set_state(t_philo *philo, t_philo_state state);
void	set_meals_eaten(t_philo *philo, size_t meals);
void	set_last_meal(t_philo *philo, size_t last_meal);

long	ft_get_time(void);
long	ft_get_delay(long start_time);
void	ft_usleep(long delay);

void	print_state(t_game *game, t_philo *philo);
void	print_fork(t_game *game, t_philo *philo);

#endif