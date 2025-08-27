/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:17:51 by aboumall          #+#    #+#             */
/*   Updated: 2025/08/27 16:56:43 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_game *game, t_philo *philo, t_bool done)
{
	sem_wait(game->forks_sem);
	if (!done)
		print_fork(game, philo);
	sem_wait(game->forks_sem);
	if (!done)
		print_fork(game, philo);
	if (!done)
		print_state(game, philo->id, eating);
	set_last_meal(philo, ft_get_time());
	set_meals_eaten(philo, get_meals_eaten(philo) + 1);
	ft_usleep(game->time_eat);
	sem_post(game->forks_sem);
	sem_post(game->forks_sem);
}

void	philo_think(t_game *game, t_philo *philo, t_bool done)
{
	if (done)
		return ;
	print_state(game, philo->id, thinking);
}

void	philo_sleep(t_game *game, t_philo *philo, t_bool done)
{
	if (!done)
		print_state(game, philo->id, sleeping);
	ft_usleep(game->time_sleep);
}

void	*philo_routine(void *param)
{
	t_philo	*philo;
	t_bool	done;

	philo = (t_philo *)param;
	philo->last_meal = philo->game->start_time;
	while (ft_get_time() < philo->game->start_time)
		usleep(100);
	pthread_create(&philo->death_thread, NULL, death_check, philo);
	pthread_detach(philo->death_thread);
	done = false;
	if (philo->id % 2 == 0)
		ft_usleep(philo->game->time_eat * 0.2);
	while (true)
	{
		philo_eat(philo->game, philo, done);
		if (!done && philo->game->nb_max_eat != -1
			&& (int)get_meals_eaten(philo) == philo->game->nb_max_eat)
		{
			done = true;
			sem_post(philo->game->nb_eat_sem);
		}
		philo_think(philo->game, philo, done);
		philo_sleep(philo->game, philo, done);
	}
	exit(EXIT_SUCCESS);
}

void	init_philos(t_game *game)
{
	size_t	i;

	i = -1;
	while (++i < game->nb_philo)
	{
		game->philos[i].game = game;
		game->philos[i].id = i + 1;
		game->philos[i].meals_eaten = 0;
		game->philos[i].meals_eaten_sem = sem_clean_open(game,
				MEALS_EATEN_SEM_NAME, 1);
		game->philos[i].last_meal_sem = sem_clean_open(game, LAST_MEAL_SEM_NAME,
				1);
		game->philos[i].state_sem = sem_clean_open(game, STATE_SEM_NAME, 1);
	}
}
