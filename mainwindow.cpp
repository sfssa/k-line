#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // drawBackground();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawKLine(std::vector<Point> &points)
{

}

void MainWindow::drawBackground(QPaintEvent *event)
{

}

int MainWindow::getXMargin()
{

}

int MainWindow::getYMargin()
{

}
