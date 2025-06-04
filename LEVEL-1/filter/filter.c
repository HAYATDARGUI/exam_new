/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:05:40 by mlaffita          #+#    #+#             */
/*   Updated: 2025/06/04 14:16:31 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int ft_strncmp(char *s1,char *s2,int n)
{
    int i=0;
    while(i<n&& (s1[i] ||s2[i]))
    {
        if(s1!=s2)
            return (s1[i]-s2[i]);
        i++;
    }
    return 0;
}
int main(int arc,char **arv)
{
    char buffer[BUFFER_SIZE];
    char *str;
    char *tmp;
    int r;
    int lenght=0;
    int i=0;
    if (arc != 2)
		return (1);
    while((r=read(0,buffer,BUFFER_SIZE))>0)
    {
        str=realloc(tmp,lenght+r+1);
        if(!str)
        {
            free(tmp);
            return 0;
        }
        tmp=str;
        i=0;
        if(i< r)
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
        if(ft_strncmp(tmp+i,arv[1],len)==0)
        {
            j=0;
            while(j<len)
            {
                write(1,"*",1);
                j++;
            }
            i=+len;
        }
        else
            write(1,&tmp[i++],1);
    }
    tmp[i]='\0';
    free(tmp);
}