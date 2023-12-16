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
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("kline.sqlite");

    if (!db.open()) {
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
                                           "volCCyQuote varchar(64),"
                                           "confirm int)").arg(instid);
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
