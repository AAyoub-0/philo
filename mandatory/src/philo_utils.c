/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:39:42 by aboumall          #+#    #+#             */
/*   Updated: 2025/07/05 01:19:39 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_meals_eaten(t_philo *philo, size_t meals)
{
	pthread_mutex_lock(&philo->meals_eaten_lock);
	philo->meals_eaten = meals;
	pthread_mutex_unlock(&philo->meals_eaten_lock);
}

size_t	get_meals_eaten(t_philo *philo)
{
	size_t	meals;

	pthread_mutex_lock(&philo->meals_eaten_lock);
	meals = philo->meals_eaten;
	pthread_mutex_unlock(&philo->meals_eaten_lock);
	return (meals);
}

void	set_last_meal(t_philo *philo, size_t last_meal)
{
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = last_meal;
	pthread_mutex_unlock(&philo->last_meal_lock);
}

size_t	get_last_meal(t_philo *philo)
{
	size_t	last_meal;

	pthread_mutex_lock(&philo->last_meal_lock);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_lock);
	return (last_meal);
}
