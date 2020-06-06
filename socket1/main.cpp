//
//  main.cpp
//  socket1
//
//  Created by shimeng on 2020/6/6.
//  Copyright © 2020 shimeng. All rights reserved.
//
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h> // close
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define closesocket close
#endif

#include <iostream>
#include <cstdlib>


int main(int argc, const char * argv[]) {
  #ifdef WIN32
  WSADATA ws;
  WSAStartup(MAKEWORD(2, 2), &ws);
  #endif

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    std::cout << "Socket create failed" << std::endl;
    return -1;
  }
  unsigned short port = 8080;
  if (argc > 1) {
    port = atoi(argv[1]);
  }
  sockaddr_in saddr;
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(port);
  saddr.sin_addr.s_addr = htonl(0);
  
  if (bind(sock, (sockaddr*)(&saddr), sizeof(saddr)) != 0) {
    std::cout << "bind port fail " << port << std::endl;
    return -2;
  } else {
    std::cout << "bind success " << port << std::endl;
  }
  
  listen(sock, 10);
  
  return 0;
}
