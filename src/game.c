/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:19:52 by aboumall          #+#    #+#             */
/*   Updated: 2025/06/25 18:20:23 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	set_state(t_philo *philo, t_philo_state state)
{
	pthread_mutex_lock(&philo->state_lock);
	philo->state = state;
	pthread_mutex_unlock(&philo->state_lock);
}

void	set_meals_eaten(t_philo *philo, size_t meals)
{
	pthread_mutex_lock(&philo->meals_eaten_lock);
	philo->meals_eaten = meals;
	pthread_mutex_unlock(&philo->meals_eaten_lock);
}

void	set_last_meal(t_philo *philo, size_t last_meal)
{
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = last_meal;
	pthread_mutex_unlock(&philo->last_meal_lock);
}
