/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:07:30 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/22 22:12:05 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX_TIME_SECONDS 5

typedef struct s_data
{
	int	*counter;
	pthread_mutex_t	*mutex;
}	t_data;

// Function executed by thread 1 (increment)
void *increment_thread(void *arg) {
    int *counter = ((t_data *) arg) -> counter;
	pthread_mutex_t *mutex = ((t_data *) arg) -> mutex;

    struct timeval start_time;
    gettimeofday(&start_time, NULL);
    struct timeval current_time;
    while (1) {
        gettimeofday(&current_time, NULL);
        if ((current_time.tv_sec - start_time.tv_sec) >= MAX_TIME_SECONDS) {
            break;
        }
        pthread_mutex_lock(mutex); // Lock the mutex before accessing the counter
        (*counter)++;
        printf("Increment thread: Counter = %ld\n", *counter);
        pthread_mutex_unlock(mutex); // Unlock the mutex
        usleep(50000); // Sleep for 0.5 seconds
    }
    pthread_exit(NULL); // Exit the thread
}

// Function executed by thread 2 (decrement)
void *decrement_thread(void *arg) {
    int *counter = ((t_data *) arg) -> counter;
	pthread_mutex_t *mutex = ((t_data *) arg) -> mutex;
    struct timeval start_time;
    gettimeofday(&start_time, NULL);
    struct timeval current_time;
    while (1) {
        gettimeofday(&current_time, NULL);
        if ((current_time.tv_sec - start_time.tv_sec) >= MAX_TIME_SECONDS) {
            break;
        }
        pthread_mutex_lock(mutex); // Lock the mutex before accessing the counter
        (*counter)--;
        printf("Decrement thread: Counter = %ld\n", *counter);
        pthread_mutex_unlock(mutex); // Unlock the mutex
        usleep(40000); // Sleep for 0.75 seconds
    }
    pthread_exit(NULL); // Exit the thread
}

int main() {
    int *counter = (int *)malloc(sizeof(int)); // Dynamically allocate memory for the shared variable
    if (counter == NULL) {
        perror("malloc");
        return 1;
    }

	t_data *data;

	pthread_mutex_t *mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutex, NULL);
	data = malloc(sizeof(t_data));
	data -> counter = counter;
	data -> mutex = mutex;
    *counter = 0; // Initialize the counter

    //pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex for protecting access to counter

    pthread_t inc_thread, dec_thread; // Thread identifiers

    // Create increment thread
    if (pthread_create(&inc_thread, NULL, increment_thread, (void *)data) != 0) {
        perror("pthread_create");
        return 1;
    }

    // Create decrement thread
    if (pthread_create(&dec_thread, NULL, decrement_thread, (void *)data) != 0) {
        perror("pthread_create");
        return 1;
    }

    // Wait for increment thread to finish
    if (pthread_join(inc_thread, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    // Wait for decrement thread to finish
    if (pthread_join(dec_thread, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    free(counter); // Free memory allocated for counter

    printf("Main thread: Threads have finished execution.\n");

    return 0;
}

