/*
 * life.c
 *
 * Simulate Conway's Game of Life on a board built interactively from stdin
 * drawing commands. The program accepts three command-line arguments:
 *     ./life width height iterations
 *
 * The initial board is drawn by sending characters to stdin that control a
 * pen starting at the top-left corner (0,0):
 *   - w/a/s/d : move up/left/down/right (within bounds)
 *   - x       : toggle pen (lift/lower)
 * When pen is down, moving writes a live cell (value 1) at the pen position.
 *
 * Implementation notes:
 * - Uses dynamic allocation for the board and clone buffers as a flat
 *   row-major `int *` buffer. This avoids stack overflows and is portable.
 * - Indexing of the flat buffers uses the explicit expression `(i * w + j)`.
 * - The simulation runs `iter` generations. For each cell we count the 8
 *   neighbors (cells adjacent in the 3x3 window excluding the center) and
 *   apply the standard Game of Life rules to produce the next state.
 * - Allowed functions (per subject): `atoi, read, putchar, malloc/calloc/realloc/free`.
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int ac, char **av)
{
    /* Validate arguments before using av[] */
    if (ac < 4) {
        write(2, "Usage: ./life width height iter\n", 31);
        return 1;
    }
    int w = atoi(av[1]);
    int h = atoi(av[2]);
    int iter = atoi(av[3]);
    if (w <= 0 || h <= 0 || iter < 0) {
        write(2, "Usage: ./life width height iter\n", 31);
        return 1;
    }

    /* Allocate flat buffers on the heap */
    int *board = calloc((size_t)h * w, sizeof(int));
    int *clone = calloc((size_t)h * w, sizeof(int));
    if (!board || !clone) {
        if (board) free(board);
        if (clone) free(clone);
        return 1;
    }

    /* Read drawing commands from stdin to initialize the board */
    int x = 0, y = 0, pen = 0;
    char c;
    while (read(0, &c, 1) == 1){
        if(c == 'w' && y > 0)
            y--;
        else if(c == 's' && y < h-1)
            y++;
        else if(c == 'a' && x > 0)
            x--;
        else if(c == 'd' && x < w-1)
            x++;
        else if(c == 'x')
            pen = !pen;
            if(pen)
                board[y * w + x] = 1;
    }

    /* Simulate `iter` generations of Conway's Game of Life */
    for (int t = 0; t < iter; t++ ){
        for(int i = 0; i < h; i ++){
            for(int j = 0; j < w; j ++){
                /* Count the 8 neighbors around (i,j) */
                int n = 0;
                for(int a = -1; a <= 1; a ++)
                    for(int b = -1; b <= 1; b ++)
                        if((a || b) && i + a >= 0 && i + a < h && j + b >= 0 && j+b < w)
                                n += board[(i + a) * w + (j + b)];
                int cur = board[i * w + j];
                /* Apply Game of Life rules */
                    clone[i * w + j] = (cur && (n == 2 || n == 3)) || (!cur && n == 3);
            }
        }
        /* Move clone -> board for the clone generation */
        for(int i = 0; i < h; i ++)
            for(int j = 0; j < w; j ++)
                    board[i * w + j] = clone[i * w + j];
    }

    /* Print the final board: alive -> '0', dead -> ' ' (space) */
    for(int i = 0; i < h; i ++){
        for(int j = 0; j < w; j ++)
                putchar(board[i * w + j] ? '0' : ' ');
        putchar('\n');
    }

    free(board);
    free(clone);
    return 0;
}
