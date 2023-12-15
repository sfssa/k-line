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
    // DatabaseHandler::GetInstance()->GetInstance()->createTable("BTCUSDT");
    std::vector<AUDHUF> arr;
    DatabaseHandler::GetInstance()->GetInstance()->getAUDHUFHistoryData(arr);
}

void test_parse(){
    // R"()"禁止括号内的所有转义字符
    std::string beforeParse = R"(
        {
            "code":"0",
            "msg":"",
            "data":[
             [
                "1597026383085",
                "3.721",
                "3.743",
                "3.677",
                "3.708",
                "8422410",
                "22698348.04828491",
                "12698348.04828491",
                "1"
            ],
            [
                "1597026383085",
                "3.731",
                "3.799",
                "3.494",
                "3.72",
                "24912403",
                "67632347.24399722",
                "37632347.24399722",
                "1"
            ]
            ]
        }
    )";
    // 进行解析

    // 输出解析后的数据
}

void test_requestHistoricalData(){
    Data* data = new Data();
    data->requestHistoricalData();
    // qDebug() << "===>" << QSslSocket::sslLibraryBuildVersionString();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    test_DatabaseHandler();
    // test_timestmapToReadableTime();
    // test_requestHistoricalData();
    return a.exec();
}
