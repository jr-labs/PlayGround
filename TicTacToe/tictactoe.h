#pragma once

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <string>

using namespace std;

class TicTac
{
public:
    enum Turn {
        _COMPUTER  = 0,
        _HUMAN     = 1
    };

    TicTac();
    ~TicTac();

    void toss();
    void printBoard();
    Turn whosTurn();
    void promptToPlay();
    void play();
    void startGame();
    bool done();
    
private:
    void init();
    bool empty(int pos);
    bool rowMatched(int *pawn);
    bool columnMatched(int *pawn);
    bool diagonalMatched(int *pawn);
   
    
    int   pos[10];  // 0 - RESERVED  1-9 Positions
    Turn  _whosTurn;
    Turn  _tossWinner;
    int   _moves;
};
