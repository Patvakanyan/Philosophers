/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hellper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:11:36 by apatvaka          #+#    #+#             */
/*   Updated: 2025/06/25 19:33:29 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_table *table)
{
	if (table->philo)
		free(table->philo);
	free(table);
}

void	free_mutex_forks(t_table *table, int len)
{
	int	i;

	i = -1;
	while (++i < len && table->sim_stop)
		pthread_mutex_destroy(&(table->forks[i]));
	free(table->forks);
}

void	end_sim(t_table *table)
{
	free_mutex_forks(table, table->num_of_philo);
	free_mutex_meal(table, table->num_of_philo);
	pthread_mutex_destroy(&(table->sim_stop_mutex));
	pthread_mutex_destroy(&(table->print_mutex));
}

void	free_mutex_meal(t_table *table, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		pthread_mutex_destroy(&(table->philo[i].meal_mutex));
}
