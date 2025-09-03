/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:28:02 by aboumall          #+#    #+#             */
/*   Updated: 2025/09/03 20:18:07 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# include <limits.h>

# define USAGE \
	"Usage: ./philo <number_of_philosophers> <time_to_die>\
 <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
# define ERROR \
	"Error: Invalid arguments. All arguments must be\
 positive integers.\n"

# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[38;5;34m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"

# define PRINT_SEM_NAME "print_sem"
# define NB_EAT_SEM_NAME "nb_eat_sem"
# define DEAD_SEM_NAME "dead_sem"
# define END_SEM_NAME "end_sem"
# define FORKS_SEM_NAME "forks_sem"
# define MEALS_EATEN_SEM_NAME "meals_eaten_sem"
# define LAST_MEAL_SEM_NAME "last_meal_sem"
# define STATE_SEM_NAME "state_sem"

typedef enum e_bool
{
	true = 1,
	false = 0
}					t_bool;

typedef enum e_philo_state
{
	eating,
	sleeping,
	thinking,
	dead,
	none
}					t_philo_state;

typedef struct s_philo
{
	pid_t			pid;
	size_t			id;
	size_t			meals_eaten;
	size_t			last_meal;
	t_philo_state	state;
	struct s_game	*game;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	int				nb_max_eat;
	long			start_time;
	pthread_t		death_thread;
}					t_philo;

typedef struct s_game
{
	size_t			nb_philo;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	int				nb_max_eat;
	long			start_time;
	t_philo			*philos;
	sem_t			*print_sem;
	sem_t			*nb_eat_sem;
	sem_t			*dead_sem;
	sem_t			*forks_sem;
	sem_t			*end_sem;
	sem_t			*meals_eaten_sem;
	sem_t			*last_meal_sem;
	sem_t			*state_sem;
	pthread_t		nb_eat_thread;
}					t_game;

sem_t				*sem_clean_open(t_game *game, const char *name, int value);

void				init_philos(t_game *game);
void				*philo_routine(void *param);

void				*death_check(void *param);
void				*eat_check(void *param);
void				free_game(t_game *game);

void				set_meals_eaten(t_game *game, t_philo *philo, size_t meals);
void				set_last_meal(t_game *game, t_philo *philo, size_t last_meal);

int					get_nb_eat(t_game *game);
size_t				get_meals_eaten(t_game *game, t_philo *philo);
size_t				get_last_meal(t_game *game, t_philo *philo);

long				ft_get_time(void);
long				ft_get_delay(long start_time);
void				ft_usleep(long delay);

void				print_state(t_game *game, size_t id, t_philo_state state);
void				print_fork(t_game *game, t_philo *philo);
size_t				mini_atoi(char *str);
t_bool				ft_isdigit(char c);

#endif