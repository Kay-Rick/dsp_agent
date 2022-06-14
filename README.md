# dsp_agent



### 文件说明

- 若srpc接口有变化，需要重新build，对应文件`build.sh`
- `config.json`：程序运行时读取的配置信息

- `ssdp_server.py`：运行在容器外，模拟核心框架做测试，本质是TCP Server
- `start_all.sh`：运行在容器外，用于启动项目中所有的容器
- `start_dsp_agent.sh`：容器内清理环境，重新启动

