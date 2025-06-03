#include <stdio.h>
#include <stdlib.h>

void sort(int *tab,int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(tab[i]>tab[j])
            {
                int tmp=tab[i];
                tab[i]=tab[j];
                tab[j]=tmp;
            }
        }
    }
}

void proccess(int *tab,int *res, int target,int resi,int start,int total,int n)
{
    if(total==target && resi>0)
    {
        for (int i = 0; i < resi; i++)
        {
            printf("%d%s",res[i],i<resi-1?" ":"\n");
        }
    }
    for(int i=start;i<n;i++)
    {
        if(i>start && tab[i]==tab[i+1])
            continue;
        if(total+tab[i]> target)
            break;
        res[resi]=tab[i];
        proccess(tab,res,target,resi+1,i+1,total+tab[i],n);
    }
}

int main(int arc,char **arv)
{
    if(arc <3)
        return 1;
    int n=arc -2;
    int *tab= malloc(n*4);
    int *res= malloc(n*4); 
    int target;
    for(int i=0;i<n;i++)
        tab[i]=atoi(arv[i+2]);
    sort(tab,n);
    if(target=0)
    {
        printf("\n");
    }
    proccess(tab,res,target,0,0,0,n);
}