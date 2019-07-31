#ifndef MESSAGE_MANAGE_H_
#define MESSAGE_MANAGE_H_

#define MQTT_MSG_LENGTH 100
#define TOPIC_MSG_LENGTH 100

typedef struct{
	unsigned char  msg_type;
	unsigned char qos;
    unsigned char retained;
	unsigned short msg_id;
	unsigned char topic[TOPIC_MSG_LENGTH];
	unsigned char payload[MQTT_MSG_LENGTH];
    int payloadlen;
}MQTT_MSG;


int msg_man_add(int index, MQTT_MSG newmsg);
int msg_man_modify(int index,MQTT_MSG newmsg);
int msg_man_get(int index,unsigned short id,unsigned char type,MQTT_MSG *outMSG);
int msg_man_del(int index,unsigned short id,unsigned char type);
int msg_man_get_num(int index);
int msg_man_init(void);







#endif /* DEVICE_MANAGER_H_ */
