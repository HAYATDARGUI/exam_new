/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brocken_gnl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:16:12 by hdargui           #+#    #+#             */
/*   Updated: 2025/05/17 15:19:54 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int r;
    static int p;
    char line[70000];
    int i=0;
    if(fd < 0 && BUFFER_SIZE <1)
        return NULL;
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
    line[p]='\0';
    if(i==0)
        return NULL;
    return (ft_strdup(line));
}