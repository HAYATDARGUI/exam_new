/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdargui <hdargui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:12:44 by mlaffita          #+#    #+#             */
/*   Updated: 2025/06/04 14:25:22 by hdargui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> 
#include <stdio.h>
int numberdejavu(int *tabnumbers,int indextab,int *tabfinal,int indextabf)
{
    int i=0;
    int j=0;
    while(i <indextab && j<indextabf)
    {
        if(tabnumbers[i]!=tabfinal[j])
            i++;
        if(tabnumbers[i]==tabfinal[j])
        {
            i++;
            j++;
        }
    }
    if(j==indextabf)
        return 1;
    return 0;
}
void powerset(int target,int *tabnumbers,int indextab,int *tabfinal,int indextabf,int *usednumber)
{
    if(target==0)
    {
        if(numberdejavu(tabnumbers,indextab,tabfinal,indextabf)==1)
        {
            for(int i=0;i<indextabf;i++)
                printf("%d",tabfinal[i]);
            printf("\n");
        }
        return ;
    }
    for(int i=0;i< indextab;i++)
    {
        if(usednumber[i]==0)
        {
            usednumber[i]=1;
            target-=tabnumbers[i];
            tabfinal[indextabf]=tabnumbers[i];
            powerset(target,tabnumbers,indextab,tabfinal,indextabf+1,usednumber);
            usednumber[i]=0;
            target+=tabnumbers[i];
        }
    }
}
int main(int arc,char **arv)
{
    if(arc < 3)
        return -1;
    int target =atoi(arv[1]);
    int indextab= arc-2;
    int *tabnumbers=malloc(sizeof(int)*indextab);
    if(!tabnumbers)
    {
        exit(1);
    }
    for(int i=0;i < indextab;i++)
    {
        tabnumbers[i]=atoi(arv[i+2]);
    }
    int *tabfinal=malloc(sizeof(int)*indextab);
    if(!tabfinal)
    {
        exit(1);
    }
    int *usednumber=calloc(sizeof(int),indextab);
    if(!usednumber)
    {
        exit(1);
    }
    powerset(target,tabnumbers,indextab,tabfinal,0,usednumber);
    free(tabfinal);
    free(tabnumbers);
    free(usednumber);
}