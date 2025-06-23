/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:17:51 by aboumall          #+#    #+#             */
/*   Updated: 2025/06/23 20:24:17 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->nb_philo)
	{
		game->philos[i].id = i + 1;
		game->philos[i].meals_eaten = 0;
		game->philos[i].last_meal = 0;
		game->philos[i].state = none;
		pthread_mutex_init(&game->philos[i].fork.fork_lock, NULL);
		pthread_mutex_init(&game->philos[i].meals_eaten_lock, NULL);
		pthread_mutex_init(&game->philos[i].last_meal_lock, NULL);
		pthread_mutex_init(&game->philos[i].state_lock, NULL);
		if (i > 0)
			game->philos[i - 1].next = &game->philos[i];
		else
			game->philos[i].prev = &game->philos[game->nb_philo - 1];
		i++;
	}
	game->philos[game->nb_philo - 1].next = &game->philos[0];
}

void	free_game(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->nb_philo)
	{
		pthread_mutex_destroy(&game->philos[i].fork.fork_lock);
		pthread_mutex_destroy(&game->philos[i].meals_eaten_lock);
		pthread_mutex_destroy(&game->philos[i].last_meal_lock);
		pthread_mutex_destroy(&game->philos[i].state_lock);
		i++;
	}
	free(game->philos);
	game->philos = NULL;
	pthread_mutex_destroy(&game->print_lock);
	pthread_cancel(game->death_thread);
	game->dead = NULL;
} 
