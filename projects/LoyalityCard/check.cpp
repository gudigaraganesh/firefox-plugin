#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/select.h>
#include "nuserial.h"
int nu_watch_serial_data (int sd, unsigned long miliseconds)
{
    int ret = 0;
    struct pollfd fds[1]={0};
    fds[0].fd = sd;
    fds[0].events = POLLIN | POLLPRI;
    fds[0].revents = 0;
    ret = poll (fds, 1, miliseconds);
    if (ret < 0)
      {
	  return -1;
      }
    if (fds[0].revents & POLLIN)
      {
	  ret = SPORT_READ;
      }
    return ret;
}
