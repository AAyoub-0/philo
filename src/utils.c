/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:47:01 by aboumall          #+#    #+#             */
/*   Updated: 2025/02/26 13:47:38 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	mini_atoi(char *str)
{
	size_t	result;
	int i;
	
	i = 0;
	result = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result);
}

void	print_philo(t_philo *philo)
{
	printf("Philo[%p]\n{\n", philo);
	printf("      id : %d;\n", philo->id);
	printf("      fork : %p;\n", philo->fork);
	printf("}\n");
}

void	print_game(t_game *game)
{
	printf("Game[%p]\n{\n", game);
	printf("      nb_philo   : %zu;\n", game->nb_philo);
	printf("      time_die   : %zu;\n", game->time_die);
	printf("      time_eat   : %zu;\n", game->time_eat);
	printf("      time_sleep : %zu;\n", game->time_sleep);
	printf("      nb_max_eat : %d;\n", game->nb_max_eat);
	printf("}\n");
}
