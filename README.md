# coding along automaton impl

Coding along following intriguing videos and customizing their code for myself.

1. [hikalium - 2D Cellular Automaton / THE FIRST CODE](https://www.youtube.com/watch?v=pAS6NtXhKeQ)
2. [[REVIEW] hikalium - 2D Cellular Automaton / THE FIRST CODE](https://www.youtube.com/watch?v=zaStTOm6LI8)

## Usage

- **Press `Enter`** key to move the state.

- Exit by `(^C)`


### Parameter

- **if no argument given**: **Conway's Game of Life-- Acorn**
    
    For instance,

    ```bash
    ./.maton
    ```

- **else**: randomly decide each cell's life (Killed or Alive!)
    
    The intial state is not decided by arguments.

    (due to randomness is decided by the time seed)

    For instance,

    ```bash
    ./.maton 1
    ```

## Build

### Using gcc

#### Normal

```bash
gcc -o .maton maton.c && ./maton
```

#### With Debugger

```bash
gcc -g -o .maton maton.c
```

In this case, this can be runed by `gdb` command

```
gdb .maton
```

and type `run` to gdb prompt.

