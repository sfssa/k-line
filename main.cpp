#include "mainwindow.h"
#include <QApplication>
#include "databasehandler.h"
#include "utils.h"
#include "data.h"

void test_timestmapToReadableTime(){
    // 获得的时间是毫秒级，需要/1000
    uint64_t timestamp = 1702534140;
    QString ret = QString::fromStdString(timestmapToReadableTime(timestamp));
    qDebug() << ret;
}

void test_DatabaseHandler(){
    DatabaseHandler::GetInstance()->createTable("btcusdt");
    // std::vector<Point> arr;
    // DatabaseHandler::GetInstance()->getAUDHUFHistoryData(arr);
}

void test_parse(){
    // 进行解析
    Data* d = new Data();
}

void test_requestHistoricalData(){
    Data* data = new Data();
    // data->testCurl();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    test_DatabaseHandler();
    // test_timestmapToReadableTime();
    // test_requestHistoricalData();
    // test_parse();
    return a.exec();
}
