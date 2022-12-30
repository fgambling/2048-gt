#include "number.h"
#include <vector>
#include <cstdlib>



#define N 4
#define TARGET 2048

//GAME STATUS
#define S_FAIL 0
#define S_WIN 1
#define S_NORMAL 2


number::number()
{
    score = 0;
    randNew();
    randNew();
}

bool number::isOver()
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if ((j + 1 < N) && (data[i][j] * data[i][j+1] == 0 || data[i][j] == data[i][j+1])) return false;
            if ((i + 1 < N) && (data[i][j] * data[i+1][j] == 0 || data[i][j] == data[i+1][j])) return false;
        }
    }
    return true;
}

bool number::moveLeft()
{
    int temp[N][N];
    for (int i = 0; i < N; ++i)
    {
        int preVal = 0;
        int curPos = 0;
        //int index = 1;
        for (int j = 0; j < N; ++j)
        {
            temp[i][j] = data[i][j];
            if (data[i][j] == 0)
            {
                continue;
            }

            if (preVal == 0)
            {
                preVal = data[i][j];
            }

            else if (preVal == data[i][j])
            {
                data[i][curPos] = preVal * 2;
                score += preVal;
                preVal = 0;
                if (data[i][curPos] == TARGET) status = S_WIN;
                ++curPos;
            }

            else if (preVal != data[i][j])
            {
                data[i][curPos] = preVal;
                preVal = data[i][j];
                ++curPos;
            }
            data[i][j] = 0;
        }
        if (preVal) data[i][curPos] = preVal;
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (data[i][j] != temp[i][j]) return true;
        }
    }
    return false;
}

bool number::moveup()
{
    bool update;
    rotate();
    rotate();
    rotate();
    update = moveLeft();
    rotate();
    return update;
}

bool number::moveRight()
{
    bool update;
    rotate();
    rotate();
    update = moveLeft();
    rotate();
    rotate();
    return update;
}

bool number::moveDown()
{
    bool update;
    rotate();
    update = moveLeft();
    rotate();
    rotate();
    rotate();
    return update;
}

//clockwise rotate
void number::rotate()
{
    int temp[N][N] = {{0}};
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            temp[i][j] = data[N - 1 - j][i];
        }
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            data[i][j] = temp[i][j];
        }
    }

}

bool number::randNew()
{
    std::vector<int> emptyPos;
    // store empty pos
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (data[i][j] == 0) {
                emptyPos.push_back(i * 4 + j);
            }
        }
    }
    if (emptyPos.size() == 0) {
        return false;
    }
    // random choose 1 empty pos
    int value = emptyPos[rand() % emptyPos.size()];
    // the probability of 4 is 10%
    data[value / 4][value % 4] = rand() % 10 == 1 ? 4 : 2;
    return true;
}



void number::restart()
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            data[i][j] = 0;
        }
    }

    randNew();
    randNew();
    status = S_NORMAL;
    score = 0;
}

int number::getScore()
{
    return score;
}


