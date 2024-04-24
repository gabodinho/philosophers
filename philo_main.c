

#include "philo.h"

int main(int argc, char *argv[])
{
    if (input_check(argc, argv))
        write(1, "error\n", 6);
    else
        printf("success\n");
    return (0);
}