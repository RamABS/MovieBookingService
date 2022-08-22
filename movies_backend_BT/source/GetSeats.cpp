#include <iostream>
#include "../include/GetSeats.h"

CAvailableSeats::CAvailableSeats()
{
    cout << "Booking ticket" <<endl;
    m_resource = make_shared<Resource>();
    //m_resource->set_path("/bookseat");
    m_resource->set_path("/availseats/{movieid:[[:digit:]]+}/{theaterid:[[:digit:]]+}");
    m_resource->set_method_handler("GET", [&](const shared_ptr<Session> session){
        return get_resource_handler(session);});   
}

void CAvailableSeats::api_error(const shared_ptr<Session> session, const std::string &msg)
{
    session->close(restbed::NOT_ACCEPTABLE, msg,
                   {{"Content-Type", "text/plain"},
                    {"Content-Length", std::to_string(msg.size())}});
}

bool CAvailableSeats::get_parameters(const shared_ptr<Session> &session,
int& movie_id, int& theater_id)
{
    const auto &request = session->get_request();
    if (request->has_path_parameter("movieid") && request->has_path_parameter("theaterid"))
    {
        movie_id = atoi(request->get_path_parameter("movieid").c_str());
        theater_id = atoi(request->get_path_parameter("theaterid").c_str());
        return true;
    }
    else
    {
        api_error(session, "Not Acceptable, missing id");
    }
    return false;
}

shared_ptr<Resource> CAvailableSeats::get_resource() const
{
    return m_resource;
}

void CAvailableSeats::get_resource_handler(const shared_ptr<Session> session)
{
    cout << "Get Available Tickets" <<endl;
    int movie_id = 0, theater_id = 0;
    if(get_parameters(session,movie_id,theater_id))    
    {
        auto content = CDatabase::get_instance().get_available_seats(movie_id,theater_id);
        session->close(OK, content, {{"content-length", to_string(content.size())}});
    }
}

