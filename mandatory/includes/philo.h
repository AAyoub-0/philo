/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:28:02 by aboumall          #+#    #+#             */
/*   Updated: 2025/07/05 01:39:17 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define USAGE "Usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
# define ERROR "Error: Invalid arguments. All arguments must be positive integers.\n"

# define RESET       "\033[0m"
# define BLACK       "\033[30m"
# define RED         "\033[31m"
# define GREEN       "\033[38;5;34m"
# define YELLOW      "\033[33m"
# define BLUE        "\033[34m"
# define MAGENTA     "\033[35m"
# define CYAN        "\033[36m"
# define WHITE       "\033[37m"

# define BOLD        "\033[1m"
# define UNDERLINE   "\033[4m"


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
	t_fork				fork;
	struct s_philo		*prev;
	pthread_mutex_t		meals_eaten_lock;
	pthread_mutex_t		last_meal_lock;
	struct s_game		*game;
}						t_philo;

typedef struct s_game
{
	t_bool				start;
	size_t				nb_philo;
	size_t				time_die;
	size_t				time_eat;
	size_t				time_sleep;
	int					nb_max_eat;
	int					nb_eat;
	t_philo				*philos;
	t_philo				*dead;
	t_bool				dead_printed;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		nb_eat_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		start_lock;
	pthread_t			death_thread;
}						t_game;

void	init_philos(t_game *game);

void	*death_check(void *param);
void	free_game(t_game *game);

void	set_state(t_philo *philo, t_philo_state state);
void	set_meals_eaten(t_philo *philo, size_t meals);
void	set_last_meal(t_philo *philo, size_t last_meal);
void	set_nb_eat(t_game *game, int nb_eat);
void	set_dead(t_game *game, t_philo *philo);
void	set_start(t_game *game, t_bool start);
void	set_start_time(t_game *game, size_t start_time);

int		get_nb_eat(t_game *game);
size_t	get_meals_eaten(t_philo *philo);
size_t	get_last_meal(t_philo *philo);
t_philo	*get_dead(t_game *game);
t_bool	get_start(t_game *game);
size_t	get_start_time(t_game *game);

long	ft_get_time(void);
long	ft_get_delay(long start_time);
void	ft_usleep(long delay);

void	print_state(t_game *game, t_philo *philo, t_philo_state state);
void	print_fork(t_game *game, t_philo *philo);
t_bool	first_fork(t_game *game, t_philo *philo);
size_t	mini_atoi(char *str);
t_bool	is_digit(char c);

#endif