# Quoridor简介
墙棋又译为步步为营，是Mirko Marchesi在1997年推出的两到四人对战的桌面棋类游戏。
本人将其实现为手游，包含单机模式和在线对战模式。
采用C/S架构，客户端使用Cocos2d-X游戏引擎进行开发，使用Alpha-Beta剪枝搜索实现AI，服务端基于Linux使用Asio网络库进行开发，采用异步Proactor模式。使用JSON作为数据交换格式，使用自动注册工厂提高了代码的质量。
目前单机模式已经完成，在线对战模式仍在开发中。

# 项目展示
![Image text](https://raw.githubusercontent.com/shiyi1996/Quoridor/master/image/%E6%9C%AA%E5%91%BD%E5%90%8D_meitu_0.png)
![Image text](https://raw.githubusercontent.com/shiyi1996/Quoridor/master/image/%E6%9C%AA%E5%91%BD%E5%90%8D_meitu_2.png)

# 客户端设计
- GlobalDefine        ：游戏数据存储模块
- SplashLayer         ：资源加载界面
- SettingLayer        ：设置界面
- ChoosePlayLayer     ：游戏模式选择界面
- GameLayer           ：游戏主界面基类
- GameWithCmpLayer    ：单机模式主界面
- GameWithPlayerLayer ：在线模式主界面
- AI                  ：机器走法计算模块
- ResultLayer         ：注册界面
- LoginLayer          ：登陆界面
# 服务端设计
## 网络部分
- server          ：完成端口绑定监听、连接控制器的建立、调度池的启动与结束、统一事件源
- io_service_pool ：构建调度器集合，并构建对应线程池，封装对调度器集合的操作，保证调度器的运行
- connection      ：对连接进行封装，含异步读写操作，读写缓冲区，以及写缓冲队列
- message         ：缓冲区的封装，将消息分为包头和包体，解决粘包情况
- sync_queue      ：同步队列，使用信号量和互斥锁，解决socket多对一写操作的冲突问题
## 业务逻辑部分
- factory         ：自动注册工厂类，消除业务逻辑中繁杂的Switch语句，提高代码质量
- action          ：业务逻辑基类
- login_action    ：登陆逻辑
- register_action ：注册逻辑
- XXX_action      ：其他业务逻辑(还在开发中)
