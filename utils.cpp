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

void parse(std::vector<MarketData>& arr)
{

}
