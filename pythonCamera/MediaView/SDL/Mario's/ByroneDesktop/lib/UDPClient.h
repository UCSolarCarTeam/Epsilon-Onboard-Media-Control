#ifndef UDPCLIENT_H
#define UDPCLIENT_H
class UDPClient {
	public:
		UDPClient(char* host_addr, int host_port);
		~UDPClient();
		int receive(char* buffer, int len);
		int send(char* buffer, int len);
	private:
	
	
};

#endif
