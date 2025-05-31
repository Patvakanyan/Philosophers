/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:45:40 by apatvaka          #+#    #+#             */
/*   Updated: 2025/05/31 19:22:32 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	build_sim(t_table *table)
// {
// 	int	i;

// 	i = -1;
// 	while (i < table->num_of_philo)
// }

int	init_philos(t_table *table)
{
	int	i;

	i = -1;
	table->philo = malloc(sizeof(t_philo) * table->num_of_philo);
	if (!table->philo)
		return (0);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_of_philo);
	if (!table->forks)
		return (0);
	if (pthread_mutex_init(&(table->print_mutex), NULL) < 0)
		return (free(table->forks), free(table->philo), 0);
	while (++i < table->num_of_philo)
	{
		if (pthread_mutex_init(&(table->philo[i].meal_mutex), NULL) < 0
			|| pthread_mutex_init(&(table->forks[i]), NULL) < 0)
			return (free_mutex_forks(table, i), free_mutex_meal(table, i),
				pthread_mutex_destroy(&(table->print_mutex)), 0);
		table->philo[i].id = i;
		table->philo[i].last_meal_time = 0;
		table->philo[i].meal_count = 0;
	}
	if (build_sim(table))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	table->philo = NULL;
	if (!table)
		return (print_error("Memory allocation failed!\n", -1));
	if (!((argc == 5 || argc == 6) && is_validate(argc, argv, table)))
		return (free_table(table), print_error("Wrong arguments!\n", -1));
	if (!init_philos(table))
		return (free(table), print_error("Memory allocation failed!\n", -1));
	free(table);
	return (1);
}
