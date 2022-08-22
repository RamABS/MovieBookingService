#include <iostream>
#include "../include/BookSeat.h"

CBookSeat::CBookSeat()
{
    cout << "Booking ticket" <<endl;
    m_resource = make_shared<Resource>();
    m_resource->set_path("/bookseat"); 
    m_resource->set_method_handler("POST", [&](const shared_ptr<Session> session){
        return post_resource_handler(session);});    
}

void CBookSeat::api_error(const shared_ptr<Session> session, const std::string &msg)
{
    session->close(restbed::NOT_ACCEPTABLE, msg,
                   {{"Content-Type", "text/plain"},
                    {"Content-Length", std::to_string(msg.size())}});
}

bool CBookSeat::post_parameters(const shared_ptr<Session> &session,
int& movie_id, int& theater_id, list<int>& seat_nos)
{
    auto &request = session->get_request();
    std::size_t length = 0;
    request->get_header("Content-Length", length);
    if (length == 0)
    {
        api_error(session, "Not Acceptable, empty request body");
        return false;
    }

     session->fetch(
        length,
        [&movie_id, &theater_id, &seat_nos](const shared_ptr<Session> session, const restbed::Bytes &data)
        {
            const std::string json_data{reinterpret_cast<const char *>(data.data()),
                                   data.size()};

            json parameter_data = json::parse(json_data);
            json parameters = parameter_data["seat_booking"];
            movie_id = parameters["movieid"].get<int>();
            theater_id = parameters["theaterid"].get<int>();
            seat_nos = parameters["seat_number"].get<list<int>>();

            cout<<movie_id<<endl;
        }
     );
     return true;
}

shared_ptr<Resource> CBookSeat::get_resource() const
{
    return m_resource;
}

void CBookSeat::post_resource_handler(const shared_ptr<Session> session)
{
    cout << "Book Ticket" <<endl;
    int movie_id = 0, theater_id = 0;
    list<int> seat_nos;
    if(post_parameters(session,movie_id,theater_id,seat_nos))    
    {
        auto content = CDatabase::get_instance().book_seat_number(movie_id,theater_id,seat_nos);
        session->close(OK, content, {{"content-length", to_string(content.size())}});
    }
}