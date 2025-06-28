/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:35:40 by aboumall          #+#    #+#             */
/*   Updated: 2025/06/29 01:42:46 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_nb_eat(t_game *game, int nb_eat)
{
	sem_wait(game->nb_eat_sem);
	game->nb_eat = nb_eat;
	sem_post(game->nb_eat_sem);
}

int	get_nb_eat(t_game *game)
{
	int	nb_eat;

	sem_wait(game->nb_eat_sem);
	nb_eat = game->nb_eat;
	sem_post(game->nb_eat_sem);
	return (nb_eat);
}

void	set_start(t_game *game, t_bool start)
{
	sem_wait(game->start_sem);
	game->start = start;
	sem_close(game->start_sem);
}

t_bool	get_start(t_game *game)
{
	t_bool	start;

	sem_wait(game->start_sem);
	start = game->start;
	sem_post(game->start_sem);
	return (start);
}
