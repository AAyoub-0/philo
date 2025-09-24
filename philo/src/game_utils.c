/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:35:40 by aboumall          #+#    #+#             */
/*   Updated: 2025/09/24 10:38:19 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_dead(t_game *game, t_philo *philo)
{
	pthread_mutex_lock(&game->dead_lock);
	game->dead = philo;
	pthread_mutex_unlock(&game->dead_lock);
}

t_philo	*get_dead(t_game *game)
{
	t_philo	*dead;

	pthread_mutex_lock(&game->dead_lock);
	dead = game->dead;
	pthread_mutex_unlock(&game->dead_lock);
	return (dead);
}

void	set_fork_used(t_fork *fork, t_bool used)
{
	pthread_mutex_lock(&fork->fork_lock);
	fork->used = used;
	pthread_mutex_unlock(&fork->fork_lock);
}

t_bool	get_fork_used(t_fork *fork)
{
	t_bool	used;

	pthread_mutex_lock(&fork->fork_lock);
	used = fork->used;
	pthread_mutex_unlock(&fork->fork_lock);
	return (used);
}
