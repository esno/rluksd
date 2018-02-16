#ifndef LUKSD_H
#define LUKSD_H

#include <stdint.h>
#include <sys/socket.h>
#include <sys/un.h>

#define LUKSD_SOCKET_FILE_PATH "/run/luksd.sock"
#define LUKSD_SOCKET_HEADER_LENGTH_SIZE 2
#define LUKSD_SOCKET_PAYLOAD_SIZE 1024

enum {
  LUKSD_SOCKET_REQ_METHOD_STATUS = 0x02,
  LUKSD_SOCKET_REQ_METHOD_UNLOCK,
  LUKSD_SOCKET_REQ_METHOD_LOCK
};

typedef struct {
  unsigned char *message;
  uint16_t message_l;
  int socket;
  unsigned char method;
} luksd_message_t;

typedef struct {
  int socket;
  struct {
    char *user;
    char *group;
    char *socket_file;
  } config;
} luksd_mgr_t;

typedef struct {
  struct sockaddr_un addr;
  socklen_t addrlen;
} luksd_peer_t;

void luksd_handle_req_status(luksd_mgr_t *luksd, luksd_message_t *msg);
void luksd_handle_requests(luksd_mgr_t *luksd);
int luksd_parse_args(luksd_mgr_t *luksd, int argc, char *argv[]);
void luksd_usage(void);

#endif
