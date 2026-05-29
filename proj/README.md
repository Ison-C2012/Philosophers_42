*This project has been created as part of the 42 curriculum by keitotak.*
# Philosophers

## Description

This project is a simulation of the classic **Dining Philosophers Problem**, implemented in C with a focus on concurrency and thread safety.

A number of philosophers sit around a circular table. Each philosopher alternates between thinking, eating, and sleeping. To eat, a philosopher must pick up two forks — one on their left and one on their right. There are exactly as many forks as philosophers, which means access to forks must be carefully managed to avoid race conditions and deadlocks.

The program is given the following parameters at launch:

| Argument | Description |
|---|---|
| `number_of_philosophers` | The number of philosophers (and forks) at the table |
| `time_to_die` | Time (ms) after which a philosopher dies if they haven't started eating |
| `time_to_eat` | Time (ms) a philosopher spends eating |
| `time_to_sleep` | Time (ms) a philosopher spends sleeping |
| `[number_of_times_each_philosopher_must_eat]` | *(Optional)* Simulation stops when all philosophers have eaten this many times |

**Goal:** Implement the simulation so that no philosopher dies — while learning the fundamentals of concurrent programming (threads, mutexes, race conditions) in C.

---

## Instructions

### Compilation

First of all:

```bash
cd philo/
```

To build the program:

```bash
make
```

### Execution

To run the simulation:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Example:**

```bash
./philo 5 800 200 200
./philo 5 800 200 200 7
```

### Cleanup

To remove object files:

```bash
make clean
```

To remove object files and the compiled binary:

```bash
make fclean
```

To recompile from scratch:

```bash
make re
```

---

## Resources

The following references were used to build understanding of the project and concurrency concepts:

### Tools & Visualizers

- [Philosophers Visualizer](https://nafuka11.github.io/philosophers-visualizer/) — A visual debugger for checking philosopher simulation behavior

### Articles & Documentation

- [Philosophers article by yliu (Qiita)](https://qiita.com/42yliu/items/86d16cdbc584c250ca6e) — A practical walkthrough of the philosophers project, understanding why dead lock must not occur
- Manual pages for C library functions (`man pthread_create`, `man pthread_mutex_init`, etc.)

### Books

- *Concurrency in Go* — Katherine Cox-Buday, O'REILLY Japan, 2018 — conceptual foundation for understanding concurrency patterns especially dead lock and resource starvation

---

### How AI Was Used

**AI tools used:** Gemini 3.5 Flash, Claude Sonnet 4.6 (Anthropic)

AI assistance was used in the following areas:

- **Understanding development tools** — explanations of build systems, compiler flags, and debugging utilities
- **Test code creation** — generating shell scripts for automated testing of edge cases
- **Code review** — identifying potential race conditions, logic errors, and style improvements
- **Project interpretation** — clarifying the rules and expected behavior of the dining philosophers simulation
- **Debugging guidance** — learning how to read and interpret Helgrind (Valgrind) error messages related to thread safety
- **README creation** — Claude Sonnet 4.6 was used to write and format this README, structuring the content into clear sections with a parameter table, usage examples, and organized resource categories
