//
//  XTcp.hpp
//  socket1
//
//  Created by shimeng on 2020/6/6.
//  Copyright © 2020 shimeng. All rights reserved.
//

#ifndef XTcp_hpp
#define XTcp_hpp

#include <string>


class XTcp 
{
public:
  XTcp();
  void CreateSocket();
  bool Bind(unsigned int short port);
  XTcp Accept();
  void Close();
  int Recv(char* buf, int bufSize);
  int Send(const char* buf, int sendSize);
  bool Connect(const char* ip, unsigned short port);
  virtual ~XTcp();
  int sock = 0;
  unsigned int port = 0;
  char ip[16];
};

#endif /* XTcp_hpp */
