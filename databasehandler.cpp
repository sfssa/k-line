#include "databasehandler.h"

DatabaseHandler *DatabaseHandler::GetInstance()
{
    static DatabaseHandler instance;
    return &instance;
}

DatabaseHandler::~DatabaseHandler()
{
    db.close();
    QSqlDatabase::removeDatabase(db.connectionName());
}

DatabaseHandler::DatabaseHandler()
{
    assert(init());
}

bool DatabaseHandler::init()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("mt4");
    db.setUserName("root");
    db.setPassword("panzhixin");
    bool ok = db.open();
    if (ok){
        qDebug() << "connection to mysql successfully";
        return true;
    }
    else {
        qDebug() << "failed to connection to mysql" << db.lastError().text();
        return false;
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
                                           "vol decimal(16,9),"
                                           "volCcy decimal(16,9),"
                                           "volCCyQuote decimal(16,9),"
                                           "confirm decimal(16,9))").arg(instid);
    qDebug() << createTableQuery;
    if(query.exec(createTableQuery)){
        qDebug() << "table created successfully";
        return true;
    }else{
        qDebug() << "error creating table: " << query.lastError().text();
        return false;
    }
}

void DatabaseHandler::getAUDHUFHistoryData(std::vector<AUDHUF> &arr)
{
    QSqlQuery query;
    // 提前预留空间
    arr.reserve(1024);
    QString queryString = "SELECT * FROM audhuf";
    if (query.exec(queryString)) {
        while (query.next()) {
            AUDHUF temp;
            temp.timestamp = query.value("time").toString();
            temp.high = query.value("high").toFloat();
            temp.open = query.value("open").toFloat();
            temp.close = query.value("close").toFloat();
            temp.low = query.value("low").toFloat();
            arr.emplace_back(temp);
        }
    } else {
        qDebug() << "Query failed:" << query.lastError().text();
    }
}
