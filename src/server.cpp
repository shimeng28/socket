//
//  main.cpp
//  socket1
//
//  Created by shimeng on 2020/6/6.
//  Copyright © 2020 shimeng. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <thread>
#include <cstring>
#include "XTcp.hpp"


class TcpThread
{
public:
  void Main() {
    char buf[1024] = {0};
    while (true) {
      size_t len = client.Recv(buf, sizeof(buf) - 1);
      if (len < 0) break;
      buf[len] = '\0';
      printf("%s", buf);
      if (strstr(buf, "quit") != nullptr) {
        char recvMsg[] = "quit success!\n";
        client.Send(recvMsg, strlen(recvMsg) + 1);
        break;
      };
      client.Send("ok\n", 3);
    }
    client.Close();
    delete this;
  }
  XTcp client;
};

int main(int argc, const char * argv[]) {
  
  unsigned short port = 8080;
  if (argc > 1) {
    port = atoi(argv[1]);
  }
  XTcp server;
  server.CreateSocket();
  server.Bind(port);
  
  while (true) {
    XTcp client = server.Accept();
    TcpThread *th = new TcpThread();
    th->client = client;
    std::thread sth(&TcpThread::Main, th);
    // std::thread sth(ref(TcpThread::Main), th);
    sth.detach();
  }
  server.Close();
  return 0;
}
