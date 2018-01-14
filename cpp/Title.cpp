#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

static char *argv_last;

int              ubee_argc;
char           **os_argv;


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
    return -1;
  }

  argv_last = os_argv[0];

  for(i = 0; os_argv[i]; i++) {
    if(argv_last == os_argv[i]) {
      argv_last = os_argv[i] + strlen(os_argv[i]) + 1;
    }
  }

  for(i = 0; environ[i]; i++) {
    if(argv_last == environ[i]) {

      size = strlen(environ[i]) + 1;
      argv_last = environ[i] + size;

      ubee_cpystrn(p, (char *) environ[i], size);
      environ[i] = (char *) p;
      p += size;
    }
  }

  argv_last--;

  return 0;
}


void
ubee_setproctitle(const char *title, const char * name)
{
  char     *p;

  os_argv[1] = NULL;

  p = ubee_cpystrn((char *) os_argv[0], (char *) name,
                  argv_last - os_argv[0]);

  p = ubee_cpystrn(p, (char *) title, argv_last - (char *) p);

  if(argv_last - (char *) p) {
    memset(p, '\0', argv_last - (char *) p);
  }

}


static int ubee_save_argv(int argc, char *const *argv)
{

  os_argv = (char **) argv;
  ubee_argc = argc;

  return 0;
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
