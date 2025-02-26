/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:44:16 by aboumall          #+#    #+#             */
/*   Updated: 2025/02/26 14:49:50 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_null_philo(t_philo *philo)
{
	philo->fork = NULL;
	philo->prev = NULL;
	philo->next = NULL;
}

void	init_philo(t_game *game, t_philo *philo)
{
	(void)game;
	set_null_philo(philo);
		philo->fork = malloc(sizeof(t_fork));
	if (!philo->fork)
		exit (EXIT_FAILURE);
	philo->fork->is_used = false;
	philo->state = none;
	philo->fork->f_restrict = NULL;
	philo->fork->attr = NULL;
}

void	init_philos(t_game *game)
{
	size_t	i;
	
	game->philos = malloc(sizeof(t_philo) * game->nb_philo);
	if (!game->philos)
		exit (EXIT_FAILURE);
	i = 0;
	while (i < game->nb_philo)
	{
		init_philo(game, &(game->philos[i]));
		game->philos[i].id = (unsigned int)i + 1;
		i++;
	}
}
