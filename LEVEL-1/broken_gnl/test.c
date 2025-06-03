#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif
char *ft_strdup(char *str)
{
    char *copy;
    int len=0;
    while(str[len])
    {
        len++;
    }
    copy=(char*)malloc(sizeof(char)*(len+1));
    if(!copy)
        return NULL;
    len =0;
    while(str[len])
    {
        copy[len]=str[len];
        len++;
    }
    copy[len]='\0';
    return copy;
}
char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int r;
    static int p;
    char line[70000];
    int i=0;
    if(fd < 0 || BUFFER_SIZE<1)
    {
        return NULL;
    }
    while(1)
    {
        if(p>=r)
        {
            r=read(fd,buffer,BUFFER_SIZE);
            p=0;
            if(r<=0)
                break;
        }
        line[i++]=buffer[p++];
        if(buffer[p-1]=='\n')
            break;
    }
    line[i]='\0';
    if(i==0)
        return NULL;
    return (ft_strdup(line));
}

int main()
{
    int fd=open("test.txt",O_RDONLY);
    char *line=get_next_line(fd);
    while(line)
    {
        printf("%s",line);
        line=get_next_line(fd);
        free(line);
    }
    // char *str=get_next_line(fd);
    // printf("%s",line);
    // printf("%s",str);
    close (fd);
}