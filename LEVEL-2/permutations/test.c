void ft_swap(char *a,char *b)
{
    char tmp=*a;
    *a=*b;
    *b=tmp;    
}

void help2(char *str,int len)
{
    for(int i=0;i<len-1;i++)
    {
        for (int j = 0; j < len -i-1; j++)
        {
            if(str[j]>str[j+1])
                ft_swap(str[j],str[j+1]);
        }
    }
}
void help1(int l,int r,char *str)
{
    if(l==r)
    {
        write(1,str+r+1,1);
        write(1,"\n",1);
    }
    for(int i=l;i<=r;i++)
    {
        ft_swap(&str[l],&str[i]);
        help1(l+1,r,str);
        ft_swap(&str[l],&str[i]);
    }
}


int main(int arc,char **arv)
{
    if(arc!=2)
    {
        return 1;
    }
    int len =0;
    while(arv[1][len])
        len++;
    help2(arv[1],len);
    help1(0,len-1,arv[1]);
}

