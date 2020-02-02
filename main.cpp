#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include <dos.h>
#include <dir.h>
#include <fstream>

using namespace std;

long x , y;
long score = 0;
long flag_score = 0;
int value[40][40];
char play_again = 'y';
int b , r , c ;

struct home{
    bool bomb = false;
    char value = '*';
    bool flag = false;
    bool open = false ;
    bool score = false;
}board[40][40];


struct player{
    string name;
    long score = 0;
}player;

int randx()
{
    return 1+ (rand() % r);
}

int randy()
{
    return 1+ (rand() % c);
}


void display()
{
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole,2);
    cout << endl;
    cout << "\t";
    cout << endl;
    for(int i = 0 ; i < r+1 ; ++i)
    {
        if(i > 0)

            cout <<endl <<i << "\t" ;
        else
            cout << "\t" ;
        SetConsoleTextAttribute(hconsole,2);
        cout << "|";
        for(int j =1 ; j < c+1 ; ++j)
        {
            SetConsoleTextAttribute(hconsole,15);
            if (board[i][j].value == ' ')
                SetConsoleTextAttribute(hconsole,136);
            if (board[i][j].value == '^')
                SetConsoleTextAttribute(hconsole,236);
            if (board[i][j].value == 'B')
                SetConsoleTextAttribute(hconsole,12);
            if (board[i][j].value == '1')
                SetConsoleTextAttribute(hconsole,11);
            if (board[i][j].value == '2')
                SetConsoleTextAttribute(hconsole,13);
            if (board[i][j].value == '3')
                SetConsoleTextAttribute(hconsole,14);
            if (board[i][j].value == '*')
                SetConsoleTextAttribute(hconsole,153);

            if(i == 0)
            {
                SetConsoleTextAttribute(hconsole,10);
                cout << j << " ";

            }
            else if(j > 9)

                cout << board[i][j].value << "  ";
            else
                cout <<  board[i][j].value << " " ;
            SetConsoleTextAttribute(hconsole,2);
            cout << "|" ;
        }
        if(i == 0)
            cout << endl;
        cout << endl;
        cout << "\t";
        for (int k = 0 ; k < 4*c - 8 ;k++)
                cout << "-";
        SetConsoleTextAttribute(hconsole,10);

    }

    cout << endl;

}

void bomb_maker()
{
    for (int i = 0 ; i < b ; i++)
    {
        int j = randx();
        int k = randy();
        if (board[j][k].bomb == true)
        {
            i--;
            continue;
        }
        board [j][k].bomb = true;
    }
}

void put_value()
{
    for(int i = 1 ; i < r+1 ; i++)
        for(int j = 1 ; j < c+1 ; j++)
        {
            int num = 9;
            if(board[i][j].bomb == true)
            {
                value[i][j] = num;
                continue;
            }
            num = 0;
            if(board[i-1][j].bomb == true)
                num++;
            if(board[i+1][j].bomb == true)
                num++;
            if(board[i][j-1].bomb == true)
                num++;
            if(board[i][j+1].bomb == true)
                num++;
            if(board[i-1][j+1].bomb == true)
                num++;
            if(board[i-1][j-1].bomb == true)
                num++;
            if(board[i+1][j+1].bomb == true)
                num++;
            if(board[i+1][j-1].bomb == true)
                num++;
            value[i][j] = num;
        }
}

void zero_maker(int i , int j)
{
    if(value[i][j] == 0)
    {
        board[i][j].value = ' ';
        board[i][j].open = true;
        player.score++;
        board[i][j].score = true;
        if(value[i-1][j] == 0 && board[i-1][j].open == false && i > 1 && board[i-1][j].flag == false)
            zero_maker( i-1 , j);
        else if(board[i-1][j].open == false && board[i-1][j].flag == false)
        {
            board[i-1][j].value = (char)(48 + value[i-1][j]);
            board[i-1][j].open = true;
        }
        if(value[i+1][j] == 0 && board[i+1][j].open == false && i < r && board[i+1][j].flag == false)
            zero_maker( i+1 , j);
        else if(board[i+1][j].open == false && board[i+1][j].flag == false)
        {
            board[i+1][j].value = (char)(48 + value[i+1][j]);
            board[i+1][j].open = true;
        }
        if(value[i][j-1] == 0 && board[i][j-1].open == false && j > 1 && board[i][j-1].flag == false)
            zero_maker( i , j-1);
        else if(board[i][j-1].open == false && board[i][j-1].flag == false)
        {
            board[i][j-1].value = (char)(48 + value[i][j-1]);
            board[i][j-1].open = true;
        }
        if(value[i][j+1] == 0 && board[i][j+1].open == false && j < c && board[i][j+1].flag == false)
            zero_maker( i , j+1);
        else if(board[i][j+1].open == false && board[i][j+1].flag == false)
        {
            board[i][j+1].value = (char)(48 + value[i][j+1]);
            board[i][j+1].open = true;
        }
        if(value[i-1][j+1] == 0 && board[i-1][j+1].open == false && i > 1 && j < c && board[i-1][j+1].flag == false)
            zero_maker( i-1 , j+1);
        else if(board[i-1][j+1].open == false && board[i-1][j+1].flag == false)
        {
            board[i-1][j+1].value = (char)(48 + value[i-1][j+1]);
            board[i-1][j+1].open = true;
        }
        if(value[i-1][j-1] == 0 && board[i-1][j-1].open == false && i > 1 && j > 1 && board[i-1][j-1].flag == false)
            zero_maker( i-1 , j-1);
        else if(board[i-1][j-1].open == false && board[i-1][j-1].flag == false)
        {
            board[i-1][j-1].value = (char)(48 + value[i-1][j-1]);
            board[i-1][j-1].open = true;
        }
        if(value[i+1][j+1] == 0 && board[i+1][j+1].open == false && i < r && j < c && board[i+1][j+1].flag == false)
            zero_maker( i+1 , j+1);
        else if(board[i+1][j+1].open == false && board[i+1][j+1].flag == false)
        {
            board[i+1][j+1].value = (char)(48 + value[i+1][j+1]);
            board[i+1][j+1].open = true;
        }
        if(value[i+1][j-1] == 0 && board[i+1][j-1].open == false && i < r && j > 1 && board[i+1][j-1].flag == false)
            zero_maker( i+1 , j-1);
        else if(board[i+1][j-1].open == false && board[i+1][j-1].flag == false)
        {
            board[i+1][j-1].value = (char)(48 + value[i+1][j-1]);
            board[i+1][j-1].open = true;
        }

    }
    else
    {
        if(value[i][j] != 9)
        {
            board[i][j].value = (char)(48 + value[i][j]);
            board[i][j].open = true;
        }
        else
            board[i][j].flag = false;
    }
}

 void get_user()
{
        HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
        char status;
        char answer;
        cout << "Enter the X and Y : ";
        cin >> x >> y;
        cout << endl << "Flag or Open ? ";
        SetConsoleTextAttribute(hconsole,12);
        cout << "(f / o)  ";
        SetConsoleTextAttribute(hconsole,15);
        cin >> status;
        if (status == 'o')
        {
           if(board[x][y].open == true)
            {
                cout << endl;
                system("cls");
                SetConsoleTextAttribute(hconsole,14);
                cout <<"\t\t" <<"It's already opened" << endl;
                SetConsoleTextAttribute(hconsole,15);
                cout << endl;
            }
           else
            {
                if(board[x][y].flag == true)
                {

                    cout << "Are you sure ?? ";
                    SetConsoleTextAttribute(hconsole,12);
                    cout << "(y / n) " << endl;
                    SetConsoleTextAttribute(hconsole,15);

                    cin >> answer;
                    if(answer == 'y')
                        zero_maker(x , y);
                }
                else
                    zero_maker(x , y);
            system("cls");
            }
        }
        else if(status == 'f')
        {
            if(board[x][y].flag == true)
            {
                system("cls");
                SetConsoleTextAttribute(hconsole,14);
                cout <<"\t\t" <<"It's already flagged" << endl << endl;
                SetConsoleTextAttribute(hconsole,15);
            }
            else
            {
            board[x][y].flag = true;
            board[x][y].value = '^';
            system("cls");
            if(board[x][y].flag == true && board[x][y].bomb == true && board[x][y].score == false)
            {

                flag_score++;
                board[x][y].score=true;
            }
            if(flag_score == b)
                player.score = player.score + flag_score;
            }
        }
}


int main()
{
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while(play_again == 'y')
    {
        SetConsoleTextAttribute(hconsole,15);
        cout << "Enter your name: ";
        //PlaySound(TEXT("hello.wav"),NULL,SND_SYNC);
        cin >> player.name;
        cout << endl;
        system("cls");
        cout << "Enter the number of rows & columns [5,35] : ";
        cin >> r >> c;
        cout << "Enter the number of bombs : ";
        label1:
        cin >> b;
        system("cls");
        if (b > r*c)
        {
            SetConsoleTextAttribute(hconsole,12);
            cout << "PLEASE ENTER AN APPROPRIATE NUMBER !  ";
            SetConsoleTextAttribute(hconsole,15);
            goto label1;
        }
        player.score = 0;
        flag_score = 0;
        for(int i = 1 ; i < r+1 ; i++)
            for(int j = 1 ; j < c+1 ; j++)
            {
                board[i][j].bomb = false;
                board[i][j].flag = false;
                board[i][j].open = false;
                board[i][j].score = false;
                board[i][j].value = '*';
            }
        srand(time(0));
        bomb_maker();
        put_value();
        SetConsoleTextAttribute(hconsole,79);
        cout << endl << " Username : " << player.name << " " << endl << endl;
        SetConsoleTextAttribute(hconsole,159);
        cout << " Number of bombs : " << b << " ";
        SetConsoleTextAttribute(hconsole,2);
        cout << endl;
        display();
        SetConsoleTextAttribute(hconsole,15);
        cout << endl;
        get_user();
        if(board[x][y].bomb == true && board[x][y].flag == false)
            {
                system("cls");
                SetConsoleTextAttribute(hconsole,12);
                cout << "\t\t\t"<< "GAME OVER !" << endl;
               // PlaySound(TEXT("bomb.wav"),NULL,SND_SYNC);
                SetConsoleTextAttribute(hconsole,15);
                for (int i = 1 ; i < r+1 ; i++)
                    for (int j = 1 ; j < c+1 ; j++)
                        if (board[i][j].bomb == true)
                        {
                            SetConsoleTextAttribute(hconsole,12);
                            board[i][j].value = 'B';
                        }
                        else
                            board[i][j].value =(char)(value[i][j] + 48);
                display();
                PlaySound(TEXT("bomb.wav"),NULL,SND_SYNC);
                cout << endl;
                SetConsoleTextAttribute(hconsole,15);
                std::ofstream myfile;
                myfile.open ("record.txt", std::ios_base::app);
                myfile << "Player Name " << ": " << player.name << endl;
                myfile << "Score " << ": " << player.score << endl;
                myfile << "Playing Time " << ": " << endl << endl;
                myfile.close();
                cout << "Do you wanna play again? ";
                SetConsoleTextAttribute(hconsole,12);
                cout << "(y / n)" << endl;
                SetConsoleTextAttribute(hconsole,15);
                cin >> play_again;
                system("cls");
                continue;
            }

         for(int i = 1 ; i < r+1 ; i++ )
            {
                for(int j = 1 ; j < c+1 ; j++)
                {
                    if(value[i][j] != 0 && board[i][j].open == true && value[i][j] != 9 && board[i][j].score == false)
                    {
                        player.score++;
                        board[i][j].score = true;
                    }
                }
            }
        while(1)
        {
            SetConsoleTextAttribute(hconsole,79);
            cout << endl << " Username : " << player.name << " " << endl << endl;
            SetConsoleTextAttribute(hconsole,159);
            cout << " Number of bombs : " << b << " " << endl;
            SetConsoleTextAttribute(hconsole,2);
            display();
            SetConsoleTextAttribute(hconsole,14);
            cout << endl;
            cout << "Score : " << player.score << endl;
            SetConsoleTextAttribute(hconsole,15);
            cout << endl;
            if(player.score == r*c)
            {
                system("cls");
                SetConsoleTextAttribute(hconsole,10);
                cout << "\t\t\t" <<"YOU WON !" << endl;
                SetConsoleTextAttribute(hconsole,15);
                display();

                break;
            }
            get_user();
            for(int i = 1 ; i < r+1 ; i++ )
            {
                for(int j = 1 ; j < c+1 ; j++)
                {
                    if(value[i][j] != 0 && board[i][j].open == true && value[i][j] != 9 && board[i][j].score == false)
                    {
                        player.score++;
                        board[i][j].score = true;
                    }
                }
            }
            if(board[x][y].bomb == true && board[x][y].flag == false)
            {
                SetConsoleTextAttribute(hconsole,12);
                cout << "\t\t\t"<< "GAME OVER !" << endl;
               // PlaySound(TEXT("bomb.wav"),NULL,SND_SYNC);
                SetConsoleTextAttribute(hconsole,15);
                for (int i = 1 ; i < r+1 ; i++)
                    for (int j = 1 ; j < c+1 ; j++)
                        if (board[i][j].bomb == true)
                        {
                            SetConsoleTextAttribute(hconsole,12);
                            board[i][j].value = 'B';
                        }
                        else
                            board[i][j].value = (char) (value[i][j] + 48);
                display();
                PlaySound(TEXT("bomb.wav"),NULL,SND_SYNC);
                cout << endl;
                SetConsoleTextAttribute(hconsole,15);
                std::ofstream myfile;
                myfile.open ("record.txt", std::ios_base::app);
                myfile << "Player Name " <<": " << player.name << endl;
                myfile << "Score " <<  ": " << player.score << endl;
                myfile.close();
                cout << "Do you wanna play again? (y / n) " << endl;
                cin >> play_again;
                system("cls");
                break;
            }

        }
    }
    return 0;
}
