

#ifndef EX3_SERVER_H
#define EX3_SERVER_H

#include <list>
#include <pthread.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <sstream>
#include <stdexcept>
#include "../sockets/Tcp.h"
#include <iostream>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "TaxiCenter.h"
#include "Server.h"
#include "Cab.h"
#include "Driver.h"

using namespace std;
using namespace boost::iostreams;
using namespace boost::archive;

class Server {
private:
    struct ClientData {
        int client_socket;
        int clientDescriptor;
        unsigned int client_size;
        bool online;
        Server *server;
    };
    int capacity;
    int num_of_connections;
    int server_socket;
    bool online;
    Socket *tcp;
    TaxiCenter *taxiCenter;
    int driversNum;

    struct sockaddr_in server_details;
    list<ClientData *> *clients;
    pthread_mutex_t connection_locker;
    pthread_mutex_t list_locker;


public:
    Server(Socket* tcp, int driversNum, TaxiCenter* taxiCenter);

    void start();

    static void *threadFunction(void *element);

    void receiveMessages(void *element);

    virtual ~Server();

};

#endif //EX3_SERVER_H
