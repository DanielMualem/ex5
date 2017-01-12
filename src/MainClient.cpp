#include <iostream>
#include "../sockets/Udp.h"
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

BOOST_CLASS_EXPORT_GUID(Point, "Point");
BOOST_CLASS_EXPORT_GUID(LuxuryCab, "LuxuryCab");
BOOST_CLASS_EXPORT_GUID(StandardCab, "StandardCab");

using namespace std;
using namespace boost::archive;

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
    cin >> id >> dummy >> age >> dummy >> statusChar >> dummy >> experience >> dummy >> cabId;
    status = createMartialStat(statusChar);
    Driver* driver = new Driver(id, age, status, experience, cabId);

    Socket* udp = new Udp(0, atoi(argv[2]), argv[1]);
    udp->initialize();
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();
    char buffer[4096];
    udp->sendData(serial_str);

    Cab *driverCab;
    char *end = buffer + 4095;
    udp->reciveData(buffer, sizeof(buffer));
    boost::iostreams::basic_array_source<char> device(buffer, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> driverCab;
    driver->setTaxiCab(driverCab);

    while (true) {
        udp->reciveData(buffer, sizeof(buffer));

        if (atoi(buffer) == -1) {
            break;
        } else {
            Node* loc;
            boost::iostreams::basic_array_source<char> device(buffer, end);
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(device);
            boost::archive::binary_iarchive ia2(s3);
            ia2 >> loc;
            driver->setLocation(loc);
            delete loc;
        }
    }


    delete driverCab;
    delete driver;
    delete udp;
    return 0;
}