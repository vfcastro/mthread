#include "../include/mthread.h"
#include "../include/mdata.h"

TCB_t *MAIN = NULL;
TCB_t *EXEC = NULL;
int TID = 0;

int main_init();
void mfinish();

int mcreate (int prio, void* (*start)(void*), void *arg)
{
	if(main_init() == ERROR)
		return ERROR;
	
	TCB_t *newThread = (TCB_t*)malloc(sizeof(TCB_t));
	ucontext_t *newContext = (ucontext_t*) malloc(sizeof(ucontext_t));
	ucontext_t *endContext = (ucontext_t*) malloc(sizeof(ucontext_t));
	void *new_stack = (char*) malloc(STACKSIZE);
	void *end_stack = (char*) malloc(STACKSIZE);
	
	if(newThread != NULL && newContext != NULL && endContext != NULL && new_stack != NULL && end_stack != NULL){
		getcontext(newContext);
		newContext->uc_stack.ss_sp = new_stack;
		newContext->uc_stack.ss_size = STACKSIZE;
		newContext->uc_link = endContext;
		makecontext(newContext, (void (*)(void))start, 1, arg);

		getcontext(endContext);
		endContext->uc_stack.ss_sp = end_stack;
		endContext->uc_stack.ss_size = STACKSIZE;
		endContext->uc_link = NULL;
		makecontext(endContext, mfinish, 0);
		
		newThread->tid = ++TID;
		newThread->state = STATE_READY;
		newThread->prio = prio;
		newThread->context = *(newContext);
		newThread->prev = NULL;
		newThread->next = NULL;
	}
}


int main_init()
{	
	ucontext_t *main_context = (ucontext_t*) malloc(sizeof(ucontext_t));
	if(main_context == NULL)
		return ERROR;
	
	getcontext(main_context);
	if(MAIN == NULL){
		MAIN = (TCB_t*)malloc(sizeof(TCB_t));
		if(MAIN == NULL)
			return ERROR;
		
		MAIN->tid = 0;
		MAIN->state = STATE_RUNNING;
		MAIN->prio = 0;
		MAIN->context = *(main_context);
		MAIN->prev = NULL;
		MAIN->next = NULL;
		EXEC = MAIN;
		setcontext(main_context);
	}
	return SUCCESS;
}

void mfinish()
{
	

}





int myield(void);
int mwait(int tid){
}
int mmutex_init(mmutex_t *mtx);
int mlock (mmutex_t *mtx);
int munlock (mmutex_t *mtx);
