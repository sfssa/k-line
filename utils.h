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
// libcurl库请求访问的回调函数
size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);
#endif // UTILS_H
