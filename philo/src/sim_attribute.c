/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_attribute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:02:52 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/03 15:03:29 by apatvaka         ###   ########.fr       */
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
		usleep(1000);
		table->i = -1;
		while (++table->i < table->num_of_philo)
		{
			pthread_mutex_lock(&(table->philo[table->i].meal_mutex));
			time = get_time() - table->philo[table->i].last_meal_time;
			if ((time > table->time_to_die)
				&& table->philo[table->i].last_meal_time)
				return (chek_sim_hellper(table), NULL);
			pthread_mutex_unlock(&(table->philo[table->i].meal_mutex));
		}
	}
	return (NULL);
}
