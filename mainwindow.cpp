#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QColor>
#include <QLabel>
#include <QFont>
#include <QPushButton>
#include "number.h"
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("2048");
    this->setFixedSize(500,700);

    //declare number class
    record = new number;
    conti = false;

    //set 2048 label
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font("Microsoft YaHei", 10, 1000);
    label->setText("2048");
    label->setFont(font);
    label->setGeometry(50, 40, 200, 100);
    label->setStyleSheet("font-size:60px;color:#b8860b");

    //set r/q label
    QLabel * rLable = new QLabel;
    rLable->setParent(this);
    rLable->setText("R - restart");
    rLable->setGeometry(70, 130, 200, 100);
    rLable->setStyleSheet("font-size:20px;color:#b8860b");

    QLabel * qLable = new QLabel;
    qLable->setParent(this);
    qLable->setText("Q - quit");
    qLable->setGeometry(70, 160, 200, 100);
    qLable->setStyleSheet("font-size:20px;color:#b8860b");

    //set restart button
    QPushButton * restart = new QPushButton;
    restart->setParent(this);
    restart->setText("Restart");
    restart->move(320, 170);
    restart->setFixedSize(100, 50);
    restart->setStyleSheet("background-color: burlywood; color: gainsboro; padding: -1");
    restart->setFont(QFont("Microsoft YaHei", 20));

    connect(restart, &QPushButton::clicked, [=]()
    {
        record->restart();
        update();
    });

}

void MainWindow::paintEvent(QPaintEvent*)
{
    //set background color to antiquewhite
    QPainter painter(this);

    QColor color("#faebd7");
    painter.setPen(Qt::transparent);
    painter.setBrush(color);
    painter.drawRect(this->rect());

    //draw score
    //1.draw rect
    painter.setRenderHint(QPainter::Antialiasing);
    color.setNamedColor("burlywood");
    painter.setBrush(color);
    painter.setPen(Qt::transparent);
    QRect rect(250, 40, 200, 100);
    painter.drawRoundedRect(rect, 15, 15);

    //2.draw text
    QString str = QString("SCORE    %1").arg(record->score);

    QPen pen;
    pen.setColor("gainsboro");
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    painter.setFont(QFont("Microsoft YaHei", 30));
    painter.drawText(QRect(255, 70, 250, 100), str);


    //draw game rect
    rect.setRect(50, 250, 400, 400);
    painter.setPen(Qt::transparent);
    painter.drawRoundedRect(rect, 15, 15);

    //draw number
    int xBase = 50;
    int yBase = 250;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            rect.setRect(xBase + 98 * j + 8, yBase + 98 * i + 8, 90, 90);
            if (record->data[i][j] == 0) color.setNamedColor("ghostwhite");
            else if (record->data[i][j] == 2) color.setNamedColor("linen");
            else if (record->data[i][j] == 4) color.setNamedColor("cornsilk");
            else if (record->data[i][j] == 8) color.setNamedColor("darksalmon");
            else if (record->data[i][j] == 16) color.setNamedColor("darkorange");
            else if (record->data[i][j] == 32) color.setNamedColor("lightcoral");
            else if (record->data[i][j] == 64) color.setNamedColor("indianred");
            else if (record->data[i][j] == 128) color.setNamedColor("yellow");
            else if (record->data[i][j] == 256) color.setNamedColor("gold");
            else if (record->data[i][j] == 512) color.setNamedColor("goldenrod");
            else if (record->data[i][j] == 1024) color.setNamedColor("aqua");
            else if (record->data[i][j] == 2048) color.setNamedColor("deepskyblue");
            else if (record->data[i][j] == 4096) color.setNamedColor("deeppink");

            painter.setBrush(color);
            painter.drawRoundedRect(rect, 5, 5);

            if (record->data[i][j] != 0)
            {
                if (record->data[i][j] == 2 || record->data[i][j] == 4) pen.setColor("dimgrey");
                else pen.setColor("white");
                pen.setWidth(40);
                painter.setPen(pen);
                if (record->data[i][j] == 8192) painter.drawText(rect, "error", Qt::AlignHCenter | Qt::AlignVCenter);
                else painter.drawText(rect, QString::number(record->data[i][j]), Qt::AlignHCenter | Qt::AlignVCenter);
                painter.setPen(Qt::transparent);
            }
        }
    }

}

//record key press
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    bool change = false;
    switch (event->key())
    {
    case Qt::Key_W:
        change = record->moveup();
        break;
    case Qt::Key_Up:
        change = record->moveup();
        break;
    case Qt::Key_S:
        change = record->moveDown();
        break;
    case Qt::Key_Down:
        change = record->moveDown();
        break;
    case Qt::Key_A:
        change = record->moveLeft();
        break;
    case Qt::Key_Left:
        change = record->moveLeft();
        break;
    case Qt::Key_D:
        change = record->moveRight();
        break;
    case Qt::Key_Right:
        change = record->moveRight();
        break;
    case Qt::Key_R:
        record->restart();
        break;
    case Qt::Key_Q:
        this->close();
        break;
    default:
        break;
    }

    if (change)
    {
        record->randNew();
    }
    update();

    //if 2048 occurs, prompt message box
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (record->data[i][j] == 2048 && !conti)
            {
                QMessageBox myBox;
                myBox.setWindowTitle("You win");
                myBox.setText("You win!");
                QPushButton * reBtn = myBox.addButton(tr("Restart"), QMessageBox::ActionRole);
                QPushButton * conBtn = myBox.addButton(tr("Continue"), QMessageBox::ActionRole);

                myBox.exec();
                if (myBox.clickedButton() == reBtn)
                {
                    record->restart();
                    update();
                }
                else if (myBox.clickedButton() == conBtn)
                {
                    conti = true;
                }
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

