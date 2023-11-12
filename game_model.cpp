#include <time.h>
#include <stdlib.h>
#include "game_model.h"

GameModel::GameModel()
  : mRow(kRow),
    mCol(kCol),
    totalMineNumber(kMineCount),
    timerSeconds(kTime),
    gameState(PLAYING)
{
}

GameModel::~GameModel()
{
}

void GameModel::createGame(int row, int col, int mineCount, GameLevel level)
{
    gameMap.clear();//clearing gurbage values
    mRow = row;
    mCol = col;
    totalMineNumber = mineCount;
    curMineNumber = mineCount;
    gameState = PLAYING;
    gameLevel = level;
    timerSeconds = 0;

    for(int i = 0; i < mRow; i++)
    {
        std::vector<MineBlock> lineBlocks; // vector of a mineblock struct named lineBlocks
        for(int j = 0; j < mCol; j++)
        {
            MineBlock mineBlock;
            mineBlock.curState = UN_DIG;
            mineBlock.valueFlag = 0;
            lineBlocks.push_back(mineBlock);//keeping values in vector
        }
        gameMap.push_back(lineBlocks);//keeping values
    }


    srand((unsigned int)time(0));
    int k = totalMineNumber;
    while(k > 0)
    {
        int pRow = rand() % mRow;
        int pCol = rand() % mCol;
        if(gameMap[pRow][pCol].valueFlag != -1)
        {
            gameMap[pRow][pCol].valueFlag = -1; //putting bombs in blocks randomly
            k--;
        }
    }

    for(int i = 0; i < mRow; i++)
    {
        for(int j = 0; j < mCol; j++)
        {

            if(gameMap[i][j].valueFlag != -1) // a block doesnt have a bomb
            {

                for(int y = -1; y <= 1; y++) // going across row (up,current,down)
                {
                    for(int x = -1; x <= 1; x++) // going across column (left,current,right)
                    {
                        if(i + y >= 0
                            && i + y < mRow
                            && j + x >= 0
                            && j + x < mCol    // conditions for valid block
                            && gameMap[i + y][j + x].valueFlag == -1   //condition for a bomb
                            && !(x == 0 && y == 0)) // it is that block itself
                        {
                            gameMap[i][j].valueFlag++;  //counting bombs in adjacent blocks of a particular block
                        }
                    }
                }
            }
        }
    }
}

void GameModel::restartGame()
{
    createGame(mRow, mCol, totalMineNumber, gameLevel);
}

void GameModel::digMine(int m, int n) // what happens after clicking a block
{

    if(gameMap[m][n].valueFlag > 0
        && gameMap[m][n].curState == UN_DIG)
    {
        gameMap[m][n].curState = DIGGED;  // just one block is digged
    }


    if(gameMap[m][n].valueFlag == 0
        && gameMap[m][n].curState == UN_DIG)
    {
        gameMap[m][n].curState = DIGGED;// that block is digged
        for(int y = -1; y <= 1; y++)  // going across row (up,current,down)
        {
            for(int x = -1; x <= 1; x++) // going across row (left,current,right)
            {
                if(m + y >= 0
                    && m + y < mRow
                    && n + x >= 0
                    && n + x < mCol // conditions for valid block
                    && !(x == 0 && y == 0)) // it is that block itself
                {
                    digMine(m + y, n + x);  //several mines are digged untill valueFlag of block is not zero
                }
            }
        }
    }

    if(gameMap[m][n].valueFlag == -1) //when the block contains bomb
    {
        gameState = OVER;
        gameMap[m][n].curState = BOMB;
    }

    checkGame();
}

void GameModel::markMine(int m, int n)
{
    if(gameMap[m][n].curState == UN_DIG)
    {
        if(gameMap[m][n].valueFlag == -1)
        {
            gameMap[m][n].curState = MARKED;
        }
        else
        {
            gameState = FAULT;
            gameMap[m][n].curState = WRONG_BOMB;
        }
        curMineNumber--;
    }
    else if(gameMap[m][n].curState == MARKED || gameMap[m][n].curState == WRONG_BOMB)
    {
        gameMap[m][n].curState = UN_DIG;
        gameState = PLAYING;
        curMineNumber++;
    }

    checkGame();
}

void GameModel::checkGame()
{

    if(gameState == OVER)
    {

        for(int i = 0; i < mRow; i++)
        {
            for(int j = 0; j < mCol; j++)
            {
                if(gameMap[i][j].valueFlag == -1)
                {
                    gameMap[i][j].curState = BOMB;
                }
            }
        }
        return;
    }

    if(gameState != FAULT)
    {
        for(int i = 0; i < mRow; i++)
        {
            for(int j = 0; j < mCol; j++)
            {
                if(gameMap[i][j].curState == UN_DIG)
                {
                    gameState = PLAYING;
                    return;
                }
            }
        }

        gameState = WIN;
    }
}
