#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVector>
#include <QPointF>
#include <QPainter>
#include "data.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // 在构造函数调用绘制背景函数
    explicit MainWindow(QWidget *parent = nullptr);
    // 析构函数
    ~MainWindow();
    // 根据数据画K线
    void drawKLine(std::vector<Point>& points);
    // 绘制表格背景
    void drawBackground(QPaintEvent* event);
    // 计算有多少个横坐标值
    int getXMargin();
    // 计算有多少个纵坐标值
    int getYMargin();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
