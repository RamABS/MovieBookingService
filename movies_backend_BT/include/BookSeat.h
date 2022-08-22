#pragma once

#include "IResourceFactory.h"
#include "string.h"
#include <map>
#include <list>
#include <sstream>
#include "json.hpp"
#include "Database.h"


///The resource class to reserve a seat
///
///The class provides the handler for api to book/reserve a seat from a theater for a given movie
class CBookSeat : public IResourceFactory
{
    public:
    CBookSeat();
    std::shared_ptr<Resource> get_resource() const final;

    private:
    /*
    The error provider
    */
    void api_error(const shared_ptr<Session> session, const std::string &msg);
    /*
    The function will check the api parameters
    input : Session object
    return : returns the true/false based on the validity of the parameters
    On true, it returns Movie ID, Theater ID and Seat No which are received as API parameters
    */
    bool post_parameters(const shared_ptr<Session> &session,int& movie_id, int& theater_id, list<int>& seat_nos);
    /*
    The resource handler for booking ticket for a given theater and movie
    */
    void post_resource_handler(const shared_ptr<Session> session);
    shared_ptr<Resource> m_resource;
};