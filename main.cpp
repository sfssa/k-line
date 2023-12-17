#include "mainwindow.h"
#include <QApplication>
#include "databasehandler.h"
#include "utils.h"
#include "data.h"

void test_timestmapToReadableTime(){
    uint64_t timestamp = 1702720260000;
    QString ret = timestmapToReadableTime(timestamp);
    qDebug() << ret;
}

void test_DatabaseHandler(){
    // DatabaseHandler::GetInstance()->createTable("btcusdt");
    // std::vector<Point> arr;
    // DatabaseHandler::GetInstance()->getAUDHUFHistoryData(arr);
    // DatabaseHandler::GetInstance()->getInstidHistoricalData("btcusdt");
    DatabaseHandler::GetInstance()->getMinCloseOfInstid("btcusdt");
    DatabaseHandler::GetInstance()->getMaxCloseOfInstid("btcusdt");
}

void test_utils(){
    QVector<Point> points;
    getPointsByHistorialData(points);
}

void test_parse(){
    // 进行解析
    Data* d = new Data();
}

void test_draw(){

}

void test_requestHistoricalData(){
    // Data* data = new Data();
    // data->testCurl();
    // DatabaseHandler::GetInstance();
    // data->requestHistoricalData();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QVector<Point> points;
    getPointsByHistorialData(points);
    w.drawKLine(points);
    test_DatabaseHandler();
    // test_timestmapToReadableTime();
    // test_requestHistoricalData();
    // test_parse();
    // test_DatabaseHandler();
    // test_utils();
    // test_timestmapToReadableTime();
    return a.exec();
}
