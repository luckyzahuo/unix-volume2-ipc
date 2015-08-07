#include    <sys/types.h>   /* basic system data types */
#include    <sys/time.h>    /* timeval{} for select() */
#include    <time.h>    /* timespec{} for pselect() */
#include    <errno.h>
#include    <fcntl.h>   /* for nonblocking */
#include    <limits.h>  /* PIPE_BUF */
#include    <signal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <sys/stat.h>    /* for S_xxx file mode constants */
#include    <unistd.h>
#include    <sys/wait.h>

#ifdef  HAVE_MQUEUE_H
# include   <mqueue.h>  /* Posix message queues */
#endif
#ifdef  HAVE_SEMAPHORE_H
# include   <semaphore.h>   /* Posix semaphores */
#ifndef SEM_FAILED
#define SEM_FAILED  ((sem_t *)(-1))
#endif
#endif
#ifdef  HAVE_SYS_MMAN_H
# include   <sys/mman.h>    /* Posix shared memory */
#endif
#ifndef MAP_FAILED
#define MAP_FAILED  ((void *)(-1))
#endif
#ifdef  HAVE_SYS_IPC_H
# include   <sys/ipc.h> /* System V IPC */
#endif
#ifdef  HAVE_SYS_MSG_H
# include   <sys/msg.h> /* System V message queues */
#endif
#ifdef  HAVE_SYS_SEM_H
#ifdef  __bsdi__
#undef  HAVE_SYS_SEM_H /* hack: BSDI's semctl() prototype is wrong */
#else
# include   <sys/sem.h> /* System V semaphores */
#endif
#ifndef HAVE_SEMUN_UNION
/* $$.It semun$$ */
union semun { /* define union for semctl() */
int val;
struct semid_ds *buf;
unsigned short *array;
};
#endif
#endif  /* HAVE_SYS_SEM_H */
#ifdef  HAVE_SYS_SHM_H
# include   <sys/shm.h> /* System V shared memory */
#endif
#ifdef  HAVE_SYS_SELECT_H
# include   <sys/select.h>  /* for convenience */
#endif
#ifdef  HAVE_POLL_H
# include   <poll.h>    /* for convenience */
#endif
#ifdef  HAVE_STROPTS_H
# include   <stropts.h> /* for convenience */
#endif
#ifdef  HAVE_STRINGS_H
# include   <strings.h> /* for convenience */
#endif
/* Next three headers are normally needed for socket/file ioctl's:
 * * <sys/ioctl.h>, <sys/filio.h>, and <sys/sockio.h>.
 * */
#ifdef  HAVE_SYS_IOCTL_H
# include   <sys/ioctl.h>
#endif
#ifdef  HAVE_SYS_FILIO_H
# include   <sys/filio.h>
#endif
#ifdef  HAVE_PTHREAD_H
# include   <pthread.h>
#endif
#ifdef  HAVE_DOOR_H
# include   <door.h>    /* Solaris doors API */
#endif
#ifdef  HAVE_RPC_RPC_H
#ifdef _PSX4_NSPACE_H_TS /* Digital Unix 4.0b hack, hack, hack */
#undef  SUCCESS
#endif
# include   <rpc/rpc.h> /* Sun RPC */
#endif
/* Define bzero() as a macro if it's not in standard C library. */
#ifndef HAVE_BZERO
#define bzero(ptr,n) memset(ptr, 0, n)
#endif
/* Posix.1g requires that an #include of <poll.h> DefinE INFTIM, but many
 * systems still DefinE it in <sys/stropts.h>. We don't want to include
 * all the streams stuff if it's not needed, so we just DefinE INFTIM here.
 * This is the standard value, but there's no guarantee it is -1. */
#ifndef INFTIM
#define INFTIM (-1) /* infinite poll timeout */
#ifdef  HAVE_POLL_H
#define INFTIM_UNPH /* tell unpxti.h we defined it */
#endif
#endif
/* Miscellaneous constants */
#ifndef PATH_MAX /* should be in <limits.h> */
#define PATH_MAX    1024    /* max # of characters in a pathname */
#endif
#define MAX_PATH    1024
/* $$.ix [MAX_PATH]~constant,~definition~of$$ */
#define MAXLINE 4096    /* max text line length */
/* $$.ix [MAXLINE]~constant,~definition~of$$ */
/* $$.ix [BUFFSIZE]~constant,~definition~of$$ */
#define BUFFSIZE    8192    /* buffer size for reads and writes */

