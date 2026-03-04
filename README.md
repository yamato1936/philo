*This project has been created as part of the 42 curriculum by toyamagu.*

# Philosophers

## Description
`philo` is the mandatory part of the 42 Philosophers project.
It simulates the dining philosophers problem with:
- one thread per philosopher
- one mutex per fork
- mutex-protected shared state (`stop`, log output, meal data)

The simulation ends when:
- one philosopher dies, or
- all philosophers ate enough times (when the optional argument is provided)

## Instructions
### Build
```sh
make
```

### Run
```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Examples:
```sh
./philo 5 800 200 200
./philo 5 800 200 200 7
```

### Clean
```sh
make clean
make fclean
make re
```

## Resources
- 42 subject: `philo.pdf`
- POSIX threads documentation (`pthread_create`, `pthread_mutex_*`, `pthread_join`)
- `gettimeofday(2)` and `usleep(3)` manual pages
- Valgrind (`memcheck`, `helgrind`) for leak/race checks

AI usage for this project:
- used to review structure/readability and refactor function boundaries
- used to prepare edge-case test scenarios for mandatory evaluation items
- all generated/refactored code was manually verified with `make`, `norminette`,
  runtime tests, and valgrind checks
