# Quoridor
墙棋又译为步步为营，是Mirko Marchesi在1997年推出的两到四人对战的桌面棋类游戏。
本人将其实现为手游，包含单机模式和在线对战模式。
采用C/S架构，客户端使用Cocos2d-X游戏引擎进行开发，使用Alpha-Beta剪枝搜索实现AI，服务端基于Linux使用Asio网络库进行开发，采用异步Proactor模式。使用JSON作为数据交换格式，使用自动注册工厂提高了代码的质量。
目前单机模式已经完成，在线对战模式仍在开发中。

# 项目展示
![Image text](https://raw.githubusercontent.com/shiyi1996/Quoridor/master/image/%E6%9C%AA%E5%91%BD%E5%90%8D_meitu_0.png)
![Image text](https://raw.githubusercontent.com/shiyi1996/Quoridor/master/image/%E6%9C%AA%E5%91%BD%E5%90%8D_meitu_2.png)
