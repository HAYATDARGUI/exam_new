#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif
int main(int arc,char **arv)
{
    char buffer[BUFFER_SIZE];
    int r;
    char *s;
    char *tmp;
    int lenght=0;
    int i;
    if(arc!= 2)
        return 1;
    while((r=read(0,buffer,BUFFER_SIZE))>0)
    {
        s=realloc(tmp,lenght+r+1);
        if(!s)
        {
            free(tmp);
            return 0;
        }
        tmp=s;
        i=0;
        while(i < r)
        {

            tmp[lenght+i]=buffer[i];
            i++;
        }
        lenght+=r;
        tmp[lenght]='\0';
    }
    i=0;
    int j;
    int len=strlen(arv[1]);
    while(tmp[i])
    {
        if(strncmp(tmp+i,arv[1],len)==0)
        {
            j=0;
            while(j<len)
            {
                write(1,"*",1);
                j++;
            }
            i+=len;
        }
        else
            write(1,&tmp[i++],1);
    }
    free(tmp);
    return 0;
}