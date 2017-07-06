#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>
#include <list>
#include <algorithm>
#include <stdlib.h>

#include "tictactoe.h"

using namespace std;

// Public Methods
// CTOR
TicTac::TicTac()
{
    init();
}

// DTOR
TicTac::~TicTac()
{
}

void TicTac::toss()
{
    srand(time(NULL));
    if ((rand() % 2) == 0)
    {
        _whosTurn = TicTac::_COMPUTER;
        cout << "\n COMPUTER WINS THE TOSS" << endl;
    }
    else
    {
        _whosTurn = TicTac::_HUMAN;
        cout << "\n YOU WIN THE TOSS" << endl;
    }
    _tossWinner = _whosTurn;
}

void TicTac::printBoard()
{
    cout << "+-----+-----+-----+" << endl;
    for (int i=1; i < 10; i+=3)
    {
        cout << "|" << std::right
             << setw(5) <<  pos[i] 
             << "|" << setw(5) << pos[i+1] 
             << "|" << setw(5) << pos[i+2]
             << "|" << endl;
        cout << "+-----+-----+-----+" << endl;
    }
}

TicTac::Turn TicTac::whosTurn()
{
    return _whosTurn;
}

void TicTac::promptToPlay()
{
    int position;
    cout << "\n\nYour Move: " << endl;
    cout << "\nChoose Your Position (1-9): ";

    while (1)
    {
        cin.clear();
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        ss >> position;
        if (ss.eof())
        {
            if (position >= 1 && position <= 9 && empty(position))
            {
                break;
            }
        }

        cout << "\nChoose Your Position (1-9): ";

    }
    cout << "\033[2J\033[1;1H";
    cout << "\nSetting Your Pawn @ Position " << position << endl;
    pos[position] = (_tossWinner == TicTac::_HUMAN) ? 1 : 0;
    _whosTurn  = TicTac::_COMPUTER;
    _moves++;
}

void TicTac::startGame()
{
    toss();

    do {

        if (whosTurn() == TicTac::_COMPUTER) 
            play();
        else
            promptToPlay();

        printBoard();

    } while (!done());
    _moves = 0;
}

void TicTac::play()
{
    cout << "\nComputer Move ... " << endl;
    int myPawn = (_tossWinner == TicTac::_COMPUTER) ? 1 : 0;
    std::list<int>  myPos;
    for (int i=1;i < 10; i++)
    {
        if (empty(i))
            myPos.push_back(i);
    }

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1,9);
    int mychoice;

    do {
        mychoice = distribution(generator);
        auto it = std::find(myPos.begin(), myPos.end(), (int)mychoice);

        if (it == myPos.end())
           continue;
        else
           break;
    } while (1);

    pos[mychoice] = myPawn;
    cout << "\033[2J\033[1;1H";
    cout << "\nSetting My Pawn @ Position " << mychoice << endl;
    _whosTurn  = TicTac::_HUMAN;
    _moves++;
}

bool TicTac::done()
{
    int pawn;
    if (rowMatched(&pawn) || columnMatched(&pawn) || diagonalMatched(&pawn))
    {
        std::string Winner;
        if (pawn)
            Winner = (_tossWinner == TicTac::_COMPUTER) ? "COMPUTER" : "HUMAN";
         else
            Winner = (_tossWinner == TicTac::_HUMAN) ? "COMPUTER" : "HUMAN";


        cout << "Game Over: " <<  Winner << "  Wins the Game " << endl;
        return true;
    }
    else
    {
        if (_moves == 9)
        {
            cout << "\n Tie Game.. Nobody Wins" << endl;
            return true;
        }
        else
        {
            return false;
        }
    }
}

// Private Function
void TicTac::init()
{
    for (int i=0; i < 10; i++)
        pos[i] = -1;

    _moves = 0;
}

bool TicTac::empty(int pos1)
{
    if (pos1 <= 1 && pos1 >= 10) return false;

    return (pos[pos1] == -1 ) ? true : false;
}

bool TicTac::rowMatched(int *pawn)
{
    for (int i=1; i < 9; i+=3)
    {
        if ((pos[i] == pos[i+1]) && (pos[i]  == pos[i+2])
            && !empty(i) && !empty(i+1) && !empty(i+2))
        {
            cout << "\nROW Matched ROW Starting @" << i << " : " 
                 << pos[i] << "," << pos[i+1] << "," << pos[i+2] << endl;
            *pawn = pos[i];
            return true;
        }
    }
    return false;
}

bool TicTac::columnMatched(int *pawn)
{
    for (int i=1; i <= 3 ; i++)
    {
        if ((pos[i] == pos[i+3]) && (pos[i] == pos[i+6])
            && !empty(i) && !empty(i+3) && !empty(i+6))
        {
            cout << "\nCOLUMN Matched Starting @ " << i << " : " 
                 << pos[i] << "," << pos[i+3] << "," << pos[i+6] << endl;
            *pawn = pos[i];
            return true;
        }
    }
    return false;
}

bool TicTac::diagonalMatched(int *pawn)
{
    if (!empty(1) && !empty(5) && !empty(9))
    {
        if ((pos[1] == pos[5]) && (pos[1] == pos[9]))
        {
            //cout << "\nDiagonal Matched " << endl;
            *pawn = pos[1];
            return true;
        }
    }
    if (!empty(3) && !empty(5) && !empty(7))
    {
        if ((pos[3] == pos[5]) && (pos[3] == pos[7]))
        {
            //cout << "\nDiagonal Matched " << endl;
            *pawn = pos[3];
            return true;
        }
    }
    return false;
}

// Main Routine

int main(int argc, char **argv)
{
    TicTac  t;
    t.startGame();
    return 0;
}
