#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  NGX_OK          0
#define  NGX_ERROR      -1
#define NGX_SETPROCTITLE_PAD       '\0'


extern char **environ;

static char *ubee_os_argv_last;

int              ubee_argc;
char           **ubee_os_argv;


char * ubee_cpystrn(char *dst, char *src, size_t n)
{
  if(n == 0) {
    return dst;
  }

  while(--n) {
    *dst = *src;

    if(*dst == '\0') {
      return dst;
    }

    dst++;
    src++;
  }

  *dst = '\0';

  return dst;
}



int
ubee_init_setproctitle()
{
  char      *p;
  size_t       size;
  unsigned int   i;

  size = 0;

  for(i = 0; environ[i]; i++) {
    size += strlen(environ[i]) + 1;
  }

  p = (char *)malloc(size);
  if(p == NULL) {
    return NGX_ERROR;
  }

  ubee_os_argv_last = ubee_os_argv[0];

  for(i = 0; ubee_os_argv[i]; i++) {
    if(ubee_os_argv_last == ubee_os_argv[i]) {
      ubee_os_argv_last = ubee_os_argv[i] + strlen(ubee_os_argv[i]) + 1;
    }
  }

  for(i = 0; environ[i]; i++) {
    if(ubee_os_argv_last == environ[i]) {

      size = strlen(environ[i]) + 1;
      ubee_os_argv_last = environ[i] + size;

      ubee_cpystrn(p, (char *) environ[i], size);
      environ[i] = (char *) p;
      p += size;
    }
  }

  ubee_os_argv_last--;

  return NGX_OK;
}


void
ubee_setproctitle(const char *title, const char * name)
{
  char     *p;

  ubee_os_argv[1] = NULL;

  p = ubee_cpystrn((char *) ubee_os_argv[0], (char *) name,
                  ubee_os_argv_last - ubee_os_argv[0]);

  p = ubee_cpystrn(p, (char *) title, ubee_os_argv_last - (char *) p);

  if(ubee_os_argv_last - (char *) p) {
    memset(p, NGX_SETPROCTITLE_PAD, ubee_os_argv_last - (char *) p);
  }

}


static int
ubee_save_argv(int argc, char *const *argv)
{

  ubee_os_argv = (char **) argv;
  ubee_argc = argc;

  return NGX_OK;
}

int main(int argc, char *const *argv)
{

 int rtn;
  ubee_save_argv(argc,argv);
  ubee_init_setproctitle();

  ubee_setproctitle("xiejian test","work :");

  while(1) {
    rtn = system("ps -ef|awk '$8 ~ /work/ {print $0}'");
    sleep(10);
  }

  return (0);
}
