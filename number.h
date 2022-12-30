#ifndef NUMBER_H
#define NUMBER_H


class number
{
public:
    number();

    bool randNew();
    void restart();
    bool moveLeft();
    bool moveup();
    bool moveRight();
    bool moveDown();
    void rotate();
    bool isOver();
    int getScore();




    int data[4][4] = {{0}};
    int status;
    int score;
};

#endif // NUMBER_H
