#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <assert.h>
#include <QString>
#include "data.h"

class DatabaseHandler
{
public:
    static DatabaseHandler* GetInstance();
    ~DatabaseHandler();
    // 创建数据库表
    bool createTable(const QString& instid);
    // 获得audhuf历史数据
    void getAUDHUFHistoryData(std::vector<Point>& arr);
    // 将数据插入到数据库中
    bool insertIntoDb(QVector<MarketData>& arr);
    // 获得数据库连接对象
    QSqlDatabase& getDB();
private:
    // 构造函数私有化，使用单例模式
    DatabaseHandler();
    // 连接数据库
    bool init();
    // 数据库连接对象
    QSqlDatabase m_db;
};

#endif // DATABASEHANDLER_H
