/************************************************************
* File description: TCP header file. the class inherit from	*
* socket. methods of tcp socket type						*
************************************************************/

#ifndef TCP_H_
#define TCP_H_

#include "Socket.h"

class Tcp: public Socket {
private:
	int descriptorCommunicateClient;
public:
	/***********************************************************************
	* function name: Tcp												   *
	* The Input: Boolean, true - if server, false if client and port number*
	* The output: none										               *
	* The Function operation: creating new Tcp						       *
	***********************************************************************/
	Tcp(bool isServers, int port_num);
	/***********************************************************************
	* function name: Tcp												   *
	* The Input: Boolean, true - if server, false if client and port number*
	* The output: none										               *
	* The Function operation: creating new Tcp						       *
	***********************************************************************/
	Tcp(bool isServers, int port_num, string ip);
	/***********************************************************************
	* function name: ~Tcp												   *
	* The Input: none													   *
	* The output: none										               *
	* The Function operation: default destructor					       *
	***********************************************************************/
	virtual ~Tcp();
/***********************************************************************
	* function name: initialize											   *
	* The Input: none              										   *
	* The output: int number representing the return status		           *
	* The Function operation: initialize the Socket object and getting a   *
	* socket descriptor.												   *
	***********************************************************************/
	int initialize();
	/***********************************************************************
    * function name: acceptOneClient									   *
    * The Input: None                                                      *
    * The output: int number representing the descriptorCommunicateClient  *
    *    if it server or no-negative integer in client case                *
    *    or -1 when failed.                                                *
    * The Function operation: getting data from the other socket to,	   *
    * enter it to the buffer and print the data							   *
    ***********************************************************************/
	int acceptOneClient();
	/***********************************************************************
	* function name: sendData											   *
	* The Input: string representing the data to send		               *
	* The output: int number representing the return status		           *
	* The Function operation: sending the input data to the socket         *
	* who connect to this socket. 										   *
	***********************************************************************/
	int sendData(string data, int clientDescriptor);
	/***********************************************************************
	* function name: recive	`											   *
	* The Input: none										               *
	* The output: int number representing the return status	               *
	* The Function operation: getting data from the other socket and print *
	* the data															   *
	***********************************************************************/
	int receiveData(char* buffer, int size, int clientDescriptor);
};

#endif /* TCP_H_ */
