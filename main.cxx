#include "tictactoe.h"
#include "server.h"
#include "client.h"

#if 0
#define SERVER
#else
#define CLIENT
#endif

int main() {

  Position pos;
#ifdef SERVER
  start_server(pos);
#else
  start_client(pos);
#endif

  return 0;
}