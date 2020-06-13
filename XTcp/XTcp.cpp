 //
//  XTcp.cpp
//  socket1
//
//  Created by shimeng on 2020/6/6.
//  Copyright © 2020 shimeng. All rights reserved.
//
#include "./XTcp.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef WIN32
  #include <windows.h>
#else
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <unistd.h> // close
  #include <arpa/inet.h>
  #define closesocket close
#endif

#include <iostream>
#include <thread>

XTcp::XTcp() 
{
  #ifdef WIN32
    static bool first = true;
    if (first) {
      first = false;
      WSADATA ws;
      WSAStartup(MAKEWORD(2, 2), &ws);
    }
  #endif
};

void XTcp::CreateSocket() 
{
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    std::cout << "Socket create failed" << std::endl;
  }
};

bool XTcp::Bind(unsigned short port) 
{
  if (sock <= 0) {
    CreateSocket();
  }

  sockaddr_in saddr;
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(port);
  saddr.sin_addr.s_addr = htonl(0);
  
  if (bind(sock, (sockaddr*)(&saddr), sizeof(saddr)) != 0) {
    std::cout << "bind port fail " << port << std::endl;
    return false;
  } else {
    std::cout << "bind success " << port << std::endl;
  }
  listen(sock, 10);
  return true;
};

XTcp XTcp::Accept()
{
  XTcp tcp;
  sockaddr_in caddr;
  socklen_t clen = sizeof(caddr);

  int client = accept(sock, (sockaddr*)&caddr, &clen);
  if (client <= 0) {
    return tcp;
  }
  tcp.sock = client;
  char* ip = inet_ntoa(caddr.sin_addr);
  strcpy(tcp.ip, ip);
  tcp.port = ntohs(caddr.sin_port);
  return tcp;
};

void XTcp::Close()
{
  if (sock <= 0) {
    return;
  }

  closesocket(sock);
}

int XTcp::Recv(char* buf, int bufsize)
{
  return recv(sock, buf, bufsize, 0);
};

int XTcp::Send(const char* buf, int sendSize)
{
  int sendedSize = 0;
  while (sendedSize !=  sendSize) {
    int len = send(sock, buf + sendedSize, sendSize - sendedSize, 0);
    if (len < 0) {
      break;
    }
    sendedSize += len;
  }
  return sendedSize;
};

XTcp::~XTcp() 
{

}
