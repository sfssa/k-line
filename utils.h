#ifndef UTILS_H
#define UTILS_H
#include <cstdint>
#include <QString>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <vector>
#include "data.h"

// 将时间戳转换成时间
std::string timestmapToReadableTime(uint64_t timestmap);
// 解析获得的历史数据
void parse(std::vector<MarketData>& arr);
#endif // UTILS_H
