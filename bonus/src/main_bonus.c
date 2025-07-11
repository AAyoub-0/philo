/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:26:47 by aboumall          #+#    #+#             */
/*   Updated: 2025/06/29 21:35:11 by aboumall         ###   ########.fr       */
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

sem_t	*sem_clean_open(t_game *game, const char *name, int value)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (sem == SEM_FAILED)
	{
		perror("Semaphore initialization failed");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	return (sem);
}

static void	init_game(t_game *game)
{
	game->philos = malloc(sizeof(t_philo) * game->nb_philo);
	if (!game->philos)
		exit(EXIT_FAILURE);
	game->print_sem = sem_clean_open(game, PRINT_SEM_NAME, 1);
	game->nb_eat_sem = sem_clean_open(game, NB_EAT_SEM_NAME, 0);
	game->dead_sem = sem_clean_open(game, DEAD_SEM_NAME, 1);
	game->forks_sem = sem_clean_open(game, FORKS_SEM_NAME, game->nb_philo);
	pthread_create(&game->nb_eat_thread, NULL, eat_check, game);
	init_philos(game);
}

static void	start_game(t_game *game)
{
	size_t	i;

	i = 0;
	pthread_detach(game->nb_eat_thread);
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
		i++;
	}
	waitpid(-1, NULL, 0);
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
