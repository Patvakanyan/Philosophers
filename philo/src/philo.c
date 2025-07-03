/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:45:40 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/03 15:11:54 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	choose_forks(t_philo *philo)
{
	if (!choose_forks_hellper(philo))
		return ;
	pthread_mutex_unlock(&(philo->table->sim_stop_mutex));
	pthread_mutex_lock(&(philo->table->forks[philo->left]));
	pthread_mutex_lock(&(philo->table->forks[philo->right]));
	pthread_mutex_lock(&(philo->table->sim_stop_mutex));
	if (!philo->table->sim_stop)
	{
		pthread_mutex_lock(&(philo->table->print_mutex));
		printf("id = %d take the left fork\n", philo->id + 1);
		printf("id = %d take the right fork\n", philo->id + 1);
		printf("id = %d eating time\n", philo->id + 1);
		pthread_mutex_unlock(&(philo->table->print_mutex));
	}
	pthread_mutex_unlock(&(philo->table->sim_stop_mutex));
	pthread_mutex_lock(&(philo->meal_mutex));
	philo->last_meal_time = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&(philo->meal_mutex));
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&(philo->table->forks[philo->left]));
	pthread_mutex_unlock(&(philo->table->forks[philo->right]));
}

void	take_the_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&(philo->table->sim_stop_mutex));
		pthread_mutex_lock(&(philo->meal_mutex));
		if (!philo->table->sim_stop && philo->last_meal_time)
		{
			pthread_mutex_lock(&(philo->table->print_mutex));
			printf("id = %d thinking time\n", philo->id + 1);
			pthread_mutex_unlock(&(philo->table->print_mutex));
		}
		pthread_mutex_unlock(&(philo->meal_mutex));
		pthread_mutex_unlock(&(philo->table->sim_stop_mutex));
		usleep(philo->table->time_to_die / 2);
		choose_forks(philo);
	}
	else
		choose_forks(philo);
}

void	*start_sim(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (get_time() < philo->table->start_time)
		usleep(100);
	if(philo->id % 2)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&(philo->table->sim_stop_mutex));
		if (philo->table->sim_stop)
			return (pthread_mutex_unlock(&(philo->table->sim_stop_mutex)),
				NULL);
		pthread_mutex_unlock(&(philo->table->sim_stop_mutex));
		take_the_forks(philo);
		pthread_mutex_lock(&(philo->table->sim_stop_mutex));
		if (!philo->table->sim_stop && philo->last_meal_time)
		{
			pthread_mutex_lock(&(philo->table->print_mutex));
			printf("id = %d sleeping time\n", philo->id + 1);
			pthread_mutex_unlock(&(philo->table->print_mutex));
		}
		pthread_mutex_unlock(&(philo->table->sim_stop_mutex));
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
	pthread_join(table->check_die, NULL);
	while (++i < table->num_of_philo)
		pthread_join(table->philo[i].thread, NULL);
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
	if (!table)
		return (print_error("Memory allocation failed!\n", 0));
	table->philo = NULL;
	if (!((argc == 5 || argc == 6) && is_validate(argc, argv, table)))
		return (free_table(table), print_error("Wrong arguments!\n", 0));
	if (!init_philos(table))
		return (free(table), print_error("Memory allocation failed!\n", 0));
	end_sim(table);
	free_table(table);
	return (0);
}
