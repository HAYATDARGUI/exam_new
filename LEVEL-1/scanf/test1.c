#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int get;
    while(isspace((get=fgetc(f))) && get!=EOF);
    if(get==EOF)
        return -1;
    ungetc(get,f);
    return 1;
}

int match_char(FILE *f, char c)
{
    int get= fgetc(f);
    if(get==EOF)
        return -1;
    if(get==c)
        return 1;
    ungetc(get,f);
    return 0;
}

int scan_char(FILE *f, va_list ap)
{
    char *c=va_arg(ap,char *);
    int get =fgetc(f);
    if(get==EOF)
        return -1;
    *c=get;
    return 1;
}

int scan_int(FILE *f, va_list ap)
{
   int *arg=va_arg(ap,int *);
   int get=fgetc(f);
   int r=0;
   int s=1;
   int i=0;
   if(get=='-' || get=='+')
   {    
        if(get=='-')
            s=-1;
        int getnext=fgetc(f);
        if(isdigit(getnext))
            get=getnext;
        else
        {
            ungetc(getnext,f);
            ungetc(get,f);
            return -1;
        }
   }
   else if(!isdigit(get))
        return (ungetc(get,f),-1);
    while(isdigit(get))
    {
        r=r *10+(get-'0');
        get=fgetc(f);
    }
    if(get!=EOF)
        ungetc(get,f);
    *arg=r*s;
    return 1;
}

int scan_string(FILE *f, va_list ap)
{
   char *str=va_arg(ap,char *);
   int get=fgetc(f);
   int i=0;
   int count=0;
   while(!isspace(get) && get!=EOF)
   {
        str[i++]=get;
        count++;
        get=fgetc(f);
   }
   if(count==0)
   {
        if(get==EOF)
            return -1;
        ungetc(get,f);
        return -1;
   }
   str[i]='\0';
   ungetc(get,f);
   return 1;
}


int    match_conv(FILE *f, const char **format, va_list ap)
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
    if (nconv == 0 && feof(f))
		return EOF;
    return nconv;
}


int ft_scanf(const char *format, ...)
{
    va_list ap;
    va_start (ap,format);
    int ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    return ret;
}
int main(void)
{
	int a = 0;
	int b = 1;
	char c[100] = "g";

	printf("Enter a:\n");
	ft_scanf("%d %s %d", &a, c, &b);

	printf("\na: %d", a);
	printf("\nc: %s", c);
	printf("\nb: %d\n", b);
	return 0;
}