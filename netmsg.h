/*
 *  For Ato_dap board
 *
 *  netmsg.h -- message definition between ato_dap and mca
 *
 *  Created on: 2016-5-10
 *  Author: huadu
 */

#ifndef NETMSG_H_
#define NETMSG_H_

//#include "lib/stream.h"

#define NET_MSG_HEADER_VER           0x01
#define NET_MSG_WEB_MODULE           0x01
#define NET_MSG_CLIENT_MODULE        0X02
#define NET_MSG_FLAG                 0x00

/*packet type*/
#define NET_MSG_CONFIG_PACKET     		0x01
#define NET_MSG_REQ_CONFIG_PACKET       0x02
#define NET_MSG_CMD_PACKET              0x03

#define NET_MSG_PKT_TOO_SMALL -1
#define NET_MSG_HEADER_SIZE sizeof(struct net_msg_header)

/*

  Network message Header between MCA & ATO_DAP (Command Packet)
  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |  Verion     |   Packet  Type  |  Module Type  | flag          |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |                         Total Length                          |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

  Version: Network Message protocol version
  Packet Type: Acquire,clear,set,query packet
  Module Type: Packet come from which Module(MCA/ATO)
  flag: Packet subclass.
 */

struct net_msg_header {
	u_char version;
	u_char type;
	u_char module; /*refer to web or client. */
	u_char flag;
    unsigned int length; /*total length of the packet*/
};

/*Configuration packet of the network message.*/
struct filtering_molding_time
{
	double filtering_molding_rising_time_value;
	double filtering_molding_flat_topping_time;
};

struct screening_time
{
	double screening_time_rising_time_value;
};

struct high_voltage
{
	double voltage_value;
	double rising_speed;
};
#pragma pack(1)

struct mca_param
{
	int channel_no;       /*channel no, Two channel: channel0 or channel1*/
	int input_pulse_polarity;
	int nal;
	int channel_num;
	double gain;
	double threshold_value;
	double filtering_molding_rising_time_value;
	double filtering_molding_flat_topping_time;
	double screening_time_rising_time_value;
	int baseline_restorer;
    int decay_time_constant;
	double voltage_value;
	double rising_speed;
};
#pragma pack(0)
/*

#define NET_MSG_CMD_PACKET     	    0x03

Version:     NET_MSG_HEADER_VER
packet type: NET_MSG_CMD_PACKET
module type: NET_MSG_MODULE
flag       : NET_MSG_FLAG

 Network message Header between MCA & ATO_DAP (config Packet)
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |  Verion     |   Packet  Type  |  Module Type  | flag          |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |                         Total Length                          |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |                          Command Type Data                    |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 Version: Network Message protocol version
 Packet Type: Acquire,clear,set,query packet
 Module Type: Packet come from which Module(MCA/ATO)
 flag: Packet subclass.
 */
struct msg_cmd_packet {
	u_char cmd; /*Start/continue acquiring of data*/
	u_char padding1;
	u_char padding2;
	u_char padding3;
};

/*Function Declearation.*/
//int  msg_decode_header(struct stream*, struct net_msg_header*);
//int msg_decode_conf_param(struct stream*,struct mca_param*);

#endif /* NETMSG_H_ */

