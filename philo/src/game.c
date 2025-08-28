/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:19:52 by aboumall          #+#    #+#             */
/*   Updated: 2025/08/28 17:13:40 by aboumall         ###   ########.fr       */
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
	t_philo	*dead;

	pthread_mutex_lock(&game->dead_lock);
	dead = game->dead;
	pthread_mutex_unlock(&game->dead_lock);
	return (dead);
}

t_bool	is_dead(t_game *game)
{
	size_t	i;

	i = -1;
	while (++i < game->nb_philo)
	{
		if (ft_get_time()
			- get_last_meal(&game->philos[i]) >= game->time_die)
		{
			set_dead(game, &game->philos[i]);
			print_state(game, &game->philos[i], dead);
			return (true);
		}
		if (game->nb_max_eat != -1
			&& get_nb_eat(game) == (int)game->nb_philo)
			return (true);
	}
	return (false);
}

void	*death_check(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	while (ft_get_time() < game->start_time)
		continue ;
	if (game->thread_crashed)
		return (NULL);
	while (true)
	{
		if (is_dead(game))
			return (NULL);
		usleep(10);
	}
	return (NULL);
}
