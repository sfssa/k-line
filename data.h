#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QSslSocket>
#include <QJsonArray>
#include "data.h"

// BTC_USDT的历史数据API接口
const QString BTC_USDT_HISTORY_DATA_API = "https://www.okx.com/api/v5/market/history-candles?instId=BTC-USDT";
// 行情数据结构体
struct MarketData{
public:
    // 时间戳
    QString timestamp;
    // 开盘价
    double open;
    // 最高价
    double high;
    // 最低价
    double low;
    // 收盘价
    double close;
    // 交易量-张
    QString volume;
    // 交易量-币
    QString volCcy;
    // 交易量-计价货币
    QString volCcyQuote;
};

struct AUDHUF{
    // 时间戳
    QString timestamp;
    // 开盘价
    float open;
    // 最高价
    float high;
    // 最低价
    float low;
    // 收盘价
    float close;
};

struct Point{
    // 横坐标是时间间隔(1min)
    QString xTime;
    // 纵坐标是收盘价
    float yClose;
};

class Data : public QObject
{
    Q_OBJECT
public:
    Data();
    ~Data();
    void requestHistoricalData();
    // 解析获得的历史数据
    bool parse(QString& data);
public slots:
    void onFinished(QNetworkReply *);
public slots:
private:
    QNetworkAccessManager *m_netManger;
    QNetworkReply* m_reply;
    // QVector<Point>* m_arr;
    QVector<MarketData>* m_arr;
};


#endif //DATA_H
