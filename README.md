# 项目名称：k-line
## 描述

用C++语言实现K线的折线图显示。

## 环境

操作系统：	  	Windows10 64位

QT：					5.12.2

QT Creator： 	 4.8.2

MySQL：			 8.0.22

## 准备条件

将MySQL安装目录`C:\Program Files\MySQL\MySQL Server 8.0\lib`中的`libmysql.dll`和`libmysql.lib`赋值到QT项目使用的编译器的`lib`文件夹`D:\Qt\5.12.2\mingw73_64\lib`中。

# 01版本

## 设计思路

1. 获取某个永续合约(BTC_USDT)100条行情数据保存到数据库中（1min）；
2. 从MySQL数据库中将数据加载到内存中；
3. 提取开盘价、最高价、最低价、收盘价，随着鼠标聚焦到不同的点将该点对应的数据显示出来

## 类

### 数据类-Data

#### 描述

负责数据的获取和处理。

#### 函数说明

- 访问欧易的API获取历史行情数据：`void requestHistoricalData(const std::string& instid, size_t count);`
- 处理API返回值：`void handleResponse();`

### 数据库处理-DatabaseHandler

#### 描述

负责数据库相关的处理。

#### 函数说明

- 测试MySQL是否连接成功：`bool testConnection();`
- 建立`instid`品种的数据库表：`bool createTable(const std::string& instid);`
- 将获得的历史行情数据插入到数据库中：`bool insertHistoricalMarketData`
- 将数据库中的行情数据加载到内存中：`bool loadHistoricalData(const std::string& instid);`

### 渲染类-KLineDrawer

#### 描述

负责根据历史行情数据来渲染K线折线。

#### 函数说明

- 根据历史行情数据渲染成K线：`void drawKLine();`

### 工具类-Utils

- 将时间戳转换成具体的时间：`std::string timestmapToReadableTime(uint64_t timestmap);`


## 详细设计

### 数据流图

![image-20231214134623339](https://github.com/sfssa/k-line/tree/master/staticdata01.png)

### 获取数据

通过QT提供的`QNetworkAccessManager`来访问API从而申请历史行情数据，通过槽函数绑定`handleResponse`函数，拿到数据后通过`json`实现对数据的解析，之后调用数据库的插入数据函数完成数据的获取。其中数据库的插入操作通过事务来完成。

### 加载数据

将数据库中的行情数据加载到内存中。

### 渲染K线

横坐标是时间周期，纵坐标是交易品种的以`计价货币`为单位的总交易量与以`币`为单位的交易量的比值，通过`drawLine`画出K线。

通过观察欧易提供的K线图，欧易中以格线图的形式画出K线，其中纵坐标的每个格子的范围随着鼠标放大图像而变化：1000-500-400-250-200-100-40-25-20-10-5，最小粒度为5，最大粒度为1000；

横坐标范围是时间周期，纵坐标范围需要包含平均值的最小值和最大值的差值，因此在上下区间+最大粒度，随着

鼠标滑动放大或缩小当方格的范围发生变化时需要显示或删除纵坐标的值。
