#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define IDX(i,j,w) ((i) * (w) + (j))

int main(int ac, char **av)
{
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

    int *board = calloc((size_t)h * w, sizeof(int));
    int *next = calloc((size_t)h * w, sizeof(int));
    if (!board || !next) {
        if (board) free(board);
        if (next) free(next);
        return 1;
    }

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
            board[IDX(y, x, w)] = 1;
    }

    for (int t = 0; t < iter; t++ ){
        for(int i = 0; i < h; i ++){
            for(int j = 0; j < w; j ++){
                int n = 0;
                for(int a = -1; a <= 1; a ++)
                    for(int b = -1; b <= 1; b ++)
                        if((a || b) && i + a >= 0 && i + a < h && j + b >= 0 && j+b < w)
                            n += board[IDX(i + a, j + b, w)];
                int cur = board[IDX(i, j, w)];
                next[IDX(i, j, w)] = (cur && (n == 2 || n == 3)) || (!cur && n == 3);
            }
        }
        for(int i = 0; i < h; i ++)
            for(int j = 0; j < w; j ++)
                board[IDX(i, j, w)] = next[IDX(i, j, w)];
    }

    for(int i = 0; i < h; i ++){
        for(int j = 0; j < w; j ++)
            putchar(board[IDX(i, j, w)] ? 'O' : ' ');
        putchar('\n');
    }

    free(board);
    free(next);
    return 0;
}
