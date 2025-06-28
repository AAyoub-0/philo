/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:26:47 by aboumall          #+#    #+#             */
/*   Updated: 2025/06/29 01:47:07 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	game->print_sem = sem_open(PRINT_SEM_NAME, O_CREAT | O_EXCL, 0644, 1);
	game->nb_eat_sem = sem_open(NB_EAT_SEM_NAME, O_CREAT | O_EXCL, 0644, 1);
	game->dead_sem = sem_open(DEAD_SEM_NAME, O_CREAT | O_EXCL, 0644, 1);
	game->start_sem = sem_open(START_SEM_NAME, O_CREAT | O_EXCL, 0644, 1);
	game->forks_sem = sem_open(FORKS_SEM_NAME, O_CREAT | O_EXCL, 0644, game->nb_philo);
	game->start = false;
	game->dead_printed = false;
	init_philos(game);
	pthread_create(&game->death_thread, NULL, death_check, game);
}

static void	start_game(t_game *game)
{
	size_t	i;

	i = 0;
	set_start(game, true);
	while (i < game->nb_philo)
	{
		game->philos[i].pid = fork();
		if (game->philos[i].pid < 0)
		{
			perror("Fork failed");
			free_game(game);
			exit(EXIT_FAILURE);
		}
		if (game->philos[i].pid == 0)
			philo_routine(&game->philos[i]);
		else
			waitpid(game->philos[i].pid, NULL, 0);
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
