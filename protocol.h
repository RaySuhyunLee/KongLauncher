/*
 * Command protocol set for launcher
 */

#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#define CMD_ARM 0x01
#define CMD_DISARM 0x02
#define CMD_MODE 0x10
#define CMD_MOVE 0x20
#define CMD_FIRE 0x30

#define PARAM_MODE_MANUAL 0x01
#define PARAM_MODE_AUTO 0x02

#define param_uint8(buf, i) ((buf)[i*2])
#define param_uint16(buf, i) ((buf)[i*2] + (uint16_t)(buf)[i*2 + 1] << 8)
#define param_double(buf, i) ((double)param_uint16(buf, i))

#endif
