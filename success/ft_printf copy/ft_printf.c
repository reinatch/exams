#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

void put_string(char *str, int *len){
    int i = 0;

    if (!str)
        str = "(null)";
    while (str[i])
    {
        *len += write(1, &str[i], 1);
        i++;

    }
}
void put_number(long long number, int base, int *len){
    char *hex = "0123456789abcdef";

    if (number < 0)
    {
        number *= -1;
        *len += write(1, "-", 1);
    }
    if(number >= base)
        put_number((number/base), base, len);
    *len += write(1, &hex[number % base], 1);
}



int ft_printf(const char *format, ... )
{
    int len = 0;
    int i = 0;
    va_list ptr;

    va_start(ptr, format);
    while (format[i] != '\0') 
    {

        if (format[i] != '%')
            len += write(1, &format[i], 1);
        else if ((format[i] == '%') && (format[i+1]))
        {
            i++;
            if (format[i] == 's')
                put_string(va_arg(ptr, char *), &len);
            else if (format[i] == 'd')
                put_number(va_arg(ptr, int), 10, &len);
            else if (format[i] == 'x')
                put_number(va_arg(ptr, unsigned int), 16, &len);

        }
        i++;

    }

    return (va_end(ptr), len);

}


// int main (int ac, char **av)
// {
//     if (ac = 2)
//         ft_printf("%s %d %x",av[1], 42, 42);
//     return 0;
// }

