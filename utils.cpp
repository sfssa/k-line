#include "utils.h"


std::string timestmapToReadableTime(uint64_t timestmap)
{
    auto timePoint = std::chrono::system_clock::time_point(std::chrono::seconds(timestmap));
    auto tm = std::chrono::system_clock::to_time_t((timePoint));
    std::tm* timeInfo = std::localtime(&tm);
    std::stringstream ss;
    ss << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void parse(std::vector<MarketData>& arr, QString& data)
{

}

size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    QByteArray *buffer = static_cast<QByteArray *>(userp);
    size_t totalSize = size * nmemb;
    buffer->append(static_cast<char *>(contents), totalSize);
    return totalSize;
}

void showAllData(const QVector<MarketData> &arr)
{
    qDebug() << "begin";
    for(const auto& i : arr){
        qDebug() << i.timestamp;
        qDebug() << i.open;
        qDebug() << i.high;
        qDebug() << i.low;
        qDebug() << i.close;
        qDebug() << i.volume;
        qDebug() << i.volCcy;
        qDebug() << i.volCcyQuote;
    }
    qDebug() << "end";
}

double strToDouble(QString &str)
{
    bool flag;
    double value = str.toDouble(&flag);
    if(flag){
        QString formattedValue = QString::number(value, 'g', 15);
        return value;
    }
    return -1;
}
