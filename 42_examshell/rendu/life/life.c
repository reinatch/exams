#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int ac, char **av)
{
    (void)ac;
    int w = atoi(av[1]), h = atoi(av[2]), iter = atoi(av[3]);
    int board[h][w], next[h][w], x = 0, y = 0, pen = 0;
    char c;
    if (ac < 4) {
        write(2, "Usage: ./life width height iter\n", 31);
        return 1;
    }
    for(int i = 0; i < h; i ++)
        for(int j = 0; j < w; j ++)
            board[i][j] = 0;

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
            board[y][x] = 1;
    }

    for (int t = 0; t < iter; t++ ){
        for(int i = 0; i < h; i ++){
            for(int j = 0; j < w; j ++){
                int n = 0;
                for(int a = -1; a <= 1; a ++)
                    for(int b = -1; b <= 1; b ++)
                        if((a || b) && i + a >= 0 && i + a < h && j + b >= 0 && j+b < w)
                            n += board[i + a][j + b];
                next[i][j] = (board[i][j] && (n == 2 || n == 3)) || (!board[i][j] && n == 3);
            }
        }
        for(int i = 0; i < h; i ++)
            for(int j = 0; j < w; j ++)
                board[i][j] = next[i][j];
    }

    for(int i = 0; i < h; i ++){
        for(int j = 0; j < w; j ++)
            putchar(board[i][j] ? 'O' : ' ');
        putchar('\n');
    }
    return 0;
}
