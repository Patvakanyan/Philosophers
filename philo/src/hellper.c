/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hellper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:17:57 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/04 19:50:56 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	choose_forks_hellper(t_philo *philo)
{
	int	temp;

	philo->left = philo->id;
	philo->right = (philo->id + 1) % philo->table->num_of_philo;
	if (philo->id % 2 == 0)
	{
		temp = philo->left;
		philo->left = philo->right;
		philo->right = temp;
	}
	pthread_mutex_lock(&(philo->table->sim_stop_mutex));
	if (philo->table->sim_stop)
	{
		pthread_mutex_unlock(&(philo->table->sim_stop_mutex));
		return (0);
	}
	return (1);
}

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
		table->philo[table->i].last_meal_time = 0;
		table->philo[table->i].meal_count = 0;
		table->philo[table->i].right = 0;
		table->philo[table->i].left = 0;
	}
	return (1);
}

void	ft_usleep(int ms)
{
	long int	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(500);
}

long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (int)1000) + (time.tv_usec / 1000));
}

void	chek_sim_hellper(t_table *table)
{
	pthread_mutex_unlock(&(table->philo[table->i].meal_mutex));
	pthread_mutex_lock(&(table->print_mutex));
	printf("%ld %d died\n", get_time() - table->start_time,
		table->philo[table->i].id + 1);
	pthread_mutex_unlock(&(table->print_mutex));
	pthread_mutex_lock(&(table->sim_stop_mutex));
	table->sim_stop = TRUE;
	pthread_mutex_unlock(&(table->sim_stop_mutex));
}
