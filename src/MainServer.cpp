#include <iostream>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "GridTwoD.h"
#include "TaxiCenter.h"
#include "LuxuryCab.h"
#include "StandardCab.h"
#include "../sockets/Udp.h"

BOOST_CLASS_EXPORT_GUID(Point, "Point");
BOOST_CLASS_EXPORT_GUID(LuxuryCab, "LuxuryCab");
BOOST_CLASS_EXPORT_GUID(StandardCab, "StandardCab");
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
/**
 * createManufacturer function.
 * @param statusChar - H/S/T/F/H
 * @return Manufacturer enum object
 */
Manufacturer createManufacturer (char statusChar) {
    switch (statusChar) {
        case 'H':
            return Manufacturer::HONDA;
        case 'S':
            return Manufacturer::SUBARO;
        case 'T':
            return Manufacturer::TESLA;
        case 'F':
            return Manufacturer::FIAT;
        default:
            return Manufacturer::HONDA;
    }
}
/**
 * createColor function.
 * @param statusChar - R/B/G/P/W
 * @return Color enum object
 */
Color createColor (char statusChar) {
    switch (statusChar) {
        case 'R':
            return Color::RED;
        case 'B':
            return Color::BLUE;
        case 'G':
            return Color::GREEN;
        case 'P':
            return Color::PINK;
        case 'W':
            return Color::WHITE;
        default:
            return Color::WHITE;
    }
}
/**
 * addDriver function.
 * creates and adds a driver to the taxi center.
 * @param taxiCenter - the taxi center
 * @param grid - map
 */
void addDriver(TaxiCenter* taxiCenter, Socket* udp){
    Driver *driver;
    char buffer[4096];
    udp->reciveData(buffer, sizeof(buffer));
    char *end = buffer + 4095;
    boost::iostreams::basic_array_source<char> device(buffer, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> driver;
    //getting the driver's cab
    Cab *driverCab = taxiCenter->getCab(driver->getCabID());
    driver->setTaxiCab(driverCab);
    taxiCenter->addDriver(driver);

    //sending the driver's taxi
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driverCab;
    s.flush();
    udp->sendData(serial_str);
}
/**
 * addRide function.
 * creates and adds a trip to the taxi center.
 * @param taxiCenter - the taxi center.
 */
void addRide(TaxiCenter* taxiCenter, GridTwoD* grid) {
    int rideId, passengersNum, xStart, yStart, xEnd, yEnd;
    double tariff, time;
    char dummy;
    cin >> rideId >> dummy >> xStart >> dummy >> yStart >> dummy >> xEnd >> dummy >>
        yEnd >> dummy >> passengersNum >> dummy >> tariff >> dummy >> time;
    Point** map = grid->getGrid();
    TripInfo* trip = new TripInfo(rideId, &map[xStart][yStart], &map[xEnd][yEnd], passengersNum, tariff,time);
    taxiCenter->addTrip(trip);
}
/**
 * addVehicle function.
 * creates and adds a cab to the taxi center.
 * @param taxiCenter - the taxi center.
 */
void addVehicle(TaxiCenter* taxiCenter){
    int cabId, taxiType;
    Manufacturer manufacturer;
    Color color;
    char colorChar, manufacturerChar, dummy;
    cin >> cabId >> dummy >> taxiType >> dummy >> manufacturerChar >> dummy >> colorChar;
    manufacturer = createManufacturer(manufacturerChar);
    color = createColor(colorChar);
    Cab* cab = NULL;
    if (taxiType == 1) {
        cab = new StandardCab(cabId, manufacturer, color);
    } else if (taxiType == 2) {
        cab = new LuxuryCab(cabId, manufacturer, color);
    }
    taxiCenter->addCab(cab);
}
/**
 * gets a driver's location by a specific ID.
 * @param taxiCenter - the taxi center.
 * @return - the driver's location.
 */
Node* getDriverLocation(TaxiCenter* taxiCenter){
    int driverId;
    cin >> driverId;
    Node* location = taxiCenter->getDriver(driverId)->getLocation();
    return location;
}
/**
 * assign trips to the drivers and get them to their end point.
 * doing it by moveAll function in TaxiCenter.
 * @param taxiCenter - the taxi center.
 */
void startDriving(TaxiCenter* taxiCenter, Socket* udp){
    taxiCenter->moveAll();
    Node *loc = taxiCenter->getDriver(0)->getLocation();
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << loc;
    s.flush();
    udp->sendData(serial_str);
}
/**
 * the main flow of the taxi center operations.
 * handles the input by switch case for each operation.
 */
int main(int argc, char* argv[]) {
    //crating a grid
    int xSize, ySize, x ,y, mission, driversNum;
    char dummy;
    cin >> xSize >> ySize;
    GridTwoD* grid = new GridTwoD(xSize, ySize);
    grid->buildGrid();
    //adding obstacles to the grid
    int obstaclesNum;
    cin >> obstaclesNum;
    for (int i = 0; i < obstaclesNum; i++) {
        cin >> x >> dummy >> y;
        grid->addObstacle(x, y);
    }
    //creating taxiCenter
    TaxiCenter* taxiCenter = new TaxiCenter(grid);
    //creating a socket
    Socket* udp = new Udp(1, atoi(argv[1]));
    udp->initialize();
    do {
        cin >> mission;
        switch (mission) {
            case 1:
                cin >> driversNum;
                addDriver(taxiCenter, udp);
                break;
            case 2:
                addRide(taxiCenter, grid);
                break;
            case 3:
                addVehicle(taxiCenter);
                break;
            case 4:
                cout << *getDriverLocation(taxiCenter);
                break;
            case 7:
                udp->sendData("-1");
                delete udp;
                delete grid;
                delete taxiCenter;
                break;
            case 9: {
                startDriving(taxiCenter, udp);
                break;
            }
            default:
                return 0;
        }
    } while (mission != 7);

    return 0;
}