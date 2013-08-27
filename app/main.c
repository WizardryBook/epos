#include <stdarg.h>

int task_exit(int val);
int task_create(unsigned stack, void *func, unsigned pv);
int task_getid();
void task_yield();
int task_wait(int tid, int *exit_code);
int task_sleep(unsigned msec);
int putchar(int c);

int sprintf(char *buf, const char *fmt, ...);
int vsprintf(char *buf, const char *fmt, va_list args);
int printf(const char *fmt,...)
{
	char buf[1024];
	va_list args;
	int i, j;

	va_start(args, fmt);
	i=vsprintf(buf,fmt,args);
	va_end(args);

	for(j = 0; j < i; j++)
		putchar(buf[j]);

	return i;
}

static unsigned fib(unsigned n)
{
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;
  return fib(n - 1) + fib(n - 2);
}

static void hanoi(int d, char from, char to, char aux)
{
  if(d == 1) {
    task_sleep(8000);
    printf("%c%d%c ", from, d, to);
    return;
  }

  hanoi(d - 1, from, aux, to);
  task_sleep(8000);
  printf("%c%d%c ", from, d, to);
  hanoi(d - 1, aux, to, from);
}

static void tsk_fib(void *pv)
{
  int i, code;
//  printf("task #%d: pv=0x%08x\n\r", task_getid(), pv);

  printf("task #%d: waiting task #%d\n\r", task_getid(), 3);
  task_wait(3, &code);
  printf("task #%d: task #%d exit with code %d\n\r", task_getid(), 3, code);

  for(i = 38; i < 48; i++)
    printf("task #%d: fib(%d)=%u\n\r", task_getid(), i, fib(i));
    
  printf("task #%d: Exiting\n\r", task_getid());

  task_exit((int)pv);
}

static tsk_hanoi(void *pv)
{
  int n = (int)(pv);
  printf("task #%d: Hanoi tower with %d plates\n\r", task_getid(), pv);
  if(n <= 0) {
    printf("task #%d: Illegal number of plates %d\n\r", n);
    task_exit(-1);
  }
  
  hanoi(n, 'A', 'B', 'C');

  printf("task #%d: Exiting\n\r", task_getid());
  task_exit(0);
}

void main(void *pv)
{
  int code;
  printf("task #%d: Hello, I'm the first user task(pv=0x%08x)!\n\r", task_getid(), pv);

  printf("task #%d: task #%d created\n\r", task_getid(), task_create(0xa0000000, tsk_hanoi, 6));
  printf("task #%d: task #%d created\n\r", task_getid(), task_create(0xb0000000, tsk_fib, 0x19760206));

  printf("task #%d: waiting task #%d\n\r", task_getid(), 3);
  task_wait(3, &code);
  printf("task #%d: task #%d exit with code %d\n\r", task_getid(), 3, code);

  while(1) {
    task_sleep(500000);
    printf("task #%d: fib(%d)=%u\n\r", task_getid(), 37, fib(37));
  }
  task_exit(0);
}

/**
 * GCC insists on __main
 *    http://gcc.gnu.org/onlinedocs/gccint/Collect2.html
 */
void __main()
{
}

