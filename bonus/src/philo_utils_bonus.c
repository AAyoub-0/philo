/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:39:42 by aboumall          #+#    #+#             */
/*   Updated: 2025/06/29 21:25:43 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_meals_eaten(t_philo *philo, size_t meals)
{
	sem_wait(philo->meals_eaten_sem);
	philo->meals_eaten = meals;
	sem_post(philo->meals_eaten_sem);
}

size_t	get_meals_eaten(t_philo *philo)
{
	size_t	meals;

	sem_wait(philo->meals_eaten_sem);
	meals = philo->meals_eaten;
	sem_post(philo->meals_eaten_sem);
	return (meals);
}

void	set_last_meal(t_philo *philo, size_t last_meal)
{
	sem_wait(philo->last_meal_sem);
	philo->last_meal = last_meal;
	sem_post(philo->last_meal_sem);
}

size_t	get_last_meal(t_philo *philo)
{
	size_t	last_meal;

	sem_wait(philo->last_meal_sem);
	last_meal = philo->last_meal;
	sem_post(philo->last_meal_sem);
	return (last_meal);
}
