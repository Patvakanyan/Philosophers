/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:45:40 by apatvaka          #+#    #+#             */
/*   Updated: 2025/06/07 12:49:19 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time)
{
	int	i;

	i = 0;
	while (i * 1000 <= time)
	{
		usleep(1000);
		++i;
	}
}

void	*chek_sim(void *arg)
{
	int		i;
	t_table	*table;

	table = arg;
	i = -1;
	usleep(1000);
	while (++i < table->num_of_philo)
	{
		pthread_mutex_lock(&(table->print_mutex));
		pthread_mutex_unlock(&(table->print_mutex));
		if (table->philo[i].last_meal_time > table->time_to_die)
		{
			// if (table->optional_eat)
			// {
			// 	pthread_mutex_lock(&(table->philo[i].meal_mutex));
			// 	pthread_mutex_unlock(&(table->philo[i].meal_mutex));
			// }
			pthread_mutex_lock(&(table->print_mutex));
			printf("id = %d philo is die++++++++++++++++++++++++++++++",
				table->philo[i].id);
			pthread_mutex_unlock(&(table->print_mutex));
			pthread_mutex_lock(&(table->sim_stop_mutex));
			table->philo[i].is_die = TRUE;
			pthread_mutex_unlock(&(table->sim_stop_mutex));
			return (end_sim(table), NULL);
		}
	}
	return (NULL);
}

void	choose_forks(t_philo *philo)
{
	int	left;
	int	right;
	int	temp;

	left = philo->id;
	right = (philo->id + 1) % philo->table->num_of_philo;
	// pthread_mutex_lock(&(philo->table->print_mutex));
	// printf("hello = %d", (philo->id + 1) / );
	// pthread_mutex_unlock(&(philo->table->print_mutex));
	if (philo->id % 2 == 0)
	{
		temp = left;
		left = right;
		right = temp;
	}
	pthread_mutex_lock(&(philo->table->forks[left]));
	printf("id = %d take the left fork [%d]\n", philo->id, left);
	pthread_mutex_lock(&(philo->table->forks[right]));
	printf("id = %d take the right fork [%d]\n", philo->id, right);
	printf("id = %d eating time\n", philo->id);
	philo->last_meal_time = get_time();
	philo->meal_count++;
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&(philo->table->forks[left]));
	pthread_mutex_unlock(&(philo->table->forks[right]));
}

void	take_the_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&(philo->table->print_mutex));
		printf("id = %d thinking time\n", philo->table->philo->id);
		pthread_mutex_unlock(&(philo->table->print_mutex));
		usleep(philo->table->time_to_eat / 2);
		choose_forks(philo);
	}
	choose_forks(philo);
}

void	*start_sim(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		if (philo->is_die)
			return (end_sim(philo->table), NULL);
		take_the_forks(philo);
		pthread_mutex_lock(&(philo->table->print_mutex));
		printf("id = %d sleeping time\n", philo->table->philo->id);
		pthread_mutex_unlock(&(philo->table->print_mutex));
		ft_usleep(philo->table->time_to_sleep);
	}
	return (NULL);
}

int	build_sim(t_table *table)
{
	int	i;

	i = -1;
	table->start_time = get_time() + 100;
	pthread_create(&(table->check_die), NULL, chek_sim, table);
	while (++i < table->num_of_philo)
		pthread_create(&(table->philo[i].thread), NULL, start_sim,
			&(table->philo[i]));
	i = -1;
	while (++i < table->num_of_philo)
		pthread_join(table->philo[i].thread, NULL);
	pthread_join(table->check_die, NULL);
	while (get_time() < table->start_time)
		usleep(100);
	return (1);
}

// init myutex
int	init_philos(t_table *table)
{
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
	if (!init_philos_hellper(table))
		return (0);
	if (!build_sim(table))
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
