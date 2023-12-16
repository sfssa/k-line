#include "databasehandler.h"

DatabaseHandler *DatabaseHandler::GetInstance()
{
    static DatabaseHandler instance;
    return &instance;
}

DatabaseHandler::~DatabaseHandler()
{
    m_db.close();
    QSqlDatabase::removeDatabase(m_db.connectionName());
}

DatabaseHandler::DatabaseHandler()
{
    assert(init());
}

bool DatabaseHandler::init()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("kline.sqlite");

    if (!m_db.open()) {
        qDebug() << "connect sqlite3 failed";
        return false;
    }else{
        qDebug() << "connect sqlite3 successfully";
    }
}

bool DatabaseHandler::createTable(const QString &instid)
{
    QSqlQuery query;
    QString createTableQuery = QString("create table if not exists %1 ("
                                           "ts timestamp,"
                                           "o double,"
                                           "h double,"
                                           "l double,"
                                           "c double,"
                                           "vol varchar(64),"
                                           "volCcy varchar(64),"
                                           "volCCyQuote varchar(64))").arg(instid);
    // qDebug() << createTableQuery;
    if(query.exec(createTableQuery)){
        qDebug() << "table created successfully";
        return true;
    }else{
        qDebug() << "error creating table: " << query.lastError().text();
        return false;
    }
}

void DatabaseHandler::getAUDHUFHistoryData(std::vector<Point> &arr)
{
    QSqlQuery query;
    // 提前预留空间
    arr.reserve(1024);
    QString queryString = "SELECT * FROM audhuf";
    if (query.exec(queryString)) {
        while (query.next()) {
            Point temp;
            temp.xTime = query.value("time").toString();
            temp.yClose = query.value("close").toFloat();
            arr.emplace_back(temp);
        }
        qDebug() << "query successfully";
    } else {
        qDebug() << "query failed:" << query.lastError().text();
    }
}

bool DatabaseHandler::insertIntoDb(QVector<MarketData> &arr)
{
    QSqlQuery query(m_db);
    if(!m_db.transaction()){
        qDebug() << "transaction start failed";
        return false;
    }
    QString insertSql = "insert into btcusdt (ts, o, h, l, c, vol, volCcy, volCCyQuote) "
                            "values (:timestamp, :open, :high, :low, :close, :volume, :volCcy, :volCcyQuote)";

    for(const MarketData& data : arr){
        query.prepare(insertSql);
        query.bindValue(":timestamp", data.timestamp);
        query.bindValue(":open", data.open);
        query.bindValue(":high", data.high);
        query.bindValue(":low", data.low);
        query.bindValue(":close", data.close);
        query.bindValue(":volume", data.volume);
        query.bindValue(":volCcy", data.volCcy);
        query.bindValue(":volCcyQuote", data.volCcyQuote);
        if(!query.exec()){
            qDebug() << "insert failed: " << query.lastError().text();
            m_db.rollback();
            return false;
        }
    }
    if(!m_db.commit()){
        qDebug() << "transaction commit failed";
        return false;
    }
    qDebug() << "insert successful";
    return true;
}

QSqlDatabase &DatabaseHandler::getDB()
{
    return m_db;
}
