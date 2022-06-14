/*
* 测试server.cc的程序
*/
#include "proto/protogen/legacy.srpc.h"
#include "workflow/WFFacilities.h"
#include <unistd.h>
#include <iostream>
#include"serviceMgr/serviceMgr.h"

using namespace srpc;
using namespace std;

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo)
{
	wait_group.done();
}




int main(int argc, char *argv[])
{
	
	GOOGLE_PROTOBUF_VERIFY_VERSION;

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

    string agent_ip = root["agent_ip"].asString();
    int agent_port = root["agent_port"].asInt();
	

	//FpgaServiceSilly::SRPCClient client(ip, port);

	//CommunicationController::SRPCClient client(ip, port);

	// example for RPC method call
	//DSPControllerRequest req;
	//client.StartCommunicationReceiver(&req, do_nothing);

	struct WFGlobalSettings settings = GLOBAL_SETTINGS_DEFAULT;
	settings.endpoint_params.connect_timeout = 2 * 1000;
	settings.endpoint_params.response_timeout = 300 *1000;
	WORKFLOW_library_init(&settings);

	DSPControllerRequest req;
	ConfigRequest con_req;
	DSPControllerResponse resp;
	ReconstructTimeResponse time_resp;
	
	DSPController::SRPCClient client(agent_ip.c_str(), agent_port);


	string start_sar_cmd = "start sar";
	string load_sar_cmd = "load sar";
	string stop_sar_cmd = "stop sar";
	string get_sar_cmd = "get sar";

	string start_elec_cmd = "start elec";
	string load_elec_cmd = "load elec";
	string stop_elec_cmd = "stop elec";
	string get_elec_cmd = "get elec";

	string start_comm_cmd = "start comm";
	string load_comm_cmd = "load comm";
	string config_comm_cmd = "config comm";
	string get_comm_cmd = "get comm";

	string start_nav_cmd = "start nav";
	string load_nav_cmd = "load nav";
	string stop_nav_cmd = "stop nav";
	string config_nav_cmd = "config nav";
	string get_nav_cmd = "get nav";

	string start_jam_cmd = "start jam";
	string load_jam_cmd = "load jam";
	string stop_jam_cmd = "stop jam";
	string config_jam_cmd = "config jam";
	string get_jam_cmd = "get jam";


	string quit = "q";

	printf("All commands are: \n");
	printf("%s\n", start_sar_cmd.c_str());
	printf("%s\n", stop_sar_cmd.c_str());
	printf("%s\n", load_sar_cmd.c_str());
	printf("%s\n", get_sar_cmd.c_str());
	printf("%s\n", get_elec_cmd.c_str());
	printf("%s\n", get_comm_cmd.c_str());
	printf("%s\n", start_elec_cmd.c_str());
	printf("%s\n", stop_elec_cmd.c_str());
	printf("%s\n", load_elec_cmd.c_str());
	printf("%s\n", load_comm_cmd.c_str());
	printf("%s [value]\n", config_comm_cmd.c_str());

	printf("%s\n", load_nav_cmd.c_str());
	printf("%s\n", start_nav_cmd.c_str());
	printf("%s\n", stop_nav_cmd.c_str());
	printf("%s\n", get_nav_cmd.c_str());
	printf("%s [value]\n", config_nav_cmd.c_str());

	printf("%s\n", load_jam_cmd.c_str());
	printf("%s\n", start_jam_cmd.c_str());
	printf("%s\n", stop_jam_cmd.c_str());
	printf("%s\n", get_jam_cmd.c_str());
	printf("%s [value]\n", config_jam_cmd.c_str());
	
	printf("-----------------------------\n");
	printf("Please input your command:\n");

	RPCSyncContext target_Location_syntax;
	char str[16];
	for(;;){
		cin.getline(str, 16);
		//printf("str is %s\n", str);

		string s(str);

		if(s == load_sar_cmd)
		{
			client.LoadSarApp(&req, &resp, &target_Location_syntax);
			client.GetSarReconstructTime(&req, &time_resp, &target_Location_syntax);
			printf("Sar Reconstruct time is %.3fs\n", time_resp.time());
		}
		else if(s == start_sar_cmd)
			client.StartSarApp(&req, &resp, &target_Location_syntax);
		else if(s == stop_sar_cmd)
			client.StopSarApp(&req, &resp, &target_Location_syntax);
		else if(s == load_elec_cmd){
			client.LoadElecReco(&req, &resp, &target_Location_syntax);
			client.GetElecReconstructTime(&req, &time_resp, &target_Location_syntax);
			printf("Elec Reconstruct time is %.3fs\n", time_resp.time());
		}else if(s == get_sar_cmd){
			client.GetSarReconstructTime(&req, &time_resp, &target_Location_syntax);
			printf("[Independent]:Sar Reconstruct time is %.3fs\n", time_resp.time());
		}else if(s == get_elec_cmd){
			client.GetElecReconstructTime(&req, &time_resp, &target_Location_syntax);
			printf("[Independent]:Elec Reconstruct time is %.3fs\n", time_resp.time());
		}else if(s == get_comm_cmd){
			client.GetComReconstructTime(&req, &time_resp, &target_Location_syntax);
			printf("[Independent]:Com Reconstruct time is %.3fs\n", time_resp.time());
		}
		else if(s == start_elec_cmd)
			client.StartElecReco(&req, &resp, &target_Location_syntax);
		else if(s == stop_elec_cmd)
			client.StopElecReco(&req, &resp, &target_Location_syntax);
		else if(s == load_comm_cmd){
			client.LoadCommunication(&req, &resp, &target_Location_syntax);
			client.GetComReconstructTime(&req, &time_resp, &target_Location_syntax);
			printf("Com Reconstruct time is %.3fs\n", time_resp.time());
		}
		else if(s == start_comm_cmd){
			client.StartCommunication(&req, &resp, &target_Location_syntax);
		}
		else if(strncmp(s.c_str(), "config comm", 11) == 0){
			string objid = s.c_str() + 12;
			con_req.set_objid(objid);
			client.ConfigCommunication(&con_req, &resp, &target_Location_syntax);
		//nav
		}else if(s == load_nav_cmd){
			client.LoadNavigation(&req, &resp, &target_Location_syntax);
		}else if(s == start_nav_cmd){
			client.StartNavigation(&req, &resp, &target_Location_syntax);
		}else if(s == stop_nav_cmd){
			client.StopNavigation(&req, &resp, &target_Location_syntax);
		}else if(strncmp(s.c_str(), "config nav", 10) == 0){
			string objid = s.c_str() + 11;
			con_req.set_objid(objid);
			client.ConfigNavigation(&con_req, &resp, &target_Location_syntax);
		//jam
		}else if(s == load_jam_cmd){
			client.LoadElectricJam(&req, &resp, &target_Location_syntax);
		}else if(s == start_jam_cmd){
			client.StartElectricJam(&req, &resp, &target_Location_syntax);
		}else if(s == stop_jam_cmd){
			client.StopElectricJam(&req, &resp, &target_Location_syntax);
		}else if(strncmp(s.c_str(), "config jam", 10) == 0){
			string objid = s.c_str() + 11;
			con_req.set_objid(objid);
			client.ConfigElectricJam(&con_req, &resp, &target_Location_syntax);
		}
		else if(s == quit)
			break;
		else
			printf("Unknown command\n");
	}

	return 0;
}
