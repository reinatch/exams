#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

<<<<<<< HEAD
int main(int ac, char **av)
{
    if(ac != 4)
        return 0;
    int w = atoi(av[1]), h = atoi(av[2]), iter = atoi(av[3]);
    int *board = calloc((size_t) h*w, sizeof(int));
    int *clone = calloc((size_t) h*w, sizeof(int));
    int x=0, y=0, pen=0;
    char c;

    while (read(0, &c, 1) == 1)
    {
        if(c== 'w' && y >= 0)
            y--;
        else if(c== 's' && y < h-1)
            y++;
        else if(c== 'a' && x >= 0)
            x--;
        else if(c== 'd' && x < w-1)
            x++;
        else if(c == 'x')
            pen = !pen;
        if(pen)
            board[y*w+x] = 1;
    }
    for(int t = 0; t < iter; t++){
        for(int i = 0; i < h; i++){
            for(int j = 0; j < w; j++){
                int n = 0;
                for (int a = -1; a <= 1; a++)
                    for (int b = -1; b <= 1; b++)
                        if((a || b) && i + a >= 0 && i + a < h && j + b >= 0 && j + b < w )
                            n += board[(i +a) * w + (j + b)];
                clone[i*w+j] = (board[i*w+j] && (n == 2 || n == 3)) || (!board[i*w+j] && n == 3);
            }
        }
        for(int i = 0; i < h; i++)
            for(int j = 0; j < w; j++)
                board[i*w+j] = clone[i*w+j];

    }
    for (int i = 0; i < h; i++){
        int alive = 0;
        for (int j = 0; j < w; j++)
            if(board[i*w+j])
                alive = 1;
        if(!alive) {
            putchar('\n');
            continue;
        }
        for (int j = 0; j < w; j++)
            putchar(board[i*w+j] ? 'O' : ' ');
=======
int main(int ac, char **av){
    if (ac != 4)
        return 0;
    int w = atoi(av[1]), h = atoi(av[2]), iter = atoi(av[3]);
    int *board = calloc((size_t)h*w,sizeof(int));
    int *clone = calloc((size_t)h*w,sizeof(int));
    int x=0,y=0,pen=0,alive=0;
    char c;
    
    
    while(read(0, &c, 1)==1){
        if (c=='w' && y >=0) y--;
        else if (c=='s' && y < h-1) y++;
        else if (c=='a' && x >=0) x--;
        else if (c=='d' && x < w-1) x++;
        else if (c=='x') pen = !pen;
        if(pen)
            board[y*w+x] = 1;     
    }

    for (int t=0;t<iter;t++){
        for (int i=0;i<h;i++){
            for (int j=0;j<w;j++){
                int n = 0;
                for (int a = -1; a <= 1; a++)
                    for (int b = -1; b <= 1; b++)
                        if((a||b) && i+a>=0 && i+a<h && j+b>=0 && j+b<w)
                            n+= board[(i+a) * w + (j+b)];
                clone[i*w+j] = (board[i*w+j] && (n == 2 || n ==3)) || (!board[i*w+j] && n == 3);
                    
            }

        }
        for (int i =0;i<h;i++)
            for (int j =0;j<w;j++)
                board[i*w+j] = clone[i*w+j];
    }
    for (int i=0;i<h;i++){
       
        alive =0;
        for (int j=0;j<w;j++)
            if(board[i*w+j])
                alive =1;
        if(!alive){putchar('\n'); continue;}
        for(int j=0;j<w;j++)
            putchar(board[i*w+j] ? '0' : ' ');
>>>>>>> 1adbcdf (exam06)
        putchar('\n');
    }
    free(board);
    free(clone);
    return 0;
<<<<<<< HEAD
=======
    
>>>>>>> 1adbcdf (exam06)
}