/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hellper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:11:36 by apatvaka          #+#    #+#             */
/*   Updated: 2025/06/05 16:52:03 by apatvaka         ###   ########.fr       */
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
	while (++i < len)
		pthread_mutex_destroy(&(table->forks[i]));
	free(table->forks);
}

void	end_sim(t_table *table)
{
	int	i;

	i = -1;
	pthread_detach(table->check_die);
	while (++i < table->num_of_philo)
		pthread_detach(table->philo[i].thread);
	free_mutex_forks(table, table->num_of_philo);
	pthread_mutex_destroy(&(table->sim_stop_mutex));
	pthread_mutex_destroy(&(table->philo->meal_mutex));
	pthread_mutex_destroy(&(table->print_mutex));
}

void	free_mutex_meal(t_table *table, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		pthread_mutex_destroy(&(table->philo[i].meal_mutex));
}
