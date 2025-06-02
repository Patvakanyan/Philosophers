/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:45:40 by apatvaka          #+#    #+#             */
/*   Updated: 2025/06/02 13:18:35 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_sim(t_table *table)
{
}

int	build_sim(t_table *table)
{
	int	i;

	i = -1;
	pthread_create(table->);
	while (++i < table->num_of_philo)
	{
		pthread_create(table->philo[i].thread, NULL, start_sim, table);
		pthread_join(&(table->philo[i]), NULL);
	}
}

// init myutex
int	init_philos(t_table *table)
{
	table->i = -1;
	table->philo = malloc(sizeof(t_philo) * table->num_of_philo);
	if (!table->philo)
		return (0);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_of_philo);
	if (!table->forks)
		return (0);
	if (pthread_mutex_init(&(table->sim_stop_mutex), NULL) < 0)
		return (free(table->forks), free(table->philo), 0);
	if (pthread_mutex_init(&(table->print_mutex), NULL) < 0)
		return (free(table->forks),
			pthread_mutex_destroy(&(table->sim_stop_mutex)), free(table->philo),
			0);
	if (init_philos_hellper(table))
		return (0);
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
		return (print_error("Memory allocation failed!\n", 0));
	if (!((argc == 5 || argc == 6) && is_validate(argc, argv, table)))
		return (free_table(table), print_error("Wrong arguments!\n", 0));
	if (!init_philos(table))
		return (free(table), print_error("Memory allocation failed!\n", 0));
	free(table);
	return (0);
}
