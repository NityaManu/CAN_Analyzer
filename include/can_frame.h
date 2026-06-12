#ifndef CAN_FRAME_H
#define CAN_FRAME_H

#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define ENGINE_ID 0x100
#define SPEED_ID  0x200
#define BRAKE_ID  0x300

typedef struct
{
    uint32_t id;
    uint32_t timestamp;

    uint8_t dlc;

    uint8_t data[8];

} CAN_Frame;

void print_timestamp(uint32_t timestamp);

uint16_t extract_rpm(const CAN_Frame *frame);

uint16_t extract_speed(const CAN_Frame *frame);

uint8_t extract_brake(const CAN_Frame *frame);

void create_engine_frame(CAN_Frame *frame, uint16_t rpm);

void create_speed_frame(CAN_Frame *frame, uint16_t speed);

void create_brake_frame(CAN_Frame *frame, uint8_t brake_status);

void print_frame(const CAN_Frame *frame);

#endif
