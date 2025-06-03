/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:06:06 by mlaffita          #+#    #+#             */
/*   Updated: 2025/06/02 14:11:38 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

int match_space(FILE *f)
{
    int get;
    while(isspace((get=fgetc(f))));
    if(get==EOF)
        return -1;
    return (ungetc(get,f),1);
}

int match_char(FILE *f, char c)
{
    int get =fgetc(f);
    if(get==EOF)
        return -1;
    if(get==c)
        return 1;
    ungetc(get,f);
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
    match_space(f);
    char *c= va_arg(ap,char *);
    char get = fgetc(f);
    if(get==EOF)
        return -1;
    *c= get;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
    int *arg= va_arg(ap,int *);
    int s=1;
    int r=0;
    int get=fgetc(f);
    if(get==EOF)
        return -1;
    if(get=='-'||get=='+')
    {
        if(get=='-')
            s=-1;
        int getnext=fgetc(f);
        if (!isdigit(getnext))
        {
            if (getnext != EOF)
            {
                ungetc(getnext, f);
                ungetc(get, f);
            }
            return -1;
        }
        get = getnext;
    }
    else if(!isdigit(get))
        return (ungetc(get,f), -1);
    while(isdigit(get))
    {
        r= r*10+(get - '0');
        get= fgetc(f);
    }
    *arg=r*s;
    if(get != EOF)
        ungetc(get,f);
    return 1;
}

int scan_string(FILE *f, va_list ap)
{
    int get = fgetc(f);
    if(get == EOF)
        return -1;
    char *str = va_arg(ap,char *);
    int i = 0;
    while (!isspace(get) && get != EOF)
    {
        str[i++] = get;
        get = fgetc(f);
    }
    str[i] = '\0';
    if(get != EOF)
        ungetc(get,f);
    return (1);
}

int    match_conv(FILE *f, const char **format, va_list ap)
{
    switch (**format)
    {
        case 'c':
            scan_char(f, ap);
            break;
        case 'd':
            match_space(f);
            scan_int(f, ap);
            break;
        case 's':
            match_space(f);
            scan_string(f, ap);
            break;
        case EOF:
            return -1;
        default:
            return -1;
    }
    return 0;
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
    int nconv = 0;

    // int c = fgetc(f);
    // if (c == EOF)
    //     return EOF;
    // ungetc(c, f);

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            if (match_conv(f, &format, ap) != 1)
                break;
            else
                nconv++;
        }
        else if (isspace(*format))
        {
            if (match_space(f) == -1)
                break;
        }
        else if (match_char(f, *format) != 1)
            break;
        format++;
    }
    if (ferror(f))
        return EOF;
    if(nconv==0 && feof(f))
        return -1;
    return nconv;
}


int ft_scanf(const char *format, ...)
{
    va_list ap;
    va_start(ap,format);
    int ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    return ret;
}

int main()
{
    int n;
    char k[80];
    char l;
    ft_scanf("%d %s %c", &n, k, &l);
    printf("result: %d\n%s\n%c\n", n, k, l);
}