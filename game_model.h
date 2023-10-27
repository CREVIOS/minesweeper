#ifndef GAMEMODEL_H
#define GAMEMODEL_H


#include <vector>


enum BlockState
{
    UN_DIG,
    DIGGED,
    MARKED,
    BOMB,
    WRONG_BOMB
};

struct MineBlock
{
    BlockState curState;
    int valueFlag;
};


enum GameState
{
    PLAYING,
    FAULT,
    OVER,
    WIN
};


enum GameLevel
{
    BASIC,
    MEDIUM,
    HARD
};


const int kRow = 15;
const int kCol = 20;
const int kMineCount = 50;
const int kTime = 0;
// ----------------------------------------------- //

class GameModel
{
public:
    GameModel();
    virtual ~GameModel();
public:
    void digMine(int m, int n);
    void markMine(int m, int n);
    void createGame(int row = kRow, int col = kCol, int mineCount = kMineCount, GameLevel level = MEDIUM);
    void restartGame();
    void checkGame();
public:
    std::vector<std::vector<MineBlock>> gameMap;
    int mRow;
    int mCol;
    int totalMineNumber;
    int curMineNumber;
    int timerSeconds;


    GameState gameState;
    GameLevel gameLevel;
};

#endif // GAMEMODEL_H
