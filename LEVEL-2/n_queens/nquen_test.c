void help(int n,int c,int *b)
{
    if(c==n)
    {
        for(int i=0;i< n;i++)
        {
            printf("%d%c",b[i],i<n-1?"":"\n");
        }
        return;
    }
    for(int r=0;r<n;r++)
    {
        int safe =1;
        for(int i=0;i<c;i++)
        {
            int d= c-i;
            if(b[i]==r ||b[i]==r-d||b[i]==r+d)
            {
                safe=0;
                break;
            }
        }
        if(safe)
        {
            b[c]=r;
            help(n,c+1,b);
        }
    }
}

help1(int n)
{
    int b[n];
    help(n,0,b);
}

int main(int arc,char **arv)
{
    if(arc!=2 || atoi(arv[1])<0)
    {
        write(1,"\n",1);
        return 1;
    }
    help1(atoi(arv[1]));
}