
#include <unistd.h>
void    print_solved(char *str) {
    for (int i = 0; str[i]; i++)
        write (1, str + i, 1);
    write(1, "\n", 1);
}
void solve(char *str,int pos,int open,int min_rem,char *tmp,int tmp_pos)
{
    if(!str[pos])
    {
        if(open==0 && min_rem==0)
        {
            tmp[tmp_pos]=0;
            print_solved(tmp);
        }
        return;
    }
    if(min_rem > 0)
    {
        tmp[tmp_pos]=' ';
        solve(str,pos+1,open,min_rem-1,tmp,tmp_pos+1);
    }
    if(str[pos]=='(')
    {
        tmp[tmp_pos]='(';
        solve(str,pos+1,open+1,min_rem,tmp,tmp_pos+1);
    }
    else if(str[pos]==')')
    {
        if(open >0)
        {
            tmp[tmp_pos]=')';
            solve(str,pos+1,open-1,min_rem,tmp,tmp_pos+1);
        }
    }
    else
    {
        tmp[tmp_pos]=str[pos];
        solve(str,pos+1,open,min_rem,tmp,tmp_pos+1);
    }
    return ;
}
int minrem(char *str)
{
    int i=0;
    int open=0;
    int close =0;
    while(str[i])
    {
        if(str[i]=='(')
            open++;
        else if(str[i]==')')
        {
            if(open>0)
                open--;
            else
                close++;
        }
        i++;
    }
    return (open+close);

}
int main(int arc,char **arv)
{
    if(arc!=2)
        return 1;
    int i=0;
    while(arv[1][i])
    {
        i++;
    }
    char tmp[i+1];
    int min_rem=minrem(arv[1]);
    solve(arv[1],0,0,min_rem,tmp,0);
}