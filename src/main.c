/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:26:47 by aboumall          #+#    #+#             */
/*   Updated: 2025/06/28 18:43:40 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	setup(int ac, char **av, t_game *game)
{
	game->nb_philo = mini_atoi(av[1]);
	game->time_die = mini_atoi(av[2]);
	game->time_eat = mini_atoi(av[3]);
	game->time_sleep = mini_atoi(av[4]);
	if (ac == 6)
		game->nb_max_eat = (int)mini_atoi(av[5]);
	else
		game->nb_max_eat = -1;
}

static void	init_game(t_game *game)
{
	game->philos = malloc(sizeof(t_philo) * game->nb_philo);
	if (!game->philos)
		exit(EXIT_FAILURE);
	game->dead = NULL;
	pthread_mutex_init(&game->print_lock, NULL);
	pthread_mutex_init(&game->nb_eat_lock, NULL);
	pthread_mutex_init(&game->dead_lock, NULL);
	pthread_mutex_init(&game->start_lock, NULL);
	game->start = false;
	init_philos(game);
	pthread_create(&game->death_thread, NULL, death_check, game);
	set_start(game, true);
}

static void	start_game(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->nb_philo)
	{
		pthread_join(game->philos[i].thread, NULL);
		i++;
	}
	pthread_join(game->death_thread, NULL);
}

t_bool	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!is_digit(av[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac < 5 || ac > 6)
	{
		printf(USAGE);
		return (1);
	}
	else if (!check_args(ac, av))
	{
		printf(ERROR);
		return (2);
	}
	setup(ac, av, &game);
	init_game(&game);
	start_game(&game);
	free_game(&game);
	return (0);
}
