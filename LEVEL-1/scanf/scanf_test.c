
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int match_space(FILE *f)
{
    char c;
    while((c=fgetc(f))!=EOF)
    {
        if(!isspace(c))
            return (ungetc(c,f),1);
    }
    return -1;
}
int match_char(FILE *f, char c)
{
   return(c=fgetc(f));
}

int scan_char(FILE *f, va_list ap)
{
   char c=fgetc(f);
   char *s=va_arg(ap,char*);

   if(c==EOF)
        return 0;
    *s=c;
    return 1;
}
long long ft_itol(char *str)
{
    long i=0;
    int s=1;
    long r=0;
    while(isspace(str[i]) ||str[i]=='\n' || str[i]=='\t')
        i++;
    if(str[i]=='+' ||str[i]=='-')
    {
        if(str[i]=='-')
        {
            s=-1;
            i++;
        }
        i++;
    }
    while(str[i]>='0' && str[i]<='9')
    {
        r =r*10+(str[i]-'0');
        i++;
    }
    return (r*s);
}


int scan_int(FILE *f, va_list ap)
{
	int c;
    char buffer[42];
    int *s=va_arg(ap,int *);
    int i=0;
    while((c=fgetc(f))!=EOF && isdigit(c) && i< sizeof(buffer))
        buffer[i++]=c;
    if(i>0)
    {
        buffer[i]=0;
        *s=ft_itol(buffer);
        if(c!=EOF)
            return 1;
    }
    return 0;
}

int scan_string(FILE *f, va_list ap)
{
	int c;
    char *s=va_arg(ap,char *);
    int i=0;
    while((c=fgetc(f))!=EOF && !isspace(c) && i< 99)
        s[i++]=c;
    s[i]=0;
    if(i>0)
    {
        return 1;
    }
    return 0;
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

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
	int nb;
	char c;
	char str[100];

	ft_scanf("%d %c %s", &nb, &c, str);
	printf("%d %c %s",nb, c, str);
}