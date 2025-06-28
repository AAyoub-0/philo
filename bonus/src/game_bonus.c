/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:19:52 by aboumall          #+#    #+#             */
/*   Updated: 2025/06/29 01:47:30 by aboumall         ###   ########.fr       */
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
	sem_clear(game->start_sem, START_SEM_NAME);
	sem_clear(game->forks_sem, FORKS_SEM_NAME);
	game->dead = NULL;
}

void	set_dead(t_game *game, t_philo *philo)
{
	sem_wait(game->dead_sem);
	game->dead = philo;
	sem_post(game->dead_sem);
}

t_philo	*get_dead(t_game *game)
{
	t_philo *dead;

	sem_wait(game->dead_sem);
	dead = game->dead;
	sem_post(game->dead_sem);
	return (dead);
}

void	*death_check(void *param)
{
	t_game	*game;
	size_t	current_time;
	size_t	i;

	game = (t_game *)param;
	while (!get_start(game))
		ft_usleep(100);
	while (true)
	{
		i = 0;
		while (i < game->nb_philo)
		{
			current_time = ft_get_time();
			if (current_time - get_last_meal(&game->philos[i]) >= game->time_die)
			{
				set_state(&game->philos[i], dead);
				set_dead(game, &game->philos[i]);
				print_state(game, &game->philos[i]);
				set_state(&game->philos[i], none);
				return (NULL);
			}
			if (game->nb_max_eat != -1 && get_nb_eat(game) == (int)game->nb_philo)
				return (NULL);
			i++;
		}
		ft_usleep(100);
	}
	return (NULL);
}
