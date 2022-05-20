#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;

bool gameover;
const int width=20;
const int height=20;
int x,y,fruitx,fruity,score;
int tailx[100],taily[100];
int ntail;
enum eDirection {STOP=0,LEFT,RIGHT,UP,DOWN};
eDirection dir;

void Setup(){
    gameover=false;
    dir=STOP;
    x=width/2;
    y=height/2;
    fruitx=rand()%width;
    fruity=rand()%height;
    score=0;
}
void Draw(){
    system("cls");
    for(int i=0;i<width+2;i++) cout<<"#";
    cout<<"\n";
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(j==0) cout<<"#";
            if(i==y&&j==x) cout<<"O";
            else if(i==fruity&&j==fruitx) cout<<"&";
            else{
                bool isprinting=false;
                for(int k=0;k<ntail;k++){
                    if(tailx[k]==j&&taily[k]==i){
                        cout<<"o";
                        isprinting=true;
                    }
                }
                if(!isprinting) cout<<" ";
            }
            if(j==width-1) cout<<"#";
        }
        cout<<"\n";
    }
    for(int i=0;i<width+2;i++) cout<<"#";
    cout<<"\n";
    cout<<"SCORE : "<<score;
}
void Input(){
    if(_kbhit()){
        switch(_getch()){
            case 'a':   dir=LEFT;
                        break;
            case 'd':   dir=RIGHT;
                        break;
            case 'w':   dir=UP;
                        break;
            case 's':   dir=DOWN;
                        break;
            case 'x':   gameover=true;
                        break;
        }
    }
}
void Logic(){
    int prevX = tailx[0];
    int prevY = taily[0];
    int prev2X, prev2Y;
    tailx[0] = x;
    taily[0] = y;
    for (int i = 1; i < ntail; i++){
        prev2X = tailx[i];
        prev2Y = taily[i];
        tailx[i] = prevX;
        taily[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if (x>=width) x=0;
    else if(x<0) x=width-1;
    if (y>=height) y=0;
    else if(y<0) y=height-1;
    for (int i=0; i<ntail;i++)
        if (tailx[i]==x&&taily[i]==y)
            gameover=true;
    if (x==fruitx&&y==fruity){
        score+=10;
        fruitx=rand()%width;
        fruity=rand()%height;
        ntail++;
    }
}
int main(){
    Setup();
    while(!gameover){
        Draw();
        Input();
        Logic();
        Sleep(20);
    }
    return 0;
}
