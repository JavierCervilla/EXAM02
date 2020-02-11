/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javi <javi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 22:10:21 by javi              #+#    #+#             */
/*   Updated: 2020/02/10 20:38:15 by javi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdarg.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
int ft_type(char c)
{
    if (c == 'd' || c == 'x' || c == 's')
        return (1);
    return (0);
}

char *ft_ltoabase(long int num, int base)
{
    long int aux;
    int digits = 1;
    char *str;
    aux = num;

    while (aux /= base)
        digits++;
    if (!(str = (char *)malloc(sizeof(char) * (digits + 1))))
        return (NULL);
    str[digits] = '\0';
    while (digits--)
    {
        if (base == 10)
        {
            str[digits] = num % base + '0';   
        }
        if (base == 16)
        {
            if (num % base < 10)
            {
                str[digits] = num % base + '0';
            }
            if (num % base > 9)
            {
                str[digits] = num % base + 'W';
            }
        }
        num = num / base;
    }
    return(str);
}

int ft_printeger(va_list ap, int width, int precision)
{
    int spaces = -1;
    int zeros = -1;
    long int num = (long int)va_arg(ap, int);
    long int aux = num;
    int lenstr = 0;
    size_t len = 0;
    char *str = ft_ltoabase(num, 10);

    while(str[lenstr])
        lenstr++;
    
    if (precision > lenstr)
    {
        zeros = precision - lenstr;
    }
    else
        precision = lenstr;
    if (num < 0)
    {
        num = num * -1;
        width++;
    }
    if (width > precision)
        spaces = width - precision;
    while (spaces > 0)
    {
        len += write(1, " ",1);
        spaces--;
    }
    if (num < 0)
        len += write(1,"-",1);
    while (zeros > 0)
    {
        len += write(1,"0",1);
        zeros--;
    }
    len += write(1,&*str,lenstr);
}

int ft_printf(const char *format, ...)
{
    va_list ap;
    int precision = 0;
    int width = 0;
    int len = 0;

    va_start(ap,format);
    while (*format /*&&  *format != '%'*/)
    {
        if (*format == '%')
        {
            format ++;
            while (*format <= '9' && *format >= '0')
            {
                width = width * 10 + (*format - '0');
                format++;
            }
            if (*format == '.')
            {
                format++;
                while (*format <= '9' && *format >= '0')
                {
                    precision = precision * 10 + (*format - '0');
                    format++;
                }
            }
            if (*format == 'd')
            {
                len += ft_printeger(ap, width, precision);
                format++;
            }
            /*if (*format == 's')
                return (len += ft_printstr(ap, width, precision));
            if (*format == 'x')
                return (len += ft_printhex(ap, width, precision));*/
        }
        else
        {
            len += write(1,&*format,1);
            format++;
        }
    }
    return len;
}

int main()
{
    ft_printf("primera prueba:%5.10d\n",50);
    printf("primera prueba:%5.10d\n",50);
}