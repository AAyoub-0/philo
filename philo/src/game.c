/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:19:52 by aboumall          #+#    #+#             */
/*   Updated: 2025/09/26 01:09:54 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_game(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->nb_philo)
	{
		safe_mutex_destroy(&game->philos[i].fork.fork_lock);
		safe_mutex_destroy(&game->philos[i].meals_eaten_lock);
		safe_mutex_destroy(&game->philos[i].last_meal_lock);
		safe_mutex_destroy(&game->philos[i].done_lock);
		i++;
	}
	free(game->philos);
	game->philos = NULL;
	safe_mutex_destroy(&game->print_lock);
	safe_mutex_destroy(&game->dead_lock);
	safe_mutex_destroy(&game->nb_eat_lock);
	game->dead = NULL;
}

t_bool	check_all_done(t_game *game)
{
	size_t	i;

	i = -1;
	while (++i < game->nb_philo)
	{
		if (get_done(&game->philos[i]) == false)
			return (false);
		usleep(100);
	}
	set_dead(game, &game->philos[i]);
	return (true);
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
			if (get_done(&game->philos[i]) == true)
				return (true);
			set_dead(game, &game->philos[i]);
			print_state(game, &game->philos[i], dead);
			return (true);
		}
		usleep(100);
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
		if (check_all_done(game))
			return (NULL);
		if (is_dead(game))
			return (NULL);
	}
	return (NULL);
}
