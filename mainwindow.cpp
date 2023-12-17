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

        this->setBackgroundColor();
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
    drawRowLines(&painter);
    drawColLines(&painter);
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

void MainWindow::drawRowLines(QPainter *painter)
{
    int lineCount = 0;
    float biggerY = m_startY;
    float smallerY = m_startY;

    painter->setPen(this->m_darkPen);

    while (true) {
        painter->drawLine(QPointF(0.0, biggerY), QPointF(this->width(), biggerY));
        painter->drawLine(QPointF(0.0, smallerY), QPointF(this->width(), smallerY));

        biggerY += m_gap;
        smallerY -= m_gap;
        if (smallerY <= 0 || biggerY >= this->height()) {
            break;
        }

        // 每间隔一定数量的线，就画一条粗一点的横线
        lineCount += 1;
        if (lineCount == 10) {
            painter->setPen(m_darkPen);
            lineCount = 0;
        }
        else {
            painter->setPen(m_lightPen);
        }
    }
}

void MainWindow::drawColLines(QPainter *painter)
{
    int lineCount = 0;
    float biggerX = m_startX;
    float smallerX = m_startX;

    painter->setPen(m_darkPen);

    while (true) {
        painter->drawLine(QPointF(biggerX, 0.0), QPointF(biggerX, this->height()));
        painter->drawLine(QPointF(smallerX, 0.0), QPointF(smallerX, this->height()));

        biggerX += m_gap;
        smallerX -= m_gap;
        if (smallerX <= 0 || biggerX >= this->width()) {
            break;
        }

        // 每间隔一定数量的线，就画一条粗一点的竖线
        lineCount += 1;
        if (lineCount == 10) {
            painter->setPen(m_darkPen);
            lineCount = 0;
        }
        else {
            painter->setPen(m_lightPen);
        }
    }

}


