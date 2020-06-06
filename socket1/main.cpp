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
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#endif



int main(int argc, const char * argv[]) {
  #ifdef WIN32
  WSADATA ws;
  WSAStartup(MAKEWORD(2, 2), &ws);
  #endif

  for (int i = 0; i < 2000; i++) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
      std::cout << "Socket create failed" << std::endl;
      return -1;
    }
    std::cout << "[" << sock << "]";
//    closesocket(sock);
  }
  std::cout << std::endl;
  
  return 0;
}
