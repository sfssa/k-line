#include "data.h"
#include "utils.h"

Data::Data()
{
    m_NetManger = new QNetworkAccessManager;
    QUrl url(BTC_USDT_HISTORY_DATA_API);

    m_Reply = m_NetManger->get(QNetworkRequest(url));

    QObject::connect(m_NetManger, SIGNAL(finished(QNetworkReply*)),
                         this, SLOT(finishedSlot(QNetworkReply*)));
}

Data::~Data()
{

}

void Data::requestHistoricalData()
{
    QNetworkAccessManager* pManager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    QByteArray data;
    // 发送https请求前准备工作;
    QSslConfiguration config;
    QSslConfiguration conf = request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(conf);
    request.setUrl(QUrl(BTC_USDT_HISTORY_DATA_API));       // "https://www.temp.com"
    QNetworkReply *pReply = pManager->post(request, data);

    connect(pReply , SIGNAL(finished()) , this , SLOT(onFinished()));
    connect(pReply , SIGNAL(error(QNetworkReply::NetworkError)) , this , SLOT(onError(QNetworkReply::NetworkError)));
}

bool Data::parse(std::vector<MarketData> &arr)
{

}

void Data::finishedSlot(QNetworkReply *)
{
    m_Reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    m_Reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    if (m_Reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = m_Reply->readAll();
        QString string = QString::fromUtf8(bytes);
        qDebug()<<string;
    }
    else
    {
        qDebug()<< m_Reply->errorString();
    }

    m_Reply->deleteLater();
}

void Data::onFinished()
{
    QNetworkReply *pReplay = qobject_cast<QNetworkReply*>(sender());
    // 保存接受的数据;
    QByteArray replyContent = pReplay->readAll();
    qDebug() << "get data successfully";
}

void Data::onError(QNetworkReply::NetworkError errorCode)
{
    QNetworkReply *pReplay = qobject_cast<QNetworkReply*>(sender());
    // 输出错误码及错误信息;
    qDebug()<< errorCode;
    qDebug()<< pReplay->errorString();
}

