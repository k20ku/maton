#include <stdio.h>
#include <stdlib.h>
#include <time.h>

# define SIZE 32
/*
penta-deca-athlon

# # _
# _ _ -> born! :2
_ _ _

# # _
# # _ -> alive! :3
_ _ _

_ # _
_ # _ -> dead! (too few)
_ _ _

_ # _
# # # -> dead! (too many)
_ # _

*/

struct Map {
	char cell[SIZE][SIZE];
};

void print_map(struct Map *map) {
	for (int y=0; y < SIZE; y++) {
		for (int x=0; x < SIZE; x++) {
			putchar(map->cell[y][x] ? '#': ' ');
			putchar(' ');
		}
		putchar('\n');
	}
}

void cursor_up_by(int n) {
    printf("\033[%dA", n);
}

struct Map current;
struct Map next;

/*
    6x6
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},

    10x10
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

*/

#define X 10
#define Y 10
char init[X][Y] = {
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int dy[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
int dx[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};

int main(int argc, char *argv[]) {
	// init
    // https://en.cppreference.com/w/c/language/main_function.html#Parameters
    // program NULL -> argc 2
    if(argc < 2) {
        for (int y = 0; y < 10; y++) {
            for (int x = 0; x < 10; x++) {
                current.cell[y][x] = init[y][x];
            }
        }
    } else {
        unsigned int seed = (unsigned int)time(NULL);
        srand(seed);
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                current.cell[y][x] = (rand() & 1);
            }
        }
    }  


	// 
	for (;;) {
		// Print
		print_map(&current);
		// State transition from current to next
		for (int y = 0; y < SIZE; y++) {
			for (int x = 0; x < SIZE; x++){ // 0b_0000_0000 (0x00) to 0b_0001_1111 (0x1F)
				int  count = 0;
				// 範囲外参照を防ぎたいが，割り算は負の数の余りが環境依存 & 重いのでbit演算
				// 32x32, (0, 0) の左上 = (31, 31)
				// 0x00 -1 => 0xFF, 0xFF & 0x1F => 0x1F
				// 0b_0001_1111 下4bitでぐるぐるすることを期待する
				// -5 % 3 -> -2 (Java), 1
				// 0 1 2
				// 3 4 5 <- 4 が自分
				// 6 7 8
                for (int pos = 0; pos < 9; pos++) {
                    if (pos == 4) continue;
                    count += current.cell[(y + dy[pos]) & (SIZE -1)][(x + dx[pos]) & (SIZE- 1)];
                }

				if (current.cell[y][x]) {
					// current == alive, dead or alive?
                    // born! or alive!
                    if (count == 2 || count == 3) {
                        next.cell[y][x] = 1;
                    } else {
                        // keep dead due to too few or too many
                        next.cell[y][x] = 0;
                    }
				} else {
				    // current == dead, dead or alive?
                    // keep alive!
                    if (count == 3) {
                        next.cell[y][x] = 1;
                    } else {
                        // dead due to too few or many
                        next.cell[y][x] = 0;
                    }
				}
			}	
		}

        current = next;
		int c = getchar();
        cursor_up_by(SIZE + 1);
        fflush(stdout);
	}
	return 0;
}
