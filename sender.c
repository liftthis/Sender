#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

typedef struct _point {
    float lat;
    float lon;
    float alt;
  } point;

int main(int argc, char **argv) {
  if (argc < 4) {
    printf("Usage: %s <tablet ip> <lat> <lon> <alt>\n", argv[0]);
    return 1;
  }
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(4444);
  inet_pton(AF_INET, argv[1], &addr.sin_addr);

  point pt;
  pt.lat = strtof(argv[2], NULL);
  pt.lon = strtof(argv[3], NULL);
  pt.alt = strtof(argv[4], NULL);
  sendto(sockfd, &pt, sizeof(point), 0, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
  printf("send packet with %f, %f, %f", pt.lat, pt.lon, pt.alt);

  return 0;
}
