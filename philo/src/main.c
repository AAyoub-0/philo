/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:26:47 by aboumall          #+#    #+#             */
/*   Updated: 2025/08/27 21:02:23 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	setup(int ac, char **av, t_game *game)
{
	game->nb_philo = mini_atoi(av[1]);
	if (game->nb_philo == 0)
	{
		printf(ERROR);
		exit(EXIT_FAILURE);
	}
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
	if (pthread_mutex_init(&game->print_lock, NULL) != 0)
		msg_exit(game, "mutex init failure", 1);
	if (pthread_mutex_init(&game->nb_eat_lock, NULL) != 0)
		msg_exit(game, "mutex init failure", 1);
	if (pthread_mutex_init(&game->dead_lock, NULL) != 0)
		msg_exit(game, "mutex init failure", 1);
	game->dead_printed = false;
	game->start_time = ft_get_time() + (game->nb_philo * 20);
	init_philos(game);
	pthread_create(&game->death_thread, NULL, death_check, game);
}

static void	start_game(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->nb_philo)
	{
		if (pthread_join(game->philos[i].thread, NULL) != 0)
			printf("thread failed to join\n");
		i++;
	}
	if (pthread_join(game->death_thread, NULL) != 0)
		printf("thread failed to join\n");
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
	if (game.nb_max_eat == 0)
		return (0);
	init_game(&game);
	start_game(&game);
	free_game(&game);
	return (0);
}
