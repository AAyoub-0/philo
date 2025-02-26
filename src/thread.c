/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:48:03 by aboumall          #+#    #+#             */
/*   Updated: 2025/02/26 16:25:06 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_threads(t_game *game)
{
	game->threads = malloc(sizeof(pthread_t) * game->nb_philo);
	if (!game->threads)
		exit (EXIT_FAILURE);
}

void	*simple_function(void *param)
{
	t_thread	*thread;

	thread = (t_thread *)param;
	while (true)
	{
		printf("I am thread nb %d\n", thread->id);
		sleep(2);
	}
	return (NULL);
}

void	start_threads(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->nb_philo)
	{
		t_thread *thread = malloc(sizeof(t_thread));
		thread->id = i + 1;
		thread->game = game;
		pthread_create(&(game->threads[i]), NULL, simple_function, thread);
		pthread_join(game->threads[i], NULL);
		free(thread);
		i++;
	}
}
