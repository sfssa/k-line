#ifndef DATA_H
#define DATA_H
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QSslSocket>

// BTC_USDT的历史数据API接口
const QString BTC_USDT_HISTORY_DATA_API = "https://www.okx.com/api/v5/market/history-candles?instId=BTC-USDT";
// 行情数据结构体
struct MarketData{
public:
    // 时间戳
    std::string timestamp;
    // 开盘价
    double open;
    // 最高价
    double high;
    // 最低价
    double low;
    // 收盘价
    double close;
    // 交易量-张
    std::string volume;
    // 交易量-币
    std::string volCcy;
    // 交易量-计价货币
    std::string volCcyQuote;
    // 是否完结
    std::string confitm;
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
    bool parse(std::vector<MarketData>& arr);
public slots:
    void finishedSlot(QNetworkReply*);
    void onFinished();
    void onError(QNetworkReply::NetworkError errorCode);
public slots:
private:
    QNetworkAccessManager *m_NetManger;
    QNetworkReply* m_Reply;

};


#endif // DATA_H
