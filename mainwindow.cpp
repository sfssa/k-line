#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::drawKLine(QVector<Point>& points)
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
    // 画出网格背景图
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
//    QWidget::wheelEvent(event);
//    if (event->angleDelta().y() > 0) {
//        m_gap += 0.1;
//    }
//    else if (event->angleDelta().y() < 0) {
//        m_gap -= 0.1;
//    }

//    if (m_gap >= m_maxGap) {
//        m_gap = m_minGap;
//    }
//    else if (m_gap <= m_minGap) {
//        m_gap = m_maxGap;
//    }

//    this->update();
    event->ignore();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    m_startX = width() / 2;
    m_startY = height() / 2;
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
    painter->setPen(m_darkPen);
    while (true) {
        painter->drawLine(QPointF(gridRect.left(), biggerY), QPointF(gridRect.right(), biggerY));
        biggerY += m_gap;
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
    painter->setPen(m_darkPen);
    while (true) {
        painter->setPen(QColor(Qt::black));
        QString xValue = QString::number(lineCount * 1);
        QFontMetrics fm(painter->font());
        int textWidth = fm.width(xValue);
        painter->drawText(QPointF(left - textWidth / 2, gridRect.bottom() + 10), xValue);

        painter->setPen(m_lightPen);
        painter->drawLine(QPointF(left, gridRect.top()), QPointF(left, gridRect.bottom()));
        left += m_gap;

        if (left >= gridRect.right()) {
            break;
        }
        ++lineCount;
        if (lineCount %10 == 0) {
            painter->setPen(m_darkPen);
            // lineCount = 0;
        } else {
            painter->setPen(m_lightPen);
        }
    }
}



