
#include "workflow/WFFacilities.h"
#include "service.h"
#include <signal.h>
#include <string>
#include <iostream>
#include"serviceMgr/serviceMgr.h"

using namespace srpc;
static WFFacilities::WaitGroup wait_group(1);

static void registService(const char* serviceIP, int servicePort,int check_health_port,
                        const char *serviceName, int weight);


void sig_handler(int signo) { }



int main(int argc, char *argv[])
{


    if(argc != 3){
        printf("Usage: ./main [ip] [weight]\n");
        return 1;
    }

    char *agent_ip = argv[1];
    int weight = atoi(argv[2]);


    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);

    log_file = fopen("log.txt", "w");
	//read config

    char buf[64];

    std::ifstream ifs;
    ifs.open("config.json");
    assert(ifs.is_open());

    Json::Reader reader;
	Json::Value root;
    // 解析到root，root将包含Json里所有子元素
	if (!reader.parse(ifs, root, false))
	{
		cerr << "parse failed \n";
		return -1;
	}

    string ssdp_server_ip = root["ssdp_server_ip"].asString();
    int ssdp_server_port = root["ssdp_server_port"].asInt();
    int agent_port = root["agent_port"].asInt();
    int check_health_port = root["agent_health_port"].asInt();
    int is_regist_service = root["is_regist_service"].asInt();
    string service_name = root["service_name"].asString();

    Log(NOTICE, "Agent ip: %s, port: %d", agent_ip, agent_port);
    Log(NOTICE, "SSDP Server ip: %s, port: %d", ssdp_server_ip.c_str(), ssdp_server_port);

    //create socket 
    //创建套接字
    sock = socket(AF_INET, SOCK_STREAM, 0);
    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr(ssdp_server_ip.c_str());  //具体的IP地址
    serv_addr.sin_port = htons(ssdp_server_port);  //端口

    if((connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0){
        Log(ERROR,"SSDP Servere connect error!");
    }

    if(is_regist_service)
        registService(agent_ip, agent_port, check_health_port, service_name.c_str(), weight);


    #if 1
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	SRPCServer server;

    //init_service(server);

    DSPControllerImpl service1;
	server.add_service(&service1);
    
    printf("Regist service all\n");
	server.start(agent_port);
    printf("Server start\n");
	//wait_group.wait();
    getchar();
	server.stop();
	google::protobuf::ShutdownProtobufLibrary();
    #endif
	return 0;
}


static void registService(const char* serviceIP, int servicePort, int check_health_port,
                        const char *serviceName, int weight){
    string serviceAddress = string(serviceIP)+":"+to_string(servicePort);
    string serviceProtocol = "srpc";
    string serviceVersion = "v1.0";
    string serviceProvider = "gpf";

    int checkType = TCP_CHECK;
    string interval = "10s";
    string timeout = "3s";
    string checkDeregisterCriticalServiceAfter = "2m";

    static int count = 0;
    string checkURL = string(serviceIP)+ ":" + to_string(check_health_port);
    count++;

    ServiceInfo *serviceInfo = new ServiceInfo(serviceName,"",serviceIP,servicePort,serviceProtocol,serviceVersion,serviceProvider,
    weight,checkType,checkURL,interval,checkDeregisterCriticalServiceAfter,timeout);

    printf("%s:%d %s\n", serviceIP, servicePort, serviceName);
    int regRes = registerService(serviceInfo);
    if(regRes != 0){
        printf("Register service failed, the service stop...\n");
    }else{
        printf("Regist service %s done!\n", serviceName);
    }

    delete serviceInfo;
}