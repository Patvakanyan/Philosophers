/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hellper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:17:57 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/09 13:55:52 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&(philo->meal_mutex));
	philo->last_meal_time = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&(philo->meal_mutex));
	pthread_mutex_lock(&philo->table->forks[0]);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d has taken a fork\n", get_time() - philo->table->start_time,
		philo->id + 1);
	pthread_mutex_unlock(&philo->table->print_mutex);
	ft_usleep(philo->table, philo->table->time_to_die / 1000);
	pthread_mutex_unlock(&philo->table->forks[0]);
	pthread_mutex_lock(&philo->table->sim_stop_mutex);
	philo->table->sim_stop = TRUE;
	pthread_mutex_unlock(&philo->table->sim_stop_mutex);
	return (1);
}

int	choose_forks_hellper(t_philo *philo)
{
	int	temp;

	if (philo->table->num_of_philo == 1)
		return (one_philo(philo), 0);
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

void	ft_usleep(t_table *table, int ms)
{
	long int	start;

	start = get_time();
	while (get_time() - start < ms)
	{
		pthread_mutex_lock(&table->sim_stop_mutex);
		if (table->sim_stop)
		{
			pthread_mutex_unlock(&table->sim_stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->sim_stop_mutex);
		usleep(100);
	}
}

void	chek_sim_hellper(t_table *table)
{
	pthread_mutex_unlock(&(table->philo[table->i].meal_mutex));
	print_hellper(&table->philo[table->i], "died");
	pthread_mutex_lock(&(table->sim_stop_mutex));
	table->sim_stop = TRUE;
	pthread_mutex_unlock(&(table->sim_stop_mutex));
}
