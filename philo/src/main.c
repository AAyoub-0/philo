/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:26:47 by aboumall          #+#    #+#             */
/*   Updated: 2025/09/26 00:04:21 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	setup(int ac, char **av, t_game *game)
{
	game->nb_philo = mini_atoi(av[1]);
	if (game->nb_philo == 0)
		exit(EXIT_FAILURE);
	game->time_die = mini_atoi(av[2]);
	if (game->time_die == 0)
		exit(EXIT_FAILURE);
	game->time_eat = mini_atoi(av[3]);
	if (game->time_eat == 0)
		exit(EXIT_FAILURE);
	game->time_sleep = mini_atoi(av[4]);
	if (game->time_sleep == 0)
		exit(EXIT_FAILURE);
	if (ac == 6)
		game->nb_max_eat = (int)mini_atoi(av[5]);
	else
		game->nb_max_eat = -1;
	if (game->nb_max_eat == 0)
		exit(EXIT_FAILURE);
}

static void	init_game(t_game *game)
{
	game->philos = malloc(sizeof(t_philo) * game->nb_philo);
	if (!game->philos)
		exit(EXIT_FAILURE);
	game->dead = NULL;
	safe_mutex_init(game, &game->print_lock);
	safe_mutex_init(game, &game->nb_eat_lock);
	safe_mutex_init(game, &game->dead_lock);
	game->dead_printed = false;
	game->thread_crashed = false;
	game->death_thread_created = true;
	game->start_time = ft_get_time() + (game->nb_philo * 5);
	game->nb_eat = 0;
	init_philos(game);
}

static void	start_game(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->nb_philo)
	{
		pthread_safe_philo(game, &game->philos[i]);
		i++;
	}
	pthread_safe_death_thread(game);
	i = 0;
	while (i < game->nb_philo)
	{
		if (game->philos[i].thread_created)
			pthread_join(game->philos[i].thread, NULL);
		i++;
	}
	if (game->death_thread_created)
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
			if (!ft_isdigit(av[i][j]))
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
