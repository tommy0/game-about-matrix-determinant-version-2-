#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define N 3

using namespace std;
int tabel[N][N];
bool check_val[N*N];
bool turn;
int x,y,val;

int det()   //нахождение определителя
{
    int l;
    int d;
    int sum11=1,sum12=0, sum21=1, sum22=0;
// находим детерминант
    for (int i=0; i<N; i++)
    {
        sum11=1;
        l=2*N-1-i;
        sum21=1;
        for (int j=0; j<N; j++)
        {
            sum21*=tabel[j][l%N];
            l--;
            sum11*=tabel[j][(j+i)%(N)];
        }
        sum22+=sum21;
        sum12+=sum11;
    }
    d=sum12-sum22;
    return d;
}

int mark(bool turn_temp)
{
    if (turn_temp) return det();
    else return (-det());
}

void output()
{
    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            cout<<tabel[i][j]<<" ";
        }
        cout<<endl;
    }
}

void input_zero_val()
{
    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            tabel[i][j]=0;
        }
    }
    for(int i=0; i<(N*N); ++i)
    {
        check_val[i]=true;
    }
}

int who_turn_first()
{
    cout<<"1)Computer turn first"<<endl;
    cout<<"2)Player turn first"<<endl;
    int who;
    cin>>who;
    return who;
}

bool check_turn(int x, int y, int val)
{
    if(tabel[x-1][y-1]==0 && check_val[val-1]) return true;
    else return false;
}

bool endofgame(int n)
{
    if(n>0) return true;
    else return(false);
}

void output_winner(int cap)
{
    if(mark(turn)>0) cout<<"You lose "<<det()<<endl;
    else if(cap==0) cout<<"Draw "<<det()<<endl;
        else cout<<"You win "<<det()<<endl;
    cout<<"GAME OVER"<<endl;
}

int comp_turn(bool turn_temp, int n, int x_t, int y_t, int val_t)
{
    int i,j,k;
    int x_temp,y_temp,val_temp;
    int now_mark, best_mark;
    if(n==0) best_mark=mark(turn_temp);
    else
    {
        best_mark=-999999;
        for(i=0;i<N;++i)
        {
            for(j=0;j<N;++j)
            {
                if(tabel[i][j]==0)
                {
                    for(k=0;k<(N*N);++k)
                    {
                        if(check_val[k])
                        {
                            check_val[k]=false;
                            tabel[i][j]=k+1;
                            now_mark=-comp_turn(not turn_temp,n-1,x_temp,y_temp,val_temp);
                            check_val[k]=true;
                            tabel[i][j]=0;
                            if(now_mark>best_mark)
                            {
                                best_mark=now_mark;
                                x=i;
                                y=j;
                                val=k+1;
                                if(best_mark>0) return best_mark;
                            }
                        }
                    }
                }
            }
        }
    }
    return best_mark;
}

void menu_pvc()
{
    int n=9;
    bool flag;
    int cap;
    bool turn_tmp;
    turn=(who_turn_first()==1?true:false);
    turn_tmp=turn;
    output();
    while(endofgame(n))
    {
        if(turn_tmp)
        {
            cap=comp_turn(turn,n,x,y,val);
            tabel[x][y]=val;
            turn_tmp=false;
            check_val[val-1]=false;
            system("cls");
            cout<<"Tabel"<<endl;
            output();
            cout<<endl;
            n--;
        }
        else
        {
            if(n>0)
            {
                flag=true;
                while(flag)
                {
                    cout<<"Please enter coordinates of your turn"<<endl;
                    cin>>x>>y>>val;
                    if(check_turn(x,y,val))
                    {
                        tabel[x-1][y-1]=val;
                        turn_tmp=true;
                        check_val[val-1]=false;
                        system("cls");
                        cout<<"Tabel"<<endl;
                        output();
                        cout<<endl;
                        getchar();
                        n--;
                        flag=false;
                    }
                    else (cout<<"Error, Please enter again"<<endl);
                }
            }
        }
    }
    output_winner(cap);
    getchar();
}

void menu_pvp()                             //меню игры
{
    int i,j;                                        //счетчики
    int n=9;
    string num_pl;
    bool flag = false;
    cout<<"You play with player"<<endl;
    output();
    while(endofgame(n))
    {
        flag==false?num_pl="one":num_pl="two";
        cout<<"Turn player "+num_pl<<endl;
        cout<<"Please enter coordinates of you turn: ";  //input запихнуть
        cin>>x>>y>>val;
        while(not check_turn(x,y,val))
        {
            cout<<"Please repeat write coordinates and value"<<endl;
            cin>>x>>y>>val;
        }
        n--;
        check_val[val-1]=false;
        tabel[x-1][y-1]=val;                                //растановк хода
        system("cls");
        output();                                //вывод игрвого поля
        cout<<endl;
        //system("cls");
        flag=not flag;                                  //смена игрока
    }
    ((det()>0)?(cout<<"Win player one "<<det()):((det()==0)?(cout<<"Draw "<<det()):(cout<<"Win player two "<<det())));

}

int choose_game()
{
    cout<<"Hello, this game about determinant"<<endl;
    cout<<"Choose game edition"<<endl;
    cout<<"1) Player vs Player"<<endl;
    cout<<"2) Player vs Computer"<<endl;
    int option;
    bool flag=true;
    while(flag)
    {
        cin>>option;
        if(option<1 || option>2)
        {
            cout<<"Wrong choose, please try again"<<endl;
            cin>>option;
        }
        else
        {
            flag=false;
            return option;
        }
    }
}

int main()
{
    input_zero_val();
    int choose = choose_game();
    if(choose==1) menu_pvp();
    else menu_pvc();
    return 0;
}
