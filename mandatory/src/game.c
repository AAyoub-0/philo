/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:19:52 by aboumall          #+#    #+#             */
/*   Updated: 2025/07/05 01:39:34 by aboumall         ###   ########.fr       */
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
		i++;
	}
	free(game->philos);
	game->philos = NULL;
	pthread_mutex_destroy(&game->print_lock);
	pthread_mutex_destroy(&game->dead_lock);
	pthread_mutex_destroy(&game->nb_eat_lock);
	pthread_mutex_destroy(&game->start_lock);
	game->dead = NULL;
}

void	set_dead(t_game *game, t_philo *philo)
{
	pthread_mutex_lock(&game->dead_lock);
	game->dead = philo;
	pthread_mutex_unlock(&game->dead_lock);
}

t_philo	*get_dead(t_game *game)
{
	t_philo *dead;

	pthread_mutex_lock(&game->dead_lock);
	dead = game->dead;
	pthread_mutex_unlock(&game->dead_lock);
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
				set_dead(game, &game->philos[i]);
				print_state(game, &game->philos[i], dead);
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
