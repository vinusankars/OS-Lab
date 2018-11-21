void comm_func() 
{
  int sock;
  int i=0;
  struct sockaddr_in server;
  char message[1024] , server_reply[2000];

  //Create socket
  sock = socket(AF_INET , SOCK_STREAM , 0);
  if (sock == -1)
  {
      printf("Could not create socket");
  }
  // puts("Socket created");

  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_family = AF_INET;
  server.sin_port = htons( 8888 );

  //Connect to remote server
  if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
  {
      perror("connect failed. Error");
  }

  // Receive a reply from the server
  if( recv(sock , server_reply , 2000 , 0) < 0)
  {
      puts("recv failed");
  }
  puts(server_reply);
  write(sock,server_reply,50);
  for (i=0; i< strlen(server_reply); i++)
  {
    server_reply[i] = '\0';
  }
  close(sock);
}