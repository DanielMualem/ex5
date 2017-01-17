//
// Created by mor on 17/01/17.
//

#include "Server.h"

Server::Server(Socket* tcp, int driversNum, TaxiCenter* taxiCenter) {
    this->driversNum =driversNum;
    this->tcp = tcp;
    this->clients = new list<ClientData*>;
    this->server_socket = -1;
    this->capacity = 50;
    this->num_of_connections = 0;
    this->online = false;
    this->taxiCenter = taxiCenter;
    // Init mutex
    pthread_mutex_init(&this->connection_locker, 0);
    pthread_mutex_init(&this->list_locker, 0);
}
void Server::start() {

    int client;
    int client_socket;
    unsigned int client_size;
    ClientData* data;
    pthread_t thread;

    for (int i = 0; i < driversNum; i++) {

        cout << "accepting client in server\n";
        int clientDescriptor = tcp->acceptOneClient();

        if (clientDescriptor >= 0) {
            cout << "entering if";
            // Create the clients data
            data = new ClientData();
            //data->client_socket = client_socket;
            data->clientDescriptor = clientDescriptor;
            //data->client_size = client_size;
            data->server = this;
            data->online = true;

            // Push the client to the list
            cout << "locking";
            pthread_mutex_lock(&this->list_locker);
            this->clients->push_back(data);
            pthread_mutex_unlock(&this->list_locker);

            cout << "creating pthread";
            // Create a thread in order to listen to the client
            pthread_create(&thread, NULL, threadFunction, (void *) data);
        }
    }
}

void* Server::threadFunction(void* element){
    ClientData* data = (ClientData*)element;
    data->server->receiveMessages(element);
    data = NULL;
    return NULL;
}
void Server::receiveMessages(void* element) {
    ClientData *data = (ClientData *) element;

    pthread_mutex_lock(&this->connection_locker);
    this->num_of_connections++;
    pthread_mutex_unlock(&this->connection_locker);
    cout << "Connected clients: " << this->num_of_connections << endl;

    Driver *driver;
    char buffer[4096];
    cout << "receiving data in server\n";
    tcp->receiveData(buffer, sizeof(buffer), data->clientDescriptor);
    char *end = buffer + 4095;
    boost::iostreams::basic_array_source<char> device(buffer, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> driver;

    //getting the driver's cab
    Cab *driverCab = taxiCenter->getCab(driver->getCabID());
    driver->setTaxiCab(driverCab);
    driver->setClientDescriptor(data->clientDescriptor);
    taxiCenter->addDriver(driver);

    //sending the driver's taxi
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driverCab;
    s.flush();
    cout << *driver;

    cout << "sending data in server\n";
    tcp->sendData(serial_str, data->clientDescriptor);

    // while (data->online) {

    /*if (mission == 7) {
        data->online = false;

        // Reduce number of connections
        pthread_mutex_lock(&this->connection_locker);
        this->num_of_connections--;
        pthread_mutex_unlock(&this->connection_locker);

        // Print number of connections
        cout << "Connected clients: " << this->num_of_connections << endl;

        delete tcp;
    }*/

    //cout << "sending data in server\n";
    //tcp->sendData(serial_str, data->clientDescriptor);

    //sending data- moving!
    //serialize the point
    //what to do with taxi center?
    //}
}
Server::~Server(){

}