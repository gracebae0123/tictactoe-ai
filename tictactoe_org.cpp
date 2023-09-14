#include <iostream>
#include <stdlib.h>
using namespace std;

char board[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};

int choice;
int row,col;
char turn = 'X';
bool draw = false;

void display_board(){
    cout<<"         PLAYER - 1 [X]t PLAYER - 2 [O]"<<endl<<endl;;
    cout<<"               |     |     "<<endl;;
    cout<<"            "<<board[0][0]<<"  | "<<board[0][1]<<"   |  "<<board[0][2]<<endl;
    cout<<"          _____|_____|_____"<<endl;
    cout<<"               |     |     "<<endl;
    cout<<"            "<<board[1][0]<<"  | "<<board[1][1]<<"   |  "<<board[1][2]<<endl;
    cout<<"          _____|_____|_____"<<endl;
    cout<<"               |     |     "<<endl;
    cout<<"            "<<board[2][0]<<"  | "<<board[2][1]<<"   |  "<<board[2][2]<<endl;
    cout<<"               |     |     "<<endl;
}

void player_turn(){
    if (turn == 'X'){
        cout<<"Player - 1 [X] turn : "<<endl;
    }
    else{
        cout<<"Player -2 [O] turn :"<<endl;
    }

    cin>>choice;
    
    switch(choice){
        case 1: row=0; col=0; break;
        case 2: row=0; col=1; break;
        case 3: row=0; col=2; break;
        case 4: row=1; col=0; break;
        case 5: row=1; col=1; break;
        case 6: row=1; col=2; break;
        case 7: row=2; col=0; break;
        case 8: row=2; col=1; break;
        case 9: row=2; col=2; break;
        
        default: cout<<"INVALID MOVE"<<endl;
    } 
    
    char chosen_loc = board[row][col];
    
    if (turn =='X' && chosen_loc !='X' && chosen_loc != 'O'){
        // not occupied
        board[row][col] = 'X';
        turn = 'O';
    }

    else if (turn =='O' && chosen_loc !='X' && chosen_loc != 'O'){
        // not occupied
        board[row][col] = 'O';
        turn = 'X';
    }
    else{
        // if already occupied
        cout <<"The box is already occupied. Please choose anotehr one"<<endl;
        player_turn();
        display_board();
    }
    display_board();
}

bool gameover(){
    for (int i =0; i< 3; i++){
        // row or col
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] || board[0][i] == board[1][i] && board[0][i] == board[2][i]) return false;
    }
    // diagnoal
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] || board[0][2] == board[1][1] && board[0][2] == board[2][0]) return false;

    // continue playng if all boxes are not occupied
    for (int i=0; i<3; i++){
        for (int j=0;j<3;j++){
            if (board[i][j] != 'X' && board[i][j] != 'O') return true;
        }
    }
    // draw
    draw = true;
    return false;
}


int main(){
    cout<<"         T I C -- T A C -- T O E -- G A M E"<<endl;
    cout<<"             FOR 2 PLAYERS"<<endl;
    while(gameover()){
        display_board();
        player_turn();
        gameover();
    }
    if(turn == 'X' && draw == false){
        cout<<"Congratulations!Player with 'O' has won the game";
    }
    else if(turn == 'O' && draw == false){
        cout<<"Congratulations!Player with 'X' has won the game";
    }
    else
    cout<<"GAME DRAW!!!nn";
}
