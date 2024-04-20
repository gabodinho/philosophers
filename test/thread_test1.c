/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_test1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 22:03:07 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/20 22:03:18 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Function executed by thread 1
void *thread1_function(void *arg) {
    usleep(1000); // Sleep for 1 millisecond
    printf("Thread 1: Hello from thread 1!\n");
    pthread_exit(NULL); // Exit the thread
}

// Function executed by thread 2
void *thread2_function(void *arg) {
    usleep(1000); // Sleep for 1 millisecond
    printf("Thread 2: Hello from thread 2!\n");
    pthread_exit(NULL); // Exit the thread
}

int main() {
    pthread_t thread1, thread2; // Thread identifiers

    // Create thread 1
    if (pthread_create(&thread1, NULL, thread1_function, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    // Create thread 2
    if (pthread_create(&thread2, NULL, thread2_function, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    // Wait for thread 1 to finish
    if (pthread_join(thread1, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    // Wait for thread 2 to finish
    if (pthread_join(thread2, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    printf("Main thread: Threads have finished execution.\n");

    return 0;
}

