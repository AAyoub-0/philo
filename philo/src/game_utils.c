/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:35:40 by aboumall          #+#    #+#             */
/*   Updated: 2025/09/29 11:03:07 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_dead(t_game *game, t_philo *philo)
{
	pthread_mutex_lock(&game->dead_lock.mutex);
	game->dead = philo;
	pthread_mutex_unlock(&game->dead_lock.mutex);
}

t_philo	*get_dead(t_game *game)
{
	t_philo	*dead;

	pthread_mutex_lock(&game->dead_lock.mutex);
	dead = game->dead;
	pthread_mutex_unlock(&game->dead_lock.mutex);
	return (dead);
}

void	set_fork_used(t_fork *fork, t_bool used)
{
	pthread_mutex_lock(&fork->fork_lock.mutex);
	fork->used = used;
	pthread_mutex_unlock(&fork->fork_lock.mutex);
}

t_bool	get_fork_used(t_fork *fork)
{
	t_bool	used;

	pthread_mutex_lock(&fork->fork_lock.mutex);
	used = fork->used;
	pthread_mutex_unlock(&fork->fork_lock.mutex);
	return (used);
}

void	set_nb_eat(t_game *game, int nb_eat)
{
	pthread_mutex_lock(&game->nb_eat_lock.mutex);
	game->nb_eat = nb_eat;
	pthread_mutex_unlock(&game->nb_eat_lock.mutex);
}
