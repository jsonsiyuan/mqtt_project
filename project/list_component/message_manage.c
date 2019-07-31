
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "message_manage.h"
#include "list.h"

typedef struct{
	struct list_head head;
	int lock;
}MSGCtx;

typedef struct{
	struct list_head node;
	MQTT_MSG msg;
}MSG_Node;


#define num_of_list 1

static MSGCtx _MSGCtx[num_of_list];
static int _MSGInited = 0;



void Lock_Init(int *lock)
{
	*lock=0;
}
void Lock_Lock(int *lock)
{
	*lock=1;
}
void Lock_ULock(int *lock)
{
	*lock=0;
}
int Lock_check(int *lock)
{
	return *lock;
}


int msg_man_add(int index, MQTT_MSG newmsg)
{
	MSG_Node *pMsgNode;
	struct list_head *pos;
	if (index >= num_of_list)return -1;
	if (!_MSGInited)return -1;

	Lock_Lock(&_MSGCtx[index].lock);
	list_for_each(pos,&_MSGCtx[index].head)
	{

		pMsgNode = (MSG_Node*)pos;
		if(pMsgNode.msg.msg_id==newmsg.msg_id&&pMsgNode.msg.msg_type==newmsg.msg_type)
		{
			msg_man_modify(index,newmsg);
		}
	}

	if (pos == &_MSGCtx[index].head)/*全部搜索完成后*/
	{
		pMsgNode = (MSG_Node*)malloc(sizeof(MSG_Node));
		if (NULL == pMsgNode)
		{
			Lock_ULock(&_MSGCtx[index].lock);
			return -1;
		}
		memcpy(&pMsgNode->dev,&newmsg,sizeof(newmsg));
		list_add(&pMsgNode->node,&_MSGCtx[index].head);  
	}
	Lock_ULock(&_MSGCtx[index].lock);

	return 0;
}

int msg_man_modify(int index,MQTT_MSG newmsg)
{
	MSG_Node *pMsgNode;
	struct list_head *pos;
	if (index >= num_of_list)return -1;
	if (!_MSGInited)return -1;
	Lock_Lock(&_MSGCtx[index].lock);
	list_for_each(pos,&_MSGCtx[index].head)
	{

		pMsgNode = (MSG_Node*)pos;
		if(pMsgNode.msg.msg_id==newmsg.msg_id&&pMsgNode.msg.msg_type==newmsg.msg_type)
		{
			break;
		}
	}

	if (pos != &_MSGCtx[index].head)/*没有搜索完成后*/
	{
		memcpy(&pMsgNode->msg,&newmsg,sizeof(pMsgNode->msg));
	}

	Lock_ULock(&_MSGCtx[index].lock);

	return 0;
}




int msg_man_get(int index,unsigned short id,unsigned char type,MQTT_MSG *outMSG)
{
	MSG_Node *pMsgNode = NULL;
	struct list_head *pos;
	
	if (index >= num_of_list)return -1;
	if (NULL == id || NULL == outMSG)return -1;
	if (!_MSGInited)return -1;

	Lock_Lock(&_MSGCtx[index].lock);
	list_for_each(pos,&_MSGCtx[index].head)
	{
		pMsgNode = (MSG_Node*)pos;
		if(pMsgNode.msg.msg_id==id&&pMsgNode.msg.msg_type==type)
		{
			break;
		}
	}
	Lock_ULock(&_MSGCtx[index].lock);
	if (pos == &_MSGCtx[index].head)return -1;
	memcpy(outMSG,&pMsgNode->msg,sizeof(pMsgNode->msg));

	return 0;
}

int msg_man_del(int index,unsigned short id,unsigned char type)
{
	MSG_Node *pMsgNode = NULL;
	struct list_head *pos;
	int delFlag = 0;
	if (index >= num_of_list)return -1;
	if (NULL == id)return -1;
	if (!_MSGInited)return -1;

	Lock_Lock(&_MSGCtx[index].lock);
	list_for_each(pos,&_MSGCtx[index].head)
	{
		pMsgNode = (MSG_Node*)pos;
		
		if(pMsgNode.msg.msg_id==id&&pMsgNode.msg.msg_type==type)
		{
			list_del(pos);
			delFlag = 1;
			break;
		}
	}
	Lock_ULock(&_MSGCtx[index].lock);
	if (pos != &_MSGCtx[index].head){
		if (pMsgNode && 1 == delFlag)
		{
			free(pMsgNode);
		}
	}
	return 0;
}


int msg_man_get_num(int index)
{
	int num=0;
	struct list_head *pos;
	if (index >= num_of_list)return -1;
	if (!_MSGInited)return -1;

	Lock_Lock(&_MSGCtx[index].lock);
	list_for_each(pos,&_MSGCtx[index].head)
	{
		num++;
	}
	Lock_ULock(&_MSGCtx[index].lock);

	return num;
}

int msg_man_init(void)
{
	if (_MSGInited)return 0;
	int i;
	for(i=0;i<num_of_list;i++)
	{
		INIT_LIST_HEAD(&_MSGCtx[i].head);
		Lock_Init(&_MSGCtx[i].lock);
	}
	_MSGInited = 1;

	return 0;
}



