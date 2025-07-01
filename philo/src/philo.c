/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:45:40 by apatvaka          #+#    #+#             */
/*   Updated: 2025/06/25 19:17:58 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int ms)
{
	long int	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(500);
}

void	*chek_sim(void *arg)
{
	int			i;
	long int	time;
	t_table		*table;

	table = arg;
	while (1)
	{
		usleep(1000);
		i = -1;
		while (++i < table->num_of_philo)
		{
			pthread_mutex_lock(&(table->philo[i].meal_mutex));
			time = get_time() - table->philo[i].last_meal_time;
			if ((time > table->time_to_die) && table->philo[i].last_meal_time)
			{
				pthread_mutex_unlock(&(table->philo[i].meal_mutex));
				pthread_mutex_lock(&(table->print_mutex));
				printf("id = %d philo is die = %ld\n", table->philo[i].id,
					table->philo[i].last_meal_time);
				pthread_mutex_unlock(&(table->print_mutex));
				pthread_mutex_lock(&(table->sim_stop_mutex));
				table->sim_stop = TRUE;
				pthread_mutex_unlock(&(table->sim_stop_mutex));
				return (NULL);
			}
			pthread_mutex_unlock(&(table->philo[i].meal_mutex));
		}
	}
	return (NULL);
}

// pthread_mutex_lock(&(philo->table->print_mutex));
// printf("hello = %d", (philo->id + 1) / );
// pthread_mutex_unlock(&(philo->table->print_mutex));
void	choose_forks(t_philo *philo)
{
	int	left;
	int	right;
	int	temp;

	left = philo->id;
	right = (philo->id + 1) % philo->table->num_of_philo;
	if (philo->id % 2 == 0)
	{
		temp = left;
		left = right;
		right = temp;
	}
	pthread_mutex_lock(&(philo->table->sim_stop_mutex));
	if (philo->table->sim_stop)
	{
		pthread_mutex_unlock(&(philo->table->sim_stop_mutex));
		return ;
	}
	pthread_mutex_unlock(&(philo->table->sim_stop_mutex));
	pthread_mutex_lock(&(philo->table->forks[left]));
	pthread_mutex_lock(&(philo->table->forks[right]));
	pthread_mutex_lock(&(philo->table->sim_stop_mutex));
	if (!philo->table->sim_stop)
	{
		pthread_mutex_lock(&(philo->table->print_mutex));
		printf("id = %d take the left fork [%d]\n", philo->id + 1, left);
		printf("id = %d take the right fork [%d]\n", philo->id + 1, right);
		printf("id = %d eating time\n", philo->id + 1);
		pthread_mutex_unlock(&(philo->table->print_mutex));
	}
	pthread_mutex_unlock(&(philo->table->sim_stop_mutex));
	pthread_mutex_lock(&(philo->meal_mutex));
	philo->last_meal_time = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&(philo->meal_mutex));
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&(philo->table->forks[left]));
	pthread_mutex_unlock(&(philo->table->forks[right]));
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
		usleep(philo->table->time_to_eat / 2);
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
	end_sim(table);
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
	free(table);
	return (0);
}
