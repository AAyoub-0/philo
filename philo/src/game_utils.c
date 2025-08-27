/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:35:40 by aboumall          #+#    #+#             */
/*   Updated: 2025/08/21 15:22:47 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_nb_eat(t_game *game, int nb_eat)
{
	pthread_mutex_lock(&game->nb_eat_lock);
	game->nb_eat = nb_eat;
	pthread_mutex_unlock(&game->nb_eat_lock);
}

int	get_nb_eat(t_game *game)
{
	int	nb_eat;

	pthread_mutex_lock(&game->nb_eat_lock);
	nb_eat = game->nb_eat;
	pthread_mutex_unlock(&game->nb_eat_lock);
	return (nb_eat);
}
