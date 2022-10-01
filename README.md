# Squick

## Squick是什么?

Squick是一款可快速开发拓展的游戏服务器开发框架，轻量，插件化，易拓展，支持lua脚本。目前正在极速开发Unity客户端SDK中，客户端Demo: [Uquick](https://github.com/i0gan/Uquick)



**讨论QQ群：729054809**

## 特性
- 易使用，采用。
- 采用动态连链接库方式动态加载插件，开发拓展插件，让开发服务器变成开发插件。 
- 遵守谷歌C++编程规范
- 事件和属性驱动，让开发变得更简单。
- Excel实现服务端配置
- 日志捕获系统
- 支持Lua脚本开发
- 支持部分不用停服即可热更
- 默认拥有服务器插件：代理服务器、世界服务器、导航系统、数据库服务器、中心服务器、登录服务器



## 编译文件结构

```
debug
├── lib
│   ├── skcore.so
│   ├── squick_plugin_loader.so
│   └── squick_struct.so
├── plugin
│   ├── core
│   │   ├── actor.so
│   │   ├── config.so
│   │   ├── kernel.so
│   │   ├── log.so
│   │   ├── lua.so
│   │   ├── navigation.so
│   │   ├── net.so
│   │   ├── nosql.so
│   │   ├── security.so
│   │   └── test.so
│   └── extend
│       ├── db
│       │   ├── client.so
│       │   ├── logic.so
│       │   └── server.so
│       ├── game
│       │   ├── client.so
│       │   ├── logic.so
│       │   └── server.so
│       ├── login
│       │   ├── client.so
│       │   ├── http_server.so
│       │   ├── logic.so
│       │   └── server.so
│       ├── master
│       │   ├── http_server.so
│       │   ├── logic.so
│       │   └── server.so
│       ├── others
│       │   ├── chat.so
│       │   ├── consume_manager.so
│       │   └── inventory.so
│       ├── proxy
│       │   ├── client.so
│       │   ├── logic.so
│       │   └── server.so
│       └── world
│           ├── client.so
│           └── server.so
└── squick

```


## 快速开始

```bash
git clone https://github.com/pwnsky/squick.git

cd squick
bash install.sh
```


如果不能编译，可能是缺少依赖，打开third_party/install.sh 里查看需要安装的依赖。

编译

```bash
./build.sh

```
编译成功后，可执行文件在 ./build/server/squick


### 搭建Redis
这里采用docker来进行搭建
```
docker pull redis
docker run --name squick-cache -p 22222:6379  -d redis --requirepass pwnsky # pwnsky 是密码
```

测试

```bash
cd ./build
./debug.sh
```

### 客户端SDK

进入 https://github.com/i0gan/Uquick 查看详情安装

## 第三方依赖库
- minzip
- zlib
- easylogging++
- libevent
- hiredis
- protobuf
- RapidXML
- ajson
- concurrentqueue
- LuaIntf
- lua
- navigation
- nlohmann

