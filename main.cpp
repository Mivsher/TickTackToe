#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

using namespace std;

#define ind(i,j) (i+j*3)
enum state {O,X,N};
class Desk
{
    protected:
        state* d;// d[3][3];
    public:
        state* get_D()
        { return d;}
        Desk()
        {
            d = new state[9];
            for (int n = 0;n<3;n++)
                for (int m = 0;m<3;m++)
                    d[ind(n,m)] = N;
        }
        void ChangeDeskState(int r, int s, int i)
        {
            if (i == 1)
            { d[ind(r,s)] = X;}
            if (i == 0)
            { d[ind(r,s)] = O;}
        }
        string to_string()
        {
            string stemp = "";
            for(int n = 0;n<3;n++)
                {for(int m = 0;m<3;m++)
                    if(d[ind(n,m)] == N)
                     stemp += "N|";
                    else
                        if (d[ind(n,m)] == X)
                         stemp += "X|";
                        else
                         stemp += "O|";
                stemp += "\n";}
           return stemp;

        }
        bool IsEndOfGame() //returns true if "yes, it Is the End of Game"
        {
            bool b = true;
            for (int m = 0;m<3;m++)
                for (int n = 0;n<3;n++)
                    if (d[ind(m,n)] == N) b = false;
            return b;
        }
        ~Desk()
        {
            delete[] d;
        }

};
class Player
{
    protected:
        string username;
        state mark;
        Desk* D;
        int wins;
        int defeats;
    public:
        void virtual Move() = 0;
        string getUsName() {return username;}
        Player(){}
        Player(string n,state m)
        {
            username = n;
            mark = m;
        }
        void setD(Desk * d)
        { D = d;}
        Desk* getD()
        { return D;}
        ~Player(){cout<<"Player was destroed"<<endl; }

};
class Human: public Player
{
    public:
        Human(string n,state m):Player(n,m)
        { cout<<"Constructor worked for Human"<<endl; }
        void Move()
        {
            int i,j;
            cout<<"Now give me your coordinates:"<<endl;
            cin>>i;
            cin>>j;
            state* temp;
          //  temp = D->get_D();
            D->get_D()[ind(i,j)] = mark;
        }
        ~Human(){cout<<"Human is destoroyed"<<endl;}
};
class Computer: public Player
{
    public:
        Computer(bool b, string n,state m):Player(n,m)
        {
            strenght = b;
            cout<<"Constructor worked for Comp"<<endl;
        }
        void Move()
        {
            userAI();
        }
        ~Computer(){cout<<"Computer is destroed"<<endl;}
    protected:
        bool strenght;
        void userAI()
        {
         if (strenght)
            strongAI();
         else
            weakAI();
        }
        void strongAI()
        {
        }
        void weakAI()
        {
            bool succsess = false;
            state * temp;
//            temp[0][0] = *(*D).get_D();
            temp = D->get_D();
            while(!succsess)
            {
                int i = rand()%3;
                int j = rand()%3;
                if (temp[ind(i,j)] == N)
                {
                    temp[ind(i,j)] = mark;
                    succsess = true;
                }

            }
        }

};
class GAME
{
    protected:
        Player* p1;
        Player* p2;
    public:
        Desk d;
        Player* getP1() {return p1;}
        Player* getP2() {return p2;}
        GAME(string s,string name)
        {
            if (s=="1")
            {
                p1 = new Computer(0,"Computer1",X);
                p2 = new Computer(0,"Computer2",O);
            }
            else
             if(s=="2")
             {
                p1 = new Computer(0,"Computer",X);;
                p2 = new Human(name,O);
             }
            p1->setD(&d);
            p2->setD(&d);
        }
        void Play()
        {
            bool keep = true;
            if (rand()%2 == 0)
            {
              while (keep)
                {
                p1->Move();
                cout<<d.to_string()<<endl;
                if (d.IsEndOfGame()) {keep = false; continue;}
                p2->Move();
                cout<<d.to_string()<<endl;
                if (d.IsEndOfGame()) {keep = false; continue;}
                }
            }
            else
            {
                while(keep)
                {
                p2->Move();
                cout<<d.to_string()<<endl;
                if (d.IsEndOfGame()) {keep = false; continue;}
                p1->Move();
                cout<<d.to_string()<<endl;
                if (d.IsEndOfGame()) {keep = false; continue;}
                }
            }
            }
        ~GAME()
        {
            delete p1;
            delete p2;
        }

};
    int main()
{
    string stemp = "";
    cout<<"Welcom to the TicTacToe game.\nChoose game mode.\nEnter 1 for computer-computer game. Enter 2 for player-computer game."<<endl;
    bool b = true;
    while(b)
    {
        cin>>stemp;
        if (stemp!="1"&&stemp!="2")
        {
            cout<<"That won't do. Try again."<<endl;
        }
        else
        {
            b = false;
        }
    }
    string nm = "nemo";
    cout<<"Enter your name\n";
    cin>>nm;
    GAME *g = new GAME(stemp,nm);
    srand(time(0));
    g->Play();
   // cout<<G->d.to_string()<<endl;

    delete g;
    return 0;
};
