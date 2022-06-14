#include "proto/protogen/legacy.srpc.h"
#include <unistd.h>
#include"serviceMgr/serviceMgr.h"

#define INSHEADER "SSDP -s ground -t framework "
//#define ZERO_PREFIX "0000"

extern int sock; //client sock

enum APP_TYPE{
        SAR,
        ELEC_RECO,
        COM,
        NAV,
        JAM,
};


class DSPControllerImpl: public DSPController::Service{

    //elec
    void LoadElecReco(DSPControllerRequest *request,DSPControllerResponse *response,
					srpc::RPCContext *ctx) override
    {
        const char *load_msg = "-f loadapp -a elec_reco";
        

        sendIns(load_msg, ELEC_RECO, true);
    }

    virtual void StartElecReco(DSPControllerRequest *request,DSPControllerResponse *response,
					srpc::RPCContext *ctx)
    {
        const char *start_msg = "-f start -a elec_reco";
        sendIns(start_msg, ELEC_RECO);
    }

	virtual void StopElecReco(DSPControllerRequest *request,DSPControllerResponse *response,
					srpc::RPCContext *ctx)
    {
        const char *stop_msg = "-f stop -a elec_reco";
        sendIns(stop_msg, ELEC_RECO);
        elec_time = 0.0;
    }

    virtual void SwitchElecReco(DSPControllerRequest *request,DSPControllerResponse *response,
					srpc::RPCContext *ctx)
    {
        const char *stop_msg = "-f switch -a elec_reco";
        sendIns(stop_msg, ELEC_RECO);
    }

    //sar
    void LoadSarApp(DSPControllerRequest *request,DSPControllerResponse *response,
					srpc::RPCContext *ctx) override
    {
        const char *load_msg = "-f loadapp -a sar";
        sendIns(load_msg, SAR, true);
    }

    void StartSarApp(DSPControllerRequest *request,DSPControllerResponse *response,
					srpc::RPCContext *ctx) override
    {
        const char *start_msg = "-f start -a sar";
        sendIns(start_msg, SAR);
    }

	virtual void StopSarApp(DSPControllerRequest *request,DSPControllerResponse *response,
					srpc::RPCContext *ctx)
    {
        const char *stop_msg = "-f stop -a sar";
        sendIns(stop_msg, SAR);
        sar_time = 0.0;

    }

    virtual void SwitchSarApp(DSPControllerRequest *request,DSPControllerResponse *response,
					srpc::RPCContext *ctx)
    {
        const char *switch_msg = "-f switch -a sar";
        sendIns(switch_msg, SAR);

    }

    //comm
    void LoadCommunication(DSPControllerRequest *request, DSPControllerResponse *response,
					srpc::RPCContext *ctx) override
    {
        const char *load_msg = "-f loadapp -a dvb-s2";

        sendIns(load_msg, COM, true);
        
    }

    virtual void StartCommunication(DSPControllerRequest *request, DSPControllerResponse *response,
					srpc::RPCContext *ctx)
    {
        const char *start_msg = "-f start -a dvb-s2";
        sendIns(start_msg, COM);
    }

	virtual void StopCommunication(DSPControllerRequest *request, DSPControllerResponse *response,
					srpc::RPCContext *ctx)
    {
        const char *stop_msg = "-f stop -a dvb-s2";
        sendIns(stop_msg, COM);
        comm_time = 0.0;
    }

    virtual void SwitchCommunication(DSPControllerRequest *request, DSPControllerResponse *response,
					srpc::RPCContext *ctx)
    {
        const char *switch_msg = "-f switch -a dvb-s2";
        sendIns(switch_msg, COM);
    }

    virtual void ConfigCommunication(ConfigRequest *request, DSPControllerResponse *response,
					srpc::RPCContext *ctx)
    {
        string objid = request->objid();

        //-c compname -n paraname -v value
        string config_msg = "-f config -a dvb-s2 -c ";
        config_msg += objid;
        config_msg += " -n gunjiang -v 0x0";

        sendIns(config_msg.c_str(), COM);
    }

    //nav
    void LoadNavigation(DSPControllerRequest *request, DSPControllerResponse *response,
					srpc::RPCContext *ctx) override
    {
        const char *load_msg = "-f loadapp -a kp";

        sendIns(load_msg, NAV, true);
        
    }
    virtual void StartNavigation(DSPControllerRequest *request, DSPControllerResponse *response,
					srpc::RPCContext *ctx)
    {
        const char *start_msg = "-f start -a kp";
        sendIns(start_msg, NAV);
    }

	virtual void StopNavigation(DSPControllerRequest *request, DSPControllerResponse *response,
					srpc::RPCContext *ctx)
    {
        const char *stop_msg = "-f stop -a kp";
        sendIns(stop_msg, NAV);
        nav_time = 0.0;
    }

    virtual void SwitchNavigation(DSPControllerRequest *request, DSPControllerResponse *response,
					srpc::RPCContext *ctx)
    {
        const char *switch_msg = "-f switch -a kp";
        sendIns(switch_msg, NAV);
    }

    virtual void ConfigNavigation(ConfigRequest *request, DSPControllerResponse *response,
					srpc::RPCContext *ctx)
    {
        string objid = request->objid();

        //-c compname -n paraname -v value
        string config_msg = "-f config -a kp -c ";
        config_msg += objid;
        config_msg += " -n gunjiang -v 0x0";

        sendIns(config_msg.c_str(), NAV);
    }


    //jam
    void LoadElectricJam(DSPControllerRequest *request, DSPControllerResponse *response,
					srpc::RPCContext *ctx) override
    {
        const char *load_msg = "-f loadapp -a jam";

        sendIns(load_msg, JAM, true);
        
    }
    virtual void StartElectricJam(DSPControllerRequest *request, DSPControllerResponse *response,
					srpc::RPCContext *ctx)
    {
        const char *start_msg = "-f start -a jam";
        sendIns(start_msg, JAM);
    }

	virtual void StopElectricJam(DSPControllerRequest *request, DSPControllerResponse *response,
					srpc::RPCContext *ctx)
    {
        const char *stop_msg = "-f stop -a jam";
        sendIns(stop_msg, JAM);
        nav_time = 0.0;
    }

    virtual void SwitchElectricJam(DSPControllerRequest *request, DSPControllerResponse *response,
					srpc::RPCContext *ctx)
    {
        const char *switch_msg = "-f switch -a jam";
        sendIns(switch_msg, JAM);
    }

    virtual void ConfigElectricJam(ConfigRequest *request, DSPControllerResponse *response,
					srpc::RPCContext *ctx)
    {
        string objid = request->objid();

        //-c compname -n paraname -v value
        string config_msg = "-f config -a jam -c ";
        config_msg += objid;
        config_msg += " -n gunjiang -v 0x0";

        sendIns(config_msg.c_str(), JAM);
    }


    //get time

    virtual void GetNavReconstructTime(DSPControllerRequest *request, ReconstructTimeResponse *response,
					srpc::RPCContext *ctx)
    {
        response->set_time(nav_time);
    }

    virtual void GetSarReconstructTime(DSPControllerRequest *request, ReconstructTimeResponse *response,
					srpc::RPCContext *ctx)
    {
        response->set_time(sar_time);
    }

    virtual void GetElecReconstructTime(DSPControllerRequest *request, ReconstructTimeResponse *response,
					srpc::RPCContext *ctx)
    {
        response->set_time(elec_time);
    }

    virtual void GetComReconstructTime(DSPControllerRequest *request, ReconstructTimeResponse *response,
					srpc::RPCContext *ctx)
    {
        response->set_time(comm_time);
    }

    virtual void GetJamReconstructTime(DSPControllerRequest *request, ReconstructTimeResponse *response,
					srpc::RPCContext *ctx)
    {
        response->set_time(jam_time);
    }


    void sendIns(const char *str, APP_TYPE app_type, bool is_load = false);

    public:

    DSPControllerImpl(){
        memset(buf, 0, sizeof(buf));
    }

    char buf[256];
    static float sar_time;
    static float elec_time;
    static float comm_time;
    static float nav_time;
    static float jam_time;
};
