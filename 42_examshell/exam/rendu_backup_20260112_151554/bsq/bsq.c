#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int min3(int a, int b, int c){return a < b ? (a < c ? a : c) : (b < c ? b : c);}
void clean_map(char **map, int h, FILE *file) {
    fprintf(stderr, "mapp error\n");
    for (int i = 0; i < h; i++)
        if(map && map[i]) free(map[i]);
    free(map);
    if (file != stdin)
        fclose(file);
};

void process_file(char *filename){
    int h =0, w=0, max=0,maxi=0, maxj=0, *buffer;
    char empty, obstacle, full, **map;
    size_t len = 0;
    ssize_t read = 0;
    FILE *file = filename ? fopen(filename, "r") : stdin;
    if(!file) {fprintf(stderr, "mapp error\n"); return;}
    if(fscanf(file, "%d %c %c %c\n", &h, &empty, &obstacle, &full) != 4 || h <=0) {
        fprintf(stderr, "mapp error\n");
        if (file != stdin)
            fclose(file);
        return;
    }
    map = calloc((size_t)h, sizeof(char*));
    if(!map) {clean_map(map, h, file); return;}
    for(int i=0; i< h; i++){
        read = getline(&map[i], &len, file);
        if (read == -1) {clean_map(map, h, file); return;}
        if (map[i][read -1] == '\n') map[i][read -1] = 0;
        if( i == 0) w = strlen(map[i]);
        if ((int)strlen(map[i]) != w) {clean_map(map, h, file); return;}
        for(int j = 0; j < w; j++)
            if(map[i][j] != empty && map[i][j] != obstacle) {
                clean_map(map, h, file); return;
            }
        
    }
    if (empty == obstacle || empty == full || obstacle == full) {clean_map(map, h, file); return;}
    buffer = calloc((size_t)h*w, sizeof(int));

    for(int i=0; i< h; i++)
        for(int j = 0; j < w; j++) {
            if (map[i][j] == obstacle) buffer[i*w+j] = 0;
            else if (i == 0 || j == 0) buffer[i*w+j] = 1;
            else buffer[i*w+j] = 1 + min3(buffer[(i-1)*w+j] , buffer[i*w+(j - 1)] , buffer[(i-1)*w+(j - 1)]);
            if (buffer[i*w+j] >  max) {
                max = buffer[i*w+j];
                maxi = i;
                maxj = j;
            }
        }
    for(int i=maxi - max + 1; i< maxi; i++)
        for(int j = maxj - max + 1; j < maxj; j++) 
            map[i][j] = full;

    for(int i=0; i< h; i++)
        puts(map[i]);
    for(int i=0; i< h; i++)
        free(map[i]);
    free(map); free(buffer);
    if(file != stdin)
         fclose(file);
    return;
    
}
// int main(int ac, char **av){

//     if(ac == 1) process_file(NULL);
//     else for(int i=1;i<ac;i++) process_file(av[i]);
//     return 0;
// }