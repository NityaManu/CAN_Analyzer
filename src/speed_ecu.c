#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/neutrino.h>
#include "can_frame.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int coid;
    int timer_chid;
    int can_pid;
    int can_chid;
    int reply;
    int rcvid;
    int ret;
    int status;
    int set;
    struct sigevent event;
    timer_t timerid;
    struct itimerspec timer_spec;
    struct _pulse pulse;

    CAN_Frame frame;

    if(argc != 3)
    {
        printf("Usage: speed_ecu <PID> <CHID>\n");
        return -1;
    }

    can_pid = atoi(argv[1]);
    can_chid = atoi(argv[2]);

    timer_chid = ChannelCreate(0);
    if(timer_chid==-1){
    	perror("ChannelCreate");
    	return -1;
    }

    coid = ConnectAttach(0,can_pid,can_chid,_NTO_SIDE_CHANNEL,0);
    if(coid == -1)
    {
        perror("ConnectAttach");
        return -1;
    }

    SIGEV_PULSE_INIT(&event,ConnectAttach(ND_LOCAL_NODE,0,timer_chid,_NTO_SIDE_CHANNEL,0),SIGEV_PULSE_PRIO_INHERIT,1,0);
    status = timer_create(CLOCK_REALTIME,&event,&timerid);
    if(status == -1){
    	perror("TimerCreate");
    	return -1;
    }

    timer_spec.it_value.tv_sec = 0;
    timer_spec.it_value.tv_nsec = 500000000;

    timer_spec.it_interval.tv_sec = 0;
    timer_spec.it_interval.tv_nsec = 500000000;

    set = timer_settime(timerid,0,&timer_spec,NULL);
    if(set == -1){
       	perror("TimerSet");
       	return -1;
    }

    while(1)
    {
    	rcvid = MsgReceive(timer_chid,&pulse,sizeof(pulse),NULL);
    	if(rcvid==-1){
    		perror("MsgReceive");
    		return -1;
    	}

        uint16_t speed;

        if(pulse.code == 1){
        	speed = 20 + rand()%120;
        	create_speed_frame(&frame,speed);

        	ret = MsgSend(coid,&frame,sizeof(frame),&reply,sizeof(reply));
        	if(ret == -1)
        	{
        		perror("MsgSend");
        		return -1;
            }
        }
    }
    return 0;
}
