#pragma once

#include <iostream>

class TTT {

    private:

        int **board;
        int currMove;
        uint8_t numMoves;


    public:
        TTT();
        ~TTT();

        void printBoard();

        bool isEmpty(int i, int j);
        int getMove();
        void changeMove();
        void place(int i, int j);
        int check();
        int getNumMoves();

        std::vector<float> getBoardVec();
        std::vector<int> getEmptyPositionsVec();



};


TTT::TTT(){
    numMoves = 0;

    int randMove = (rand() % 2);
    currMove = randMove == 0 ? randMove-1 : randMove;

    this->board = new int*[3];
    for(int i = 0; i < 3; i++)
        this->board[i] = new int[3];

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            this->board[i][j] = 0;
}

TTT::~TTT(){
    for(int i = 0; i < 3; i++)
        delete [] this->board[i];
    delete [] this->board;
}

void TTT::printBoard(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++)
            std::cout << this->board[i][j] << "  ";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return;
}

bool TTT::isEmpty(int i, int j){
    return !this->board[i][j];
}

int TTT::getMove(){
    return this->currMove;
}

void TTT::changeMove(){
    currMove = currMove == 1 ? -1 : 1;
}

void TTT::place(int i, int j){
    numMoves++;
    this->board[i][j] = currMove;
}

int TTT::check(){
    int res = 0;

    // rows
    for(int i = 0; i < 3; i++){
        res = board[i][0] + board[i][1] + board[i][2];
        if(abs(res) == 3)
            return res/3;
    }

    // cols
    res = 0;
    for(int i = 0; i < 3; i++){
        res = board[0][i] + board[1][i] + board[2][i];
        if(abs(res) == 3)
            return res/3;
    }

    // principal diagonal
    res = 0;
    res = board[0][0] + board[1][1] + board[2][2];
    if(abs(res) == 3)
        return res/3;
    
    // second diagonal
    res = 0;
    res = board[0][2] + board[1][1] + board[2][0];
    if(abs(res) == 3)
        return res/3;

    return 0;
}

int TTT::getNumMoves(){
    return this->numMoves;
}

std::vector<float> TTT::getBoardVec(){
    std::vector<float> boardVec;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            boardVec.push_back(board[i][j]);

    return boardVec;
}

std::vector<int> TTT::getEmptyPositionsVec(){
    std::vector<int> blanksVec;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(isEmpty(i, j))
                blanksVec.push_back(i * 3 + j);

    return blanksVec;
}