/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:24:16 by aboumall          #+#    #+#             */
/*   Updated: 2025/09/24 14:26:43 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_philo(t_game *game)
{
	if (game->print_sem)
		sem_close(game->print_sem);
	if (game->nb_eat_sem)
		sem_close(game->nb_eat_sem);
	if (game->philo_dead_sem)
		sem_close(game->philo_dead_sem);
	if (game->forks_sem)
		sem_close(game->forks_sem);
	if (game->meals_eaten_sem)
		sem_close(game->meals_eaten_sem);
	if (game->last_meal_sem)
		sem_close(game->last_meal_sem);
	if (game->end_sim_sem)
		sem_close(game->end_sim_sem);
	free(game->philos);
	game->philos = NULL;
}

void	set_philo_dead(t_game *game, t_bool philo_dead)
{
	sem_wait(game->philo_dead_sem);
	game->philo_dead = philo_dead;
	sem_post(game->philo_dead_sem);
}

t_bool	get_philo_dead(t_game *game)
{
	t_bool	philo_dead;

	sem_wait(game->philo_dead_sem);
	philo_dead = game->philo_dead;
	sem_post(game->philo_dead_sem);
	return (philo_dead);
}

void	*end_sim_check(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	sem_wait(game->end_sim_sem);
	set_philo_dead(game, true);
	return (NULL);
}
