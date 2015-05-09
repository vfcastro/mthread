/*
 * mthread.h: arquivo de inclus�o com os prot�tipos das fun��es a serem
 *            implementadas na realiza��o do trabalho.
 *
 * N�O MODIFIQUE ESTE ARQUIVO.
 *
 * VERS�O 1 - 24/03/2015
 */
#ifndef __mthread__
#define __mthread__

typedef struct mutex {
	int	flag; 					// indica se o mutex foi adquirido ou n�o (0: livre; 1: ocupado)
	struct TCB	*first, *last; 	// ponteiros para lista de threads bloqueadas no mutex
} mmutex_t;

int mcreate (int prio, (void*) (*start)(void*), void *arg);
int myield(void);
int mwait(int tid);
int mmutex_init(mmutex_t *mtx);
int mlock (mmutex_t *mtx);
int munlock (mmutex_t *mtx);

#endif
