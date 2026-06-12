#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <errno.h>
#include "can_frame.h"

int main(){
	int chid;
	int rcvid;
	int status=0;
	int engine_count=0;
	int speed_count=0;
	int brake_count=0;
	int total_frames=0;

	chid=ChannelCreate(0);
	if (chid==-1){
				perror("ChannelCreate");
				return -1;
			}

	printf("PID=%d CHID=%d\n",getpid(),chid);

	CAN_Frame frame;

	while(1){
		rcvid=MsgReceive(chid,&frame,sizeof(frame),NULL);
		if(rcvid==-1){
			perror("MsgReceive");
			continue;
		}

		if(frame.dlc > 8){
			print_timestamp(frame.timestamp);
			printf("WARNING: Invalid DLC = %u\n",frame.dlc);
		}

		switch(frame.id){

		case ENGINE_ID:
		{
			uint16_t rpm = extract_rpm(&frame);
			engine_count++;
			print_timestamp(frame.timestamp);
			if(rpm > 8000){
				printf("WARNING: Invalid RPM = %u\n",rpm);
			}
			else{
				printf("RPM = %u\n",rpm);
			}
			break;
		}

		case SPEED_ID:
		{
			uint16_t speed = extract_speed(&frame);
			speed_count++;
			print_timestamp(frame.timestamp);
			if(speed > 250){
				printf("WARNING: Invalid Speed = %u\n",speed);
			}
			else{
				printf("Speed = %u km/h\n",speed);
			}
			break;
		}

		case BRAKE_ID:
			brake_count++;
			print_timestamp(frame.timestamp);
			printf("Brake = %s\n",extract_brake(&frame)?"ON":"OFF");
			break;

		default:
			print_timestamp(frame.timestamp);
			printf("Unknown CAN ID: 0x%X\n",frame.id);
			break;

		}
		total_frames++;
		if(total_frames %50==0){
			printf("\n-----CAN STATISTICS-----\n");
			printf("Engine Frames : %d\n",engine_count);
			printf("Speed Frames : %d\n",speed_count);
			printf("Brake Frames : %d\n",brake_count);
			printf("------------------------\n\n");
		}

		MsgReply(rcvid,EOK,&status,sizeof(status));
	}
}
