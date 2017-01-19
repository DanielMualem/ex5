#include <iostream>
#include "MartialStatus.h"
#include "Driver.h"
#include "LuxuryCab.h"
#include "StandardCab.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "../sockets/Tcp.h"

BOOST_CLASS_EXPORT_GUID(Point, "Point");
BOOST_CLASS_EXPORT_GUID(LuxuryCab, "LuxuryCab");
BOOST_CLASS_EXPORT_GUID(StandardCab, "StandardCab");

using namespace std;

/**
 * createMartialStat function.
 * @param statusChar - W/D/M/S
 * @return MartialStat enum Object
 */
MartialStat createMartialStat (char statusChar) {
    switch (statusChar) {
        case 'W':
            return MartialStat::WIDOWED;
        case 'D':
            return MartialStat::DIVORCED;
        case 'M':
            return MartialStat::MARRIED;
        case 'S':
            return MartialStat::SINGLE;
        default:
            return MartialStat::SINGLE;
    }
}

int main(int argc, char* argv[]) {
    int id, age, experience, cabId;
    MartialStat status;
    char statusChar, dummy;
    //getting the driver's details and creating it
    cin >> id >> dummy >> age >> dummy >> statusChar >> dummy >> experience >> dummy >> cabId;
    status = createMartialStat(statusChar);
    Driver* driver = new Driver(id, age, status, experience, cabId);
    //creating the client's socket
    Socket* tcp = new Tcp(0, atoi(argv[2]), argv[1]);
    //initialize the socket
    tcp->initialize();
    //serialize the driver
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();
    //send the serialized driver
    char buffer[4096];
    tcp->sendData(serial_str, 0);

    Cab *driverCab;
    char *end = buffer + 4095;
    //recieve the cab's data from the server and un-serialize it
    tcp->receiveData(buffer, sizeof(buffer), 0);
    boost::iostreams::basic_array_source<char> device(buffer, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> driverCab;
    //set the taxi as the driver's cab
    driver->setTaxiCab(driverCab);
    //a loop that gets and sends messages to the server
    while (true) {
        tcp->receiveData(buffer, sizeof(buffer), 0);
        //if the message was "7"- terminate the client's thread
        if (atoi(buffer) == 7) {
            break;
        } else {
            //recieve the driver's new location data and de-serialize it
            Node* loc;
            boost::iostreams::basic_array_source<char> device(buffer, end);
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(device);
            boost::archive::binary_iarchive ia2(s3);
            ia2 >> loc;
            driver->setLocation(loc);
            //cout << *loc;
            delete loc;
        }
        //send a message that the data was received
        tcp->sendData("OK", 0);
    }
    //free all the allocated memory
    delete driverCab;
    delete driver;
    delete tcp;
    return 0;
}