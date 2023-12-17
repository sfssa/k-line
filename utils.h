#ifndef UTILS_H
#define UTILS_H
#include <cstdint>
#include <QString>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <vector>
#include "data.h"
#include "databasehandler.h"

// 将时间戳转换成时间
QString timestmapToReadableTime(uint64_t timestmap);
// libcurl库请求访问的回调函数
size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);
// 输出QVector内的内容
void showAllData(const QVector<MarketData>& arr);
// 将字符串类型转换成double类型
double strToDouble(QString& str);
// 获得平均值
void getAverage();
// 获得行情数据的点
void getPointsByHistorialData(QVector<Point>& point);
#endif // UTILS_H
