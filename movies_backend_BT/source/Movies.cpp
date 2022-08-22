#include <iostream>
#include "../include/Movies.h"

CMovies::CMovies()
{
    cout << "Movie Booking Factory" <<endl;
    m_resource = make_shared<Resource>();
    m_resource->set_path("/movies");
    m_resource->set_method_handler("GET", [&](const shared_ptr<Session> session){
        get_resource_handler(session);
    });    
}

shared_ptr<Resource> CMovies::get_resource() const
{
    return m_resource;
}

void CMovies::get_resource_handler(const shared_ptr<Session> session)
{
    cout << "Movie List" <<endl;
    auto content = CDatabase::get_instance().get_all_movies();
    session->close(OK, content, {{"content-length", to_string(content.size())}});
}