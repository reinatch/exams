#include <unistd.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
    int len = 0;

    while (str[len] != '\0') 
        len++;

    return len;
}

// int main(int ac, char **av)
// {
//     if (ac == 2) 
//     {
//         printf( "%d", ft_strlen(av[1]));
//     }


//     return 0;
// }




