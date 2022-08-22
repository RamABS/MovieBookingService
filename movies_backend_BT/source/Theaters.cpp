#include <iostream>
#include "../include/Theaters.h"

CTheaters::CTheaters()
{
    cout << "Theaters Booking Factory" <<endl;
    m_resource = make_shared<Resource>();
    m_resource->set_path("/theaters/{movieid:[[:digit:]]+}");
    //m_resource->set_path("/theaters/{movie_id:[[:digit:]]+}");
    m_resource->set_method_handler("GET", [&](const shared_ptr<Session> session){
        return get_resource_handler(session);
    });    
}

void CTheaters::api_error(const shared_ptr<Session> session, const std::string &msg)
{
    session->close(restbed::NOT_ACCEPTABLE, msg,
                   {{"Content-Type", "text/plain"},
                    {"Content-Length", std::to_string(msg.size())}});
}

bool CTheaters::check_movie_id(const shared_ptr<Session> &session, int &movie_id)
{
    const auto &request = session->get_request();
    if (request->has_path_parameter("movieid"))
    {
        movie_id = atoi(request->get_path_parameter("movieid").c_str());
        if (CDatabase::get_instance().is_movie_exist(movie_id))
            return true; 
        api_error(session, "Not Acceptable, id out of range");
    }
    else
        api_error(session, "Not Acceptable, missing id");

    return false;
}

shared_ptr<Resource> CTheaters::get_resource() const
{
    return m_resource;
}

void CTheaters::get_resource_handler(const shared_ptr<Session> session)
{
    cout << "Theater List" <<endl;
    int movie_id = 0;
    if(check_movie_id(session,movie_id))
    {
        auto content = CDatabase::get_instance().get_theatres_by_movie(movie_id);
        session->close(OK, content, {{"content-length", to_string(content.size())}});
    }
}