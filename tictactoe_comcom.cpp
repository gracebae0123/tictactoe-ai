#include <iostream>
#include <stdlib.h>
#include <random>
using namespace std;

const int PLAYER_X = -1;
const int PLAYER_O = 1;

void display_board(int *board){
    cout<<"----++----++----"<<endl;
    int k=0;
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            cout<<"| ";
            if (board[k] == 0) cout<<k+1<<" |";
            else{
                if (board[k]==PLAYER_X) cout<<"X |";
                else cout<<"O |";
            }
            k++;
        }
        cout<<endl<<"----++----++----"<<endl;
    }
    
}

bool isFull(int* board){
    for (int i=0; i<9; i++){
        if (board[i] == 0) return false;
    }
    return true;
}

int winner(int* board){
    int winCombos[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };
    for (int i=0; i<8; i++){
        int a = winCombos[i][0];
        int b = winCombos[i][1];
        int c = winCombos[i][2];
        // curr player wins
        if (board[a] != 0 && board[a] == board[b] && board[a] == board[c]) return board[a];
    }
    return 0;
}

int minimax(int* board, int player){
    int win = winner(board);
    if (win != 0) return win*player;

    int move = -1;
    int maxScore = -2;
    
    for (int i=0; i<9; i++){
        if(board[i] == 0){
            board[i] = player;
            int score = -minimax(board, player*-1);
            maxScore = max(score, maxScore);
            move = i;
            board[i] = 0;
        }
    }
    if (move == -1) return 0;
    return maxScore;
}

//implement alpha beta pruning
int alphabeta (int* board, int player, int depth, int alpha, int beta, bool maximize){
    int win = winner(board);
    if (win != 0 || depth ==0) return win*player;

    if (maximize){
        int maxScore = INT_MIN;
        for (int i=0; i<9; i++){
            if (board[i] == 0){
                board[i] = player;
                int score = alphabeta(board, player*-1, depth-1, alpha, beta, false);
                board[i] = 0;
                maxScore = max(score, maxScore);
                alpha = max(alpha, score);
                if (beta <= alpha) break;
            }
        }
        return maxScore;
    }
    else{
        int minScore = INT_MAX;
        for (int i=0; i<9; i++){
            if (board[i] == 0){
                board[i] = player;
                int score = alphabeta(board, player*-1, depth-1, alpha, beta, true);
                board[i] = 0;
                minScore = min(score, minScore);
                beta = min(beta, score);
                if (beta <= alpha) break;
            }
        }
        return minScore;
    }
}
int getRandomDepth(){
    int minDepth = 3;
    int maxDepth = 7;
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(minDepth, maxDepth);
    return dist(gen);
}

int findBestMove (int* board, int player){
    int bestMove = -1;
    int bestScore = INT_MIN;
    int alpha = INT_MIN;
    int beta = INT_MAX; 

    int depth = getRandomDepth();
    for (int i=0; i<9; ++i){
        if (board[i] == 0){
            board[i] = player;
            int score = -alphabeta(board, player*-1, depth, alpha, beta, true);
            //int score = -minimax(board,player*-1);
            board[i] = 0;
            bestScore = max(score, bestScore);
            bestMove = i;
        }
    }
    return bestMove;
}

int main(){
    cout<<" T I C -- T A C -- T O E -- G A M E"<<endl;
    cout<<"      HUMAN  [X]   COMPUTER [O]"<<endl<<endl;;
    cout <<"BOARD:"<<endl;
    cout << "----++---++----" << endl;
    cout << "| 1 || 2 || 3 |" << endl;
    cout << "----++---++----" << endl;
    cout << "| 4 || 5 || 6 |" << endl;
    cout << "----++---++----" << endl;
    cout << "| 7 || 8 || 9 |" << endl;
    cout << "----++---++----" << endl << endl << endl; 

    int board[9] = {0};
    int moves = 0;
    int currPlayer = (rand() % 2 == 0) ? PLAYER_X : PLAYER_O;
    int bestMove = 0;

    while(moves < 9){
        if (currPlayer == 1){
            cout<<"Player O turn:"<<endl;
            bestMove = findBestMove(board, currPlayer);
            board[bestMove] = currPlayer;
            moves++;
            currPlayer = PLAYER_X;
            display_board(board);
        } else{
            cout<<"Player X turn:"<<endl;
            bestMove = findBestMove(board, currPlayer);
            board[bestMove] = currPlayer;
            moves++;
            currPlayer = PLAYER_O;
            display_board(board);
        }

        if (winner(board) != 0) break;
    }
     switch(winner(board)){
         case 0:
             cout<<"It's a draw!"<<endl;
             break;
         case PLAYER_X:
             cout<<"Player X wins!"<<endl;
             break;
         case PLAYER_O:
             cout<<"Player O wins!"<<endl;
             break;
     }
    return 0;
}
