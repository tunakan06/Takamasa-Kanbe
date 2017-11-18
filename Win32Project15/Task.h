#ifndef _TASK_H
#define _TASK_H

class Task
{
public:

	Task();

	~Task();

	typedef struct _STaskBaseInfo {

		void ( * Draw )( struct _STaskInfo *TInfo , float st );

	} STaskBaseInfo;

	typedef struct _STaskInfo {

		void*	Data;

	} STaskInfo;

private:
	
};

#endif

