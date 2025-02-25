/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:26:47 by aboumall          #+#    #+#             */
/*   Updated: 2025/02/25 19:55:56 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	mini_atoi(char *str)
{
	size_t	result;
	int i;
	
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result);
}

void	set_null_philo(t_philo *philo)
{
	philo->fork = NULL;
	philo->prev = NULL;
	philo->next = NULL;
}

void	init_philo(t_game *game, t_philo *philo)
{
	set_null_philo(philo);
		philo->fork = malloc(sizeof(t_fork));
	if (!philo->fork)
		exit (EXIT_FAILURE);
	philo->fork->is_used = false;
	philo->fork->f_restrict = NULL;
	philo->fork->attr = NULL;
}

void	init_philos(t_game *game)
{
	int	i;
	
	game->philos = malloc(sizeof(t_philo) * game->nb_philo);
	if (!game->philos)
		exit (EXIT_FAILURE);
	i = 0;
	while (i < game->nb_philo)
	{
		init_philo(game, &(game->philos[i]));
		i++;
	}
}

void	init_threads(t_game *game)
{
	
}

void	init_setup(int ac, char **av, t_game *game)
{
	game->nb_philo = mini_atoi(av[1]);
	if (game->nb_philo == 0 || game->nb_philo > 200)
		exit (EXIT_FAILURE);
	game->time_die = mini_atoi(av[2]);
	game->time_eat = mini_atoi(av[3]);
	game->time_sleep = mini_atoi(av[4]);
	if (ac == 5)
		game->nb_max_eat = mini_atoi(av[5]);
	else
		game->nb_max_eat = -1;
}

void	set_null_game(t_game *game)
{
	game->philos = NULL;
	game->threads = NULL;
}

t_game	*init_game(int ac, char **av)
{
	t_game	*game;
	
	game = malloc(sizeof(t_game));
	if (!game)
		exit (EXIT_FAILURE);
	set_null_game(game);
	init_setup(ac, av, game);
	init_philos(game);
	// init_threads(game);
}

int	main(int ac, char **av)
{
	t_game	*game;
	// init all trheads
	// start the game loop
	init_game(ac, av);
	printf("Philo\n");
	return (0);
}