/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:35:40 by aboumall          #+#    #+#             */
/*   Updated: 2025/08/20 04:05:50 by aboumall         ###   ########.fr       */
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
