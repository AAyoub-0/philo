/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:35:40 by aboumall          #+#    #+#             */
/*   Updated: 2025/06/28 18:40:21 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_nb_eat(t_game *game, int nb_eat)
{
	pthread_mutex_lock(&game->print_lock);
	game->nb_eat = nb_eat;
	pthread_mutex_unlock(&game->print_lock);
}

int	get_nb_eat(t_game *game)
{
	int	nb_eat;

	pthread_mutex_lock(&game->print_lock);
	nb_eat = game->nb_eat;
	pthread_mutex_unlock(&game->print_lock);
	return (nb_eat);
}

void	set_start(t_game *game, t_bool start)
{
	pthread_mutex_lock(&game->start_lock);
	game->start = start;
	pthread_mutex_unlock(&game->start_lock);
}

t_bool	get_start(t_game *game)
{
	t_bool	start;

	pthread_mutex_lock(&game->start_lock);
	start = game->start;
	pthread_mutex_unlock(&game->start_lock);
	return (start);
}
