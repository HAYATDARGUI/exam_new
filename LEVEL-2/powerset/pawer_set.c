#include <stdio.h>
#include <stdlib.h>
void ft_swap(int *a,int *b)
{
    int tmp=*a;
    *a=*b;
    *b=tmp;
}
void sort(int *tab,int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=i +1;j<n;j++)
        {
            if(tab[i]>tab[j])
            {
                ft_swap(&tab[i],&tab[j]);
            }
        }
    }
}

void proccess(int *tab,int *res,int target,int res_i,int start,int total,int n,int *flag)
{
    if(total==target && res_i >0)
    {
        for(int i=0;i<res_i;i++)
        {
            printf("%d%s",res[i],i<res_i-1?" ":"\n");
        }
        *flag=1;
    }
    for(int i=start;i<n;i++)
    {
        if(i> start && tab[i]==tab[i-1])
            continue;
        if(total +tab[i]>target)
            break;
        res[res_i]=tab[i];
        proccess(tab,res,target,res_i+1,i+1,total+tab[i],n,flag);
    }
}

int main(int arc,char **arv)
{
    if(arc < 3)
    {
        printf("\n");
        return 0;
    }
    int target=atoi(arv[1]);
    int n= arc-2;
    int *tab=malloc(n *4);
    int *res=malloc(n *4);
    int flag =0;
    for(int i=0;i<n ;i++)
    {
        tab[i]=atoi(arv[i+2]);
    }
    sort(tab,n);
    if(target==0)
    {
        printf("\n");
        flag =1;
    }
    proccess(tab,res,target,0,0,0,n,&flag);
    if(!flag)
    {
        printf("\n");
    }
}