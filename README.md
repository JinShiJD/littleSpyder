# littleSpyder-网络爬虫与数据采集工具  

**平台工具**：Qt Creator + qmake 构建（.pro 多文件工程）、C++11、QtNetwork、Windows/Linux 控制台程序

**项目内容**：
1. 基于 Qt 事件循环与信号槽机制，使用 QNetworkAccessManager 实现异步非阻塞 HTTP 抓取，通过 finished/error 信号配合 Lambda 回调处理结果与异常，实现网络 IO 与主流程解耦，避免阻塞
2. 采用网络访问层（HttpAccess）、正则解析层（RETool）、CSV 持久化层（CSVTool）三层解耦架构，各模块单一职责、独立可替换，便于横向扩展多站点与多存储后端
3. 封装正则解析引擎，基于 QRegularExpression 全局匹配 + 跨行惰性量词 + 捕获组批量提取网页中的标题与链接，pattern 可配置以适配不同站点页面结构
4. 基于 QFile/QTextStream 实现 CSV 数据落盘与回读，显式指定 UTF-8 编解码链路解决中文乱码；写入后立即回读比对，实现落盘数据一致性自校验
5. 遵循 RAII 与 C++ 对象语义，显式禁用 HttpAccess 的拷贝/移动构造与赋值运算符（= delete）、定义虚析构函数，并以 RVO 优化容器返回，减少无谓拷贝与浅拷贝隐患
6. 使用 try-catch 捕获 std::runtime_error 实现异常安全，异常路径下主动关闭文件句柄并返回错误码，避免半写状态与资源泄漏
7. 使用 qmake 编写 .pro 工程文件管理多文件编译与跨平台部署规则，通过 qDebug 分级日志完成问题追踪与调试  

**其它 待升级处**：  
　　引入 QThreadPool 实现并发抓取与限速队列，增加 UA 伪装 / 代理池 / 重试退避等反爬策略，存储升级为 SQLite/MySQL 实现增量抓取与去重，引入 HTML 解析库替代正则提升鲁棒性，补充 Qt Test 单元测试与自动化构建脚本
