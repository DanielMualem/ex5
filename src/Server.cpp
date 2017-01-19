#include "Server.h"
/**
 * Server constructor
 * @param tcp - the server's socket
 * @param driversNum - the drivers amount
 * @param taxiCenter - the taxi center
 */
Server::Server(Socket* tcp, int driversNum, TaxiCenter* taxiCenter) {
    this->driversNum = driversNum;
    this->tcp = tcp;
    this->num_of_connections = 0;
    this->taxiCenter = taxiCenter;
    pthread_mutex_init(&this->connection_locker, 0);
    pthread_mutex_init(&this->list_locker, 0);
}
/**
 * start function
 * accepting each client and starts the comunication with him
 */
void Server::start() {
    for (int i = 0; i < driversNum; i++) {
        ClientData* data;
        pthread_t thread;
        //accept each client
        int clientDescriptor = tcp->acceptOneClient();
        //if the accept succeeded
        if (clientDescriptor >= 0) {
            // Create the clients data
            data = new ClientData();
            data->clientDescriptor = clientDescriptor;
            data->server = this;
            // Push the client to the list
            pthread_mutex_lock(&this->list_locker);
            this->clients.push_back(data);
            pthread_mutex_unlock(&this->list_locker);
            // Create a thread in order to listen to the client
            pthread_create(&thread, NULL, threadFunction, (void *) data);
            this->clientsThreads.push_back(thread);
        }
    }
    for (int i = 0; i < (int)this->clientsThreads.size(); i++) {
        pthread_join(clientsThreads[i], NULL);
    }
}
/**
 * threadFunction
 * @param element - the element to pass to the function we want the thread to run
 * @return NULL
 */
void* Server::threadFunction(void* element){
    ClientData* data = (ClientData*)element;
    data->server->receiveMessages(element);
    data = NULL;
    return NULL;
}
/**
 * receiveMessages function
 * recieves the messages from the server to the client
 * @param element
 */
void Server::receiveMessages(void* element) {
    ClientData *data = (ClientData *) element;
    //lock the numOfConnection counter
    pthread_mutex_lock(&this->connection_locker);
    this->num_of_connections++;
    pthread_mutex_unlock(&this->connection_locker);
    Driver *driver;
    char buffer[4096];
    //receive the data from the client
    tcp->receiveData(buffer, sizeof(buffer), data->clientDescriptor);
    char *end = buffer + 4095;
    //serialize the driver
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
    tcp->sendData(serial_str, data->clientDescriptor);
}
/**
 * Server destructor
 */
Server::~Server(){
    for (int i = 0; i < (int)this->clients.size(); i++) {
        delete this->clients[i];
    }
}