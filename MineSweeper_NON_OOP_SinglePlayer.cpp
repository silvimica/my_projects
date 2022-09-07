#include <iostream>
#include <ctime>
#include<cstdlib>
#define Valid(i,j) (i>=0 && i<9 && j>=0 && j<9)
using namespace std;
int Numbers[9][9];
int Covered[9][9];
int Score;
int bombs;
bool WIN;
bool GAMEOVER;
void Uncover(int row, int column);
void AskUser();
void PrintBoards();

int main()
{

    int choice;
    do{
    system("CLS");
    cout<<"\tMAIN MENU\n";
    cout<<" 1)New Game\n";
    cout<<" 2)Rules\n";
    cout<<" 3)Exit game\n\n";
    cout<<"Chose option: ";
    cin>>choice;
    switch(choice)
    {
    case 1:{
        system("CLS");
        //setting initial values
    GAMEOVER=false;
    WIN=false;
    Score=0;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            Numbers[i][j]=0;
            Covered[i][j]=1;
        }
    }
    //Prompting for amount of bombs
    cout<<"Choose difficulty (Easy-Hard)\n(Input a number, 1-Easy|2-Medium|3-Hard)-> ";
    bool correct = 0;
    srand(time(NULL));
    while(!correct){
        int num;
        cin>>num;
        if(num < 1 || num > 3)
            cout<<"Please, enter a valid difficulty.\n(Input a number, 1-Easy|2-Medium|3-Hard)-> ";
        else{
            correct = 1;
            if(num == 1)
                bombs = rand()%21;
            if(num == 2)
                bombs = (rand()%31) + 20;
            if(num == 3)
                bombs = (rand()%31) + 50;
        }
    }
    system("CLS");
    //Placing bombs
    for(int i=0;i<bombs;i++)
    {
        int x,y;
        x=rand()%9;
        y=rand()%9;
        if(Numbers[x][y]!=-1)
        {
            Numbers[x][y]=-1;
        }
        else
        {
            do
            {
              x=rand()%9;
              y=rand()%9;
            }while(Numbers[x][y]==-1);
            Numbers[x][y]=-1;
        }


    }
    //Placing Numbers
    int counter;
     for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            counter=0;
            if(Numbers[i][j]!=-1)
            {


            for(int p=i-1;p<=i+1;p++)
            {
                for(int q=j-1;q<=j+1;q++)
                {
                    if(Valid(p,q))
                    {

                        if (Numbers[p][q]==-1)
                            counter++;

                    }
                }
            }
            Numbers[i][j]=counter;
            }
            else{continue;}
        }
    }
        PrintBoards();
    do
    {
        AskUser();
        system("CLS");
        PrintBoards();

    }while(!WIN && !GAMEOVER);
    if(WIN)
    {
        system("CLS");
        PrintBoards();
        cout<<"\n\nCONGRATULATIONS! YOU WON!"<<endl;
    }
    if(GAMEOVER)
    {

        cout<<"\n\nBOOM! GAME OVER! YOUR SCORE IS "<<Score<<endl;
    }
    system("PAUSE");}
    break;
    case 2:
        {
        system("CLS");
        cout<<"You are presented with a 9*9 board of squares. Some squares contain mines (bombs), others don't.\n";
        cout<<"If you click on a square containing a bomb, you lose.\n";
        cout<<"If you manage to click all the squares (without clicking on any bombs) you win.\n";
        cout<<"Clicking a square which doesn't have a bomb reveals the number of neighbouring squares containing bombs.\n";
        cout<<"Use this information plus some guess work to avoid the bombs.\n";
        cout<<"To open a square, enter the row and the column of these square.\n";
        cout<<"To return to the main menu press enter. Good Luck!\n";
        system("PAUSE");}
        break;

    case 3:
        system("CLS");
        cout<<"\n\n\tGood Bye!\n\n";
        break;
    default:
        cout<<"Sorry, this is not valid option. Try again.\n";
        system("PAUSE");
    }} while(choice!=3);

    return 0;


}
void PrintBoards()
{
    cout<<"\tSCORE: "<<Score<<".\tBOMBS: "<<bombs<<".\n\n";
    cout<<"\t";
    for(int i=0;i<9;i++)
    {
        cout<<i+1<<" ";
    }
    cout<<endl<<endl;
    for(int i=0;i<9;i++)
    {
        cout<<" "<<i+1<<"\t";
        for(int j=0;j<9;j++)
        {
            if(Covered[i][j]==1)
            {
                cout<<char(219)<<" ";
            }
            else
            {
                if(Numbers[i][j]>0)
                {
                    cout<<Numbers[i][j]<<" ";
                }
                else if(Numbers[i][j]==0)
                {
                    cout<<char(176)<<" ";
                }
                else
                {
                    cout<<"@"<<" ";
                }

            }
        }
        cout<<endl<<endl;
    }
}
void Uncover(int row, int column)
{
    if(Numbers[row][column]==-1)
    {
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                Covered[i][j]=0;

            }
        }
        GAMEOVER=true;
    }
    else if(Numbers[row][column]>0)
    {
        Covered[row][column]=0;
        Score++;
    }
    else //if the cell is empty all adjacent cells are uncovered
    {
        for(int i=row-1;i<=row+1;i++)
         {
             for(int j=column-1;j<=column+1;j++)
             {
                 if(Valid(i,j))
                 {

                     if(Covered[i][j]!=0)
                        {
                          Covered[i][j]=0; Score++;
                           if((i!=row || j!=column) && Numbers[i][j]==0)
                             {
                                Uncover(i,j);
                             }
                          else{continue;}
                     }



                 }
             }
         }
    }
    if (Score==81-bombs)
    {
        WIN=true;
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {


                    Covered[i][j]=0;

            }
        }
    }
}
void AskUser()
{
    int r,c;
    cout<<"Enter row: ";
    cin>>r;
    cout<<"Enter column: ";
    cin>>c;
    if(Valid(r-1,c-1))
    {Uncover(r-1,c-1);}
    else
    {
        do
        {
            cout<<"\nOoops! Enter values from 1 to 9.Try again!\n";
            cout<<"Enter row: ";
            cin>>r;
            cout<<"Enter column: ";
            cin>>c;
        }while(!Valid(r-1,c-1));
        Uncover(r-1,c-1);
    }
}
