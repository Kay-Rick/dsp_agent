#include "service.h"

int sock;

float DSPControllerImpl::comm_time=0;
float DSPControllerImpl::sar_time=0;
float DSPControllerImpl::elec_time=0;
float DSPControllerImpl::nav_time=0;
float DSPControllerImpl::jam_time=0;


 void DSPControllerImpl::sendIns(const char *str, APP_TYPE app_type, bool is_load){
    char zero_prefix[4];
    memset(zero_prefix, 0, sizeof(zero_prefix));
    send(sock, zero_prefix, sizeof(zero_prefix), 0);
    Log(NOTICE, "send ?? '%s' done", "0000");
    //memset(buf,0,sizeof(buf));
    strcpy(buf, INSHEADER);
    strcat(buf, str);
    send(sock, buf, strlen(buf), 0);

    char recv_buf[256] = {0};


    //first recv length，the first two bytes
    recv(sock, recv_buf, 2, 0);
    int len = (recv_buf[0] << 8) | recv_buf[1];
    Log(NOTICE, "recv buf length is %d", len);

    int n=0, count = 0;
    char *cur = recv_buf;

    //now read buffer of length of n
    while(count < len){
        n = recv(sock, cur, sizeof(recv_buf), 0);
        count += n;
        cur   += n;
    }

    Log(NOTICE, "Receive buf is '%s'", recv_buf);
    //Only load will set response param
    if(is_load){
        /// ...@1234 means the reconstruc time is 1234ms, which is 1.234s
        char *pos = strchr(recv_buf, '@');
        float time = 0.0;
        if(pos != NULL){//just for safety
            pos++;
            time = static_cast<float>(atoi(pos)) / 1000;
        }

        //change ms to s
        Log(NOTICE, "Reconstruct time is %.3f", time);
        
        switch(app_type){
        case SAR: sar_time = time; break;
        case ELEC_RECO: elec_time = time; break;
        case COM: comm_time = time; break;
        case NAV: nav_time = time; break;
        case JAM: jam_time = time; break;
        default: break;    
        }
    }



    Log(NOTICE, "send '%s' done!", str);
}
