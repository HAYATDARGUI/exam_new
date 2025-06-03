void proccess(char *str,int open,int pos,int minr,char *tmp,int postemp)
{
    int i=0;
    if(!str[i])
    {
        
    }
}

int main(int arc,char **arv)
{
    if(arc !=2)
    {
        return 1;
    }
    int len;
    while(arv[1][len])
    {
        len++;
    }
    char tmp[len+1];
    int minremove=min_remove(arv[1]);
    proccess(arv[1],0,0,minremove,tmp,0);
}