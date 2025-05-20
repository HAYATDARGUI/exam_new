#include <unistd.h>
void ft_swap(char *a,char *b)
{
    char tmp;
    tmp=*a;
    *a=*b;
    *b=tmp;
}
void help1(char *str,int len)
{
    for(int i=0;i<len-1;i++)
    {
        for(int j=0;j<len-i-1;j++)
        {
            if(str[j]>str[j+1])
            {
                ft_swap(&str[j],&str[j+1]);
            }
        }
    }
}
void help2(char *str, int l,int r)
{
    if(l==r)
    {
        write(1,str,r+1);
        write(1,"\n",1);
    }
    else
    {
        for(int i=l;i<=r;i++)
        {
            ft_swap(&str[l],&str[i]);
            help2(str,l+1,r);
            ft_swap(&str[l],&str[i]);
        }
    }
}
int main(int arc,char **arv)
{
    int len =0;
    if(arc==2)
    {
        while(arv[1][len])
        {
            len++;
        }
        help1(arv[1],len);
        help2(arv[1],0,len-1);
    }
}