/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:48:03 by aboumall          #+#    #+#             */
/*   Updated: 2025/03/04 23:41:40 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_thread	*init_thread(size_t id, t_game *game)
{
	t_thread	*thread;
	
	thread = malloc(sizeof(t_thread));
	if (!thread)
		return;
	thread->id = id;
	thread->game = game;
	thread->id_lock = malloc(sizeof(pthread_mutex_t));
	if (!thread->id_lock)
		exit (EXIT_FAILURE);
	pthread_mutex_init(thread->id_lock, NULL);
	return (thread);
}

unsigned int	get_thread_id(t_thread *thread)
{
	unsigned int	id;

	pthread_mutex_lock(thread->id_lock);
	id = thread->id;
	pthread_mutex_unlock(thread->id_lock);
	return (id);
}

void	*simple_function(void *param)
{
	t_thread	*thread;

	thread = (t_thread *)param;
	while (true)
	{
		printf("I am thread nb %d\n", get_thread_id(thread));
		sleep(3);
	}
	return (NULL);
}

void	start_threads(t_game *game)
{
	size_t	i;

	game->threads = malloc((sizeof(pthread_t) * game->nb_philo) + 1);
	if (!game->threads)
		exit (EXIT_FAILURE);
	i = 0;
	while (i < game->nb_philo)
	{
		pthread_create(&game->threads[i], NULL, simple_function, init_thread(i + 1, game));
		i++;
	}
	usleep(1000);
	i = 0;
	while (i < game->nb_philo)
	{
		pthread_join(game->threads[i], NULL);
		i++;
	}
}

void	free_threads(t_game *game)
{
	size_t	i;
	
	if (game->threads == NULL)
		return ;
	while (i < game->nb_philo + 1)
	{
		free(game->threads[i]);
		i++;
	}
}
