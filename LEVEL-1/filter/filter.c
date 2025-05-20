/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:05:40 by mlaffita          #+#    #+#             */
/*   Updated: 2025/05/16 12:56:03 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 40
#endif
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main(int arc,char **arv)
{
    if(arc !=2)
    {
        return 1;
    }
    char buffer[BUFFER_SIZE];
    char *tmp=NULL;
    char *str=NULL;
    int r;
    int lenght=0;
    int i;
    while((r=read(0,buffer,BUFFER_SIZE))>0)
    {
        str=realloc(tmp,lenght+r+1);
        if(!str)
        {
            free(tmp);
            return 1;
        }
        tmp=str;
        i=0;
        while(i< r)
        {
            tmp[lenght+i]=buffer[i];
            i++;
        }
        lenght += r;
        tmp[lenght]='\0';
    }
    if(!tmp)
        return 0;
    int len =strlen(arv[1]);
    int j;
    i=0;
    while(tmp[i])
    {
        if(strncmp(tmp+i,arv[1],len)==0)
        {
            j=0;
            while(j < len)
            {
                write(1,"*",1);
                j++;
            }
             i += len;
        }
        else
        {
            write(1,&tmp[i++],1);
        }
    }
    free(tmp);
    return 0;
}