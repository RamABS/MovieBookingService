#include <iostream>
#include "../include/Movies.h"
#include "../include/Theaters.h"
#include "../include/GetSeats.h"
#include "../include/BookSeat.h"
#include "../include/BookingServiceSettingsFactory.h"
#include "../include/BookingService.h"

using namespace std;

int main(int argc, char** argv)
{
    vector<shared_ptr<IResourceFactory>> res_factory;
    res_factory.push_back(make_shared<CMovies>());
    res_factory.push_back(make_shared<CTheaters>());
    res_factory.push_back(make_shared<CAvailableSeats>());
    res_factory.push_back(make_shared<CBookSeat>());
    auto set_factory = make_shared<CBookingServicesSettingsFactory>();
    CBookingService bookingService(res_factory, set_factory);

    cout << "Movie Booking API - Started" << endl;
    bookingService.start();

    return 0;
}
