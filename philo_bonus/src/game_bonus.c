/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:19:52 by aboumall          #+#    #+#             */
/*   Updated: 2025/08/27 19:45:27 by aboumall         ###   ########.fr       */
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
	while (i < game->nb_philo)
	{
		if (game->philos[i].pid > 0)
			kill(game->philos[i].pid, SIGKILL);
		sem_clear(game->philos[i].meals_eaten_sem, MEALS_EATEN_SEM_NAME);
		sem_clear(game->philos[i].last_meal_sem, LAST_MEAL_SEM_NAME);
		sem_clear(game->philos[i].state_sem, STATE_SEM_NAME);
		i++;
	}
	free(game->philos);
	game->philos = NULL;
	sem_clear(game->print_sem, PRINT_SEM_NAME);
	sem_clear(game->nb_eat_sem, NB_EAT_SEM_NAME);
	sem_clear(game->dead_sem, DEAD_SEM_NAME);
	sem_clear(game->forks_sem, FORKS_SEM_NAME);
}

void	*death_check(void *param)
{
	t_philo	*philo;
	t_game	*game;
	size_t	current_time;

	philo = (t_philo *)param;
	game = philo->game;
	while (true)
	{
		current_time = ft_get_time();
		if (current_time - get_last_meal(philo) >= game->time_die)
		{
			print_state(game, philo->id, dead);
			sem_wait(game->print_sem);
			exit(EXIT_SUCCESS);
		}
		usleep(100);
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
			exit(EXIT_SUCCESS);
		}
	}
	return (NULL);
}
