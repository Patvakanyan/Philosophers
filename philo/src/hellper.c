/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hellper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:17:57 by apatvaka          #+#    #+#             */
/*   Updated: 2025/06/05 17:00:12 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos_hellper(t_table *table)
{
	table->i = -1;
	while (++(table->i) < table->num_of_philo)
	{
		if (pthread_mutex_init(&(table->philo[table->i].meal_mutex), NULL) < 0
			|| pthread_mutex_init(&(table->forks[table->i]), NULL) < 0)
			return (free_mutex_forks(table, table->i), free_mutex_meal(table,
					table->i), pthread_mutex_destroy(&(table->print_mutex)),
				pthread_mutex_destroy(&(table->sim_stop_mutex)), 0);
		table->philo[table->i].id = table->i;
		table->philo[table->i].table = table;
		table->philo[table->i].is_die = FALSE;
		table->philo[table->i].last_meal_time = 0;
		table->philo[table->i].meal_count = 0;
	}
	return (1);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000000);
}
