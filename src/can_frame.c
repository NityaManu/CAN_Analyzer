#include "can_frame.h"

void print_timestamp(uint32_t timestamp){
	time_t t = timestamp;
	struct tm *time_info=localtime(&t);
	printf("[%02d:%02d:%02d] ",time_info->tm_hour,time_info->tm_min,time_info->tm_sec);
}

uint16_t extract_rpm(const CAN_Frame *frame){
	return frame->data[0]|
			(frame->data[1]<<8);
}

uint16_t extract_speed(const CAN_Frame *frame){
	return frame->data[0]|
			(frame->data[1]<<8);
}

uint8_t extract_brake(const CAN_Frame *frame){
	return frame->data[0];
}

void create_engine_frame(CAN_Frame *frame, uint16_t rpm)
{
    frame->id = ENGINE_ID;
    frame->timestamp = (uint32_t)time(NULL);
    frame->dlc = 2;
    frame->data[0] = rpm & 0xFF;
    frame->data[1] = (rpm >> 8) & 0xFF;
}


void create_speed_frame(CAN_Frame *frame, uint16_t speed)
{
    frame->id = SPEED_ID;
    frame->timestamp = (uint32_t)time(NULL);
    frame->dlc = 2;
    frame->data[0] = speed & 0xFF;
    frame->data[1] = (speed >> 8) & 0xFF;
}


void create_brake_frame(CAN_Frame *frame, uint8_t brake_status)
{
    frame->id = BRAKE_ID;
    frame->timestamp = (uint32_t)time(NULL);
    frame->dlc = 1;
    frame->data[0] = brake_status;
}


void print_frame(const CAN_Frame *frame)
{
    printf("\n");
    printf("ID        : 0x%X\n", frame->id);
    printf("Time stamp : %u\n", frame->timestamp);
    printf("DLC       : %u\n", frame->dlc);
    printf("Data      : ");

    for(int i = 0; i < frame->dlc; i++)
    {
        printf("%02X ", frame->data[i]);
    }

    printf("\n");
}
