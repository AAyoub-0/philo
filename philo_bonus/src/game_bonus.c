/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:19:52 by aboumall          #+#    #+#             */
/*   Updated: 2025/09/12 15:04:55 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sem_clear(sem_t *sem, const char *name)
{
	if (sem)
	{
		sem_close(sem);
		sem_unlink(name);
	}
}

void	free_game(t_game *game)
{
	size_t	i;

	i = 0;
	free(game->philos);
	game->philos = NULL;
	sem_clear(game->print_sem, PRINT_SEM_NAME);
	sem_clear(game->nb_eat_sem, NB_EAT_SEM_NAME);
	sem_clear(game->forks_sem, FORKS_SEM_NAME);
	sem_clear(game->end_sim_sem, END_SIM_SEM_NAME);
	sem_clear(game->philo_dead_sem, PHILO_DEAD_SEM_NAME);
	sem_clear(game->meals_eaten_sem, MEALS_EATEN_SEM_NAME);
	sem_clear(game->last_meal_sem, LAST_MEAL_SEM_NAME);
}

void	*death_check(void *param)
{
	t_philo	*philo;
	t_game	*game;
	size_t	current_time;

	philo = (t_philo *)param;
	game = philo->game;
	while (get_philo_dead(game) == false)
	{
		current_time = ft_get_time();
		if (current_time - get_last_meal(game, philo) >= game->time_die)
		{
			print_state(game, philo->id, dead);
			sem_post(game->end_sim_sem);
			// sem_wait(game->print_sem);
			// free_philo(game);
			return (NULL);
		}
		usleep(10);
	}
	return (NULL);
}

void	*eat_check(void *param)
{
	t_game	*game;
	size_t	meals_eaten;

	game = (t_game *)param;
	meals_eaten = 0;
	while (true)
	{
		sem_wait(game->nb_eat_sem);
		++meals_eaten;
		if (meals_eaten >= game->nb_philo)
		{
			// free_game(game);
			sem_post(game->end_sim_sem);
			return (NULL);
		}
	}
	return (NULL);
}
