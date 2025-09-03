/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:39:42 by aboumall          #+#    #+#             */
/*   Updated: 2025/09/03 20:17:54 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_meals_eaten(t_game *game, t_philo *philo, size_t meals)
{
	sem_wait(game->meals_eaten_sem);
	philo->meals_eaten = meals;
	sem_post(game->meals_eaten_sem);
}

size_t	get_meals_eaten(t_game *game, t_philo *philo)
{
	size_t	meals;

	sem_wait(game->meals_eaten_sem);
	meals = philo->meals_eaten;
	sem_post(game->meals_eaten_sem);
	return (meals);
}

void	set_last_meal(t_game *game, t_philo *philo, size_t last_meal)
{
	sem_wait(game->last_meal_sem);
	philo->last_meal = last_meal;
	sem_post(game->last_meal_sem);
}

size_t	get_last_meal(t_game *game, t_philo *philo)
{
	size_t	last_meal;

	sem_wait(game->last_meal_sem);
	last_meal = philo->last_meal;
	sem_post(game->last_meal_sem);
	return (last_meal);
}
