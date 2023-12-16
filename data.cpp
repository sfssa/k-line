#include "data.h"
#include "utils.h"

Data::Data()
{
    requestHistoricalData();
    m_arr = new QVector<Point>();
    m_arr->reserve(100);
}

Data::~Data()
{
    delete m_netManger;
    delete m_reply;
}

void Data::requestHistoricalData()
{
    m_netManger = new QNetworkAccessManager;
    QUrl url(BTC_USDT_HISTORY_DATA_API);

    m_reply = m_netManger->get(QNetworkRequest(url));

    QObject::connect(m_netManger, SIGNAL(finished(QNetworkReply*)),
                         this, SLOT(onFinished(QNetworkReply*)));
}

bool Data::parse(QString& data)
{
    // qDebug() << "-------------------------------";
    QVector<MarketData> arr;
    arr.reserve(100);
    // 解析
    int cur = 0;
    while(data[cur] != '['){
        ++cur;
    }

    if(data[++cur] == '['){
        ++cur;
        int begin;
        int end;
        while(true){
            begin = cur;
            end = cur + 1;
            MarketData temp;
            // 解析时间戳
            QString timestamp;
            while(data[end] != '\"'){
                ++end;
            }
            timestamp = data.mid(begin + 1, end - begin -1);
            temp.timestamp = timestamp;
            // 解析开盘价
            QString openPrice;
            begin = end + 2;
            end = begin + 1;
            while(data[end] != '\"'){
                ++end;
            }
            openPrice = data.mid(begin + 1, end - begin - 1);
            temp.open = openPrice.toDouble();
            // 解析最高价
            QString highPrice;
            begin = end + 2;
            end = begin + 1;
            while(data[end] != '\"'){
                ++end;
            }
            highPrice = data.mid(begin + 1, end - begin - 1);
            temp.high = highPrice.toDouble();
            // 解析最低价
            QString lowPrice;
            begin = end + 2;
            end = begin + 1;
            while(data[end] != '\"'){
                ++end;
            }
            lowPrice = data.mid(begin + 1, end - begin - 1);
            temp.low = lowPrice.toDouble();
            // 解析收盘价
            QString closePrice;
            begin = end + 2;
            end = begin + 1;
            while(data[end] != '\"'){
                ++end;
            }
            closePrice = data.mid(begin + 1, end - begin - 1);
            temp.close = closePrice.toDouble();
            // 交易量（张）
            QString vol;
            begin = end + 2;
            end = begin + 1;
            while(data[end] != '\"'){
                ++end;
            }

            vol = data.mid(begin + 1, end - begin - 1);
            temp.volume = vol;
            // 交易量（币）
            QString volCcy;
            begin = end + 2;
            end = begin + 1;
            while(data[end] != '\"'){
                ++end;
            }
            volCcy = data.mid(begin + 1, end - begin - 1);
            temp.volCcy = volCcy;
            // 交易量（计价货币）
            QString volCcyQuote;
            begin = end + 2;
            end = begin + 1;
            while(data[end] != '\"'){
                ++end;
            }
            volCcyQuote = data.mid(begin + 1, end - begin - 1);
            temp.volCcyQuote = volCcyQuote;
            arr.push_back(temp);
            // 解析下一个还是结束解析
            cur = end + 5;
            if(data[cur + 1] == ','){
                cur += 3;
            }
            if(data[cur + 1] == ']'){
                break;
            }
        }
        // showAllData(arr);
    }else{
        qDebug() << "error in parse function";
        return false;
    }
}

void Data::onFinished(QNetworkReply *)
{
    m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    m_reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    if (m_reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = m_reply->readAll();
        QString data = QString::fromUtf8(bytes);
        // qDebug()<< data;
        // 执行解析
        parse(data);
    }
    else
    {
        qDebug()<< m_reply->errorString();
    }

    m_reply->deleteLater();
}


