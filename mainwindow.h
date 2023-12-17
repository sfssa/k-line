#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVector>
#include <QPointF>
#include <QPalette>
#include <QColor>
#include <QWheelEvent>
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
    // 计算有多少个横坐标值
    int getXMargin();
    // 计算有多少个纵坐标值
    int getYMargin();
protected:
    // 窗口重绘时调用
    void paintEvent(QPaintEvent * event);
    // 在窗口拖动鼠标时调用
    void wheelEvent(QWheelEvent* event);
    // 放大或缩小窗口部件时调用
    void resizeEvent(QResizeEvent* event);
private:
    // 设置窗口背景颜色
    void setBackgroundColor();
    // 绘制横线
    void drawRowLines(QPainter* painter, const QRectF &gridRect);
    // 绘制竖线
    void drawColLines(QPainter* painter, const QRectF &gridRect);
private:
    // UI界面
    Ui::MainWindow *ui;
    // 最小线间隔
    int m_minGap;
    // 最大线间隔
    int m_maxGap;
    // 当前线间隔
    float m_gap;
    // 竖线初始x坐标
    float m_startX;
    // 横线初始y坐标
    float m_startY;
    // 细笔
    QPen m_lightPen;
    // 粗笔
    QPen m_darkPen;
};

#endif // MAINWINDOW_H
