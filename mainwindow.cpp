#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // drawBackground();

    m_minGap = 10;
    m_maxGap = 50;
    m_gap = (m_minGap + m_maxGap) / 2;
    m_startX = this->width() / 2;
    m_startY = this->height() / 2;
    m_lightPen = QPen(QColor(222, 222, 222));
    m_darkPen = QPen(QColor(222, 222, 222));
    m_darkPen.setWidth(2);

    setBackgroundColor();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawKLine(std::vector<Point> &points)
{

}

int MainWindow::getXMargin()
{
    return 0;
}

int MainWindow::getYMargin()
{
    return 0;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    painter.setPen(QPen(Qt::black, 2));
//    painter.drawLine(50, 600, 50, 50);
//    painter.drawLine(25, 75, 50, 50);
//    painter.drawLine(75, 75, 50, 50);
//    painter.drawLine(50, 600, 1250, 600);
//    painter.drawLine(1225, 575, 1250, 600);
//    painter.drawLine(1225, 625, 1250, 600);
//    int x = 50;
//    int y = 600;
//    int scope = 100;
//    for(int i = 1; i <= 11; ++i){
//        painter.drawLine(x + i * scope, 600, x + i * scope, 590);
//    }

//    for( int i = 1; i <= 5; ++i){
//        painter.drawLine(50, 600 - i * scope, 60, 600 - i * scope);
//    }
    QWidget::paintEvent(event);
    QPainter painter(this);
    QBrush backgroundBrush(QColor(250, 250, 250));
    painter.fillRect(rect(), backgroundBrush);
    QRectF rect(100, 100, 900, 500);
    drawRowLines(&painter, rect);
    drawColLines(&painter, rect);
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    QWidget::wheelEvent(event);
    if (event->angleDelta().y() > 0) {
        m_gap += 0.1;
    }
    else if (event->angleDelta().y() < 0) {
        m_gap -= 0.1;
    }

    if (m_gap >= m_maxGap) {
        m_gap = m_minGap;
    }
    else if (m_gap <= m_minGap) {
        m_gap = m_maxGap;
    }

    this->update();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    m_startX = this->width() / 2;
    m_startY = this->height() / 2;
    update();
}

void MainWindow::setBackgroundColor()
{
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(250, 250, 250));
    setPalette(palette);
    setAutoFillBackground(true);
}

void MainWindow::drawRowLines(QPainter *painter, const QRectF &gridRect)
{
    int lineCount = 0;
    float biggerY = gridRect.top();
    // float smallerY = gridRect.bottom();
    painter->setPen(m_darkPen);
    while (true) {
        painter->drawLine(QPointF(gridRect.left(), biggerY), QPointF(gridRect.right(), biggerY));
        // painter->drawLine(QPointF(gridRect.left(), smallerY), QPointF(gridRect.right(), smallerY));

        biggerY += m_gap;
        // smallerY -= m_gap;
        if (biggerY >= gridRect.bottom()) {
            break;
        }
        ++lineCount;
        if (lineCount == 10) {
            painter->setPen(m_darkPen);
            lineCount = 0;
        } else {
            painter->setPen(m_lightPen);
        }
    }
}

void MainWindow::drawColLines(QPainter *painter, const QRectF &gridRect)
{
    int lineCount = 0;
    float left = gridRect.left();
    // float smallerX = gridRect.right();
    painter->setPen(m_darkPen);
    while (true) {
        painter->drawLine(QPointF(left, gridRect.top()), QPointF(left, gridRect.bottom()));
        // painter->drawLine(QPointF(smallerX, gridRect.top()), QPointF(smallerX, gridRect.bottom()));
        // 添加坐标
//        int x = 0;
//        QString text = QString::number(x++);
//        QRectF textRect(x - 25, gridRect.bottom() + 5, 50, 20);
//        painter->drawText(textRect, Qt::AlignHCenter, text);
        left += m_gap;
        // smallerX -= m_gap;
        if (left >= gridRect.right()) {
            break;
        }
        ++lineCount;
        if (lineCount == 10) {
            painter->setPen(m_darkPen);
            lineCount = 0;
        } else {
            painter->setPen(m_lightPen);
        }
    }
}



