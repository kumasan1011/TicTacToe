/*
  Playing server for tictactoe
*/

#include <iostream>
#include <vector>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#include "server.h"

#define ERROR 0
#define EXIT  1

std::vector<std::string> split(const std::string& src, const char* delim = ",") {
  
  std::vector<std::string> vec;
  std::string::size_type len = src.length();

  for (std::string::size_type i = 0, n; i < len; i = n + 1) {
    n = src.find_first_of(delim, i);
    if (n == std::string::npos) {
      n = len;
    }
    vec.push_back(src.substr(i, n - i));
  }

  return vec;
}

int exchange_messages(int sock, char *buf) {
  
  std::string str = std::string(buf);
  std::vector<std::string> svec = split(str, " ");

  std::string pName;
  // 引数
  switch (svec.size()) {
    case 0:
    write(sock, "ERROR", sizeof("ERROR"));
    return ERROR;
    case 1:
    write(sock, "ERROR", sizeof("ERROR"));
    return ERROR;
    case 2: // LOGIN (username) or LOGOUT (username)
    if (svec[0] == "LOGIN") {
      pName = svec[1];
      std::string temp = "LOGIN " + svec[1] + " OK";
      write(sock, temp.c_str(), sizeof(temp.c_str()));
    }
    else if (svec[0] == "LOGOUT") {
      pName = svec[1];
      std::string temp = "LOGOUT " + svec[1] + " OK";
      write(sock, temp.c_str(), sizeof(temp.c_str()));
    }
    break;
    case 3: // 
    break;
    
  }

}

void start_server(Position &pos) {
  
  int sock0;
  struct sockaddr_in addr;
  struct sockaddr_in client;
  socklen_t len;
  int sock;
  int pid, cpid;
  char buf[1024];
  int n;
  int status;

  /* ソケットの作成 (1) */
  sock0 = socket(AF_INET, SOCK_STREAM, 0);

  /* ソケットの設定 */
  addr.sin_family = AF_INET;
  addr.sin_port = htons(333333);
  addr.sin_addr.s_addr = INADDR_ANY;

  bind(sock0, (struct sockaddr *)&addr, sizeof(addr));

  /* TCPクライアントからの接続要求を待てる状態にする */
  listen(sock0, 5);
  /* (1) 終わり */

  /* (2) */
  while (true) {
    /* TCPクライアントからの接続要求を受け付ける */
    len = sizeof(client);
    sock = accept(sock0, (struct sockaddr *)&client, &len);

    /* (3) */
    pid = fork();

    if (pid == 0) {

      // 文字列のやりとり
      while (true) {
        /* child process */
        n = read(sock, buf, sizeof(buf));
        if (n < 0) {
          perror("read");
          return;
        }
        
        write(sock, buf, n);
      }
      /* TCPセッションの終了 */
      close(sock);
      return;

    } else {
      /* (4) */
      while ((cpid = waitpid(-1, &status, WNOHANG)) > 0);

      if (cpid < 0 && errno != ECHILD) {
        perror("waitpid");
        return;
      }
    }
  }

  /* (5) */
  /* listen するsocketの終了 */
  close(sock0);
}