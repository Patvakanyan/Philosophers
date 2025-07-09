/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_attribute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:02:52 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/09 16:44:02 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	optional_eat_hellper(t_table *table)
{
	int	i;

	i = -1;
	if (!table->optional_eat)
		return (1);
	while (++i < table->num_of_philo)
	{
		pthread_mutex_lock(&table->philo[i].meal_mutex);
		if (table->optional_eat
			&& table->philo[i].meal_count < table->optional_eat)
			return (pthread_mutex_unlock(&table->philo[i].meal_mutex), 1);
		pthread_mutex_unlock(&table->philo[i].meal_mutex);
	}
	pthread_mutex_lock(&(table->sim_stop_mutex));
	table->sim_stop = TRUE;
	pthread_mutex_unlock(&(table->sim_stop_mutex));
	return (0);
}

void	*chek_sim(void *arg)
{
	t_table		*table;
	long int	time;

	table = arg;
	while (1)
	{
		table->i = -1;
		if (!optional_eat_hellper(table))
			return (NULL);
		while (++table->i < table->num_of_philo)
		{
			pthread_mutex_lock(&(table->philo[table->i].meal_mutex));
			time = get_time() - table->philo[table->i].last_meal_time;
			if ((time > (table->time_to_die / 1000))
				&& table->philo[table->i].last_meal_time)
				return (chek_sim_hellper(table), NULL);
			pthread_mutex_unlock(&(table->philo[table->i].meal_mutex));
		}
		usleep(1000);
	}
	return (NULL);
}

long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (int)1000) + (time.tv_usec / 1000));
}

void	choose_forks(t_philo *philo)
{
	if (!choose_forks_hellper(philo))
		return ;
	pthread_mutex_lock(&(philo->table->forks[philo->left]));
	pthread_mutex_lock(&(philo->table->forks[philo->right]));
	print_hellper(philo, "has taken a fork");
	print_hellper(philo, "has taken a fork");
	print_hellper(philo, "is eating");
	pthread_mutex_lock(&(philo->meal_mutex));
	philo->last_meal_time = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&(philo->meal_mutex));
	ft_usleep(philo->table, philo->table->time_to_eat / 1000);
	pthread_mutex_unlock(&(philo->table->forks[philo->left]));
	pthread_mutex_unlock(&(philo->table->forks[philo->right]));
}

void	print_hellper(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->sim_stop_mutex);
	if (!philo->table->sim_stop)
	{
		pthread_mutex_lock(&(philo->table->print_mutex));
		printf("%ld %d  %s\n", get_time() - philo->table->start_time, philo->id
			+ 1, str);
		pthread_mutex_unlock(&(philo->table->print_mutex));
	}
	pthread_mutex_unlock(&philo->table->sim_stop_mutex);
}
