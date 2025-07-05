/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_attribute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:02:52 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/05 12:43:47 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*chek_sim(void *arg)
{
	long int	time;
	t_table		*table;

	table = arg;
	while (1)
	{
		table->i = -1;
		while (++table->i < table->num_of_philo)
		{
			pthread_mutex_lock(&(table->philo[table->i].meal_mutex));
			time = get_time() - table->philo[table->i].last_meal_time;
			if (table->optional_eat
				&& table->optional_eat == table->philo[table->i].meal_count)
			{
				pthread_mutex_unlock(&table->philo[table->i].meal_mutex);
				pthread_mutex_lock(&(table->sim_stop_mutex));
				table->sim_stop = TRUE;
				pthread_mutex_unlock(&(table->sim_stop_mutex));
				return (NULL);
			}
			if (time > table->time_to_die
				&& table->philo[table->i].last_meal_time)
				return (chek_sim_hellper(table), NULL);
			pthread_mutex_unlock(&(table->philo[table->i].meal_mutex));
		}
		usleep(table->num_of_philo * 1000);
	}
	return (NULL);
}
