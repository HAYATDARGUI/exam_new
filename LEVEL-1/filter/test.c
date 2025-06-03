#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main(int arc,char **arv)
{
    char buffer[42];
    char *tmp;
    char *s;
    int r;
    int i=0;
    int len =0;
    if(arc!=2)
        return 0;
    while((r=read(0,buffer,sizeof(buffer)))>0)
    {
        s=realloc(tmp,len +r + 1);
        if(!s)
        {
            free(tmp);
            return 0;
        }
        tmp=s;
        while(i<r)
        {
            tmp[len+i]=buffer[i];
            i++;
        }
        len+=r;
        tmp[len]='\0';
    }
    int j=0;
    i=0;
    int lenght=strlen(arv[1]);
    while(tmp[i])
    {
        if(strncmp(tmp+i,arv[1],lenght)==0)
        {
            j=0;
            while(j<lenght)
            {
                write(1,"*",1);
                j++;
            }
            i+=lenght;
        }
        else
            write(1,&tmp[i++],1);
    }
    free(tmp);
}