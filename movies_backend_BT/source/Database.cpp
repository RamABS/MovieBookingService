#include "../include/Database.h"

CDatabase::CDatabase()
{
    for(int i = 1; i <= 20; ++i)
    {
        string name("Theater_");
        name += to_string(i);
        m_map_theaters[i] = {name, 20};
    }

    for(int i = 1; i <= 20; ++i)
    {
        string name("Movie_");
        name += to_string(i);
        m_map_movies[i] = {name};
    }

    connect_movie_to_theaters(1, {1, 7, 14});
    connect_movie_to_theaters(2, {2, 8, 15});
    connect_movie_to_theaters(3, {3, 9, 16});
    connect_movie_to_theaters(4, {4, 10, 17});
    connect_movie_to_theaters(5, {5, 11, 18});
    connect_movie_to_theaters(6, {6, 12, 19});
    connect_movie_to_theaters(7, {7, 13, 20});
    connect_movie_to_theaters(8, {8, 14});
    connect_movie_to_theaters(9, {9, 15});
    connect_movie_to_theaters(10, {10, 16});
    connect_movie_to_theaters(11, {11, 17});
    connect_movie_to_theaters(12, {12, 18});
    connect_movie_to_theaters(13, {13, 19});
    connect_movie_to_theaters(14, {14, 20});
    connect_movie_to_theaters(15, {15, 1});
    connect_movie_to_theaters(16, {16, 2});
    connect_movie_to_theaters(17, {17, 3});
    connect_movie_to_theaters(18, {18, 4});
    connect_movie_to_theaters(19, {19, 5});
    connect_movie_to_theaters(20, {20, 6});
}

void CDatabase::connect_movie_to_theaters(int movie_id, const set<int>& theater_list)
{
    set<int>& the_list = m_map_movies[movie_id].theater_list;
    std::copy(theater_list.begin(), theater_list.end(), std::inserter(the_list, the_list.begin()) );
    for(auto theater : the_list)
    {
        list<int> avail_seats(20);
        std::iota(avail_seats.begin(), avail_seats.end(), 1);

        m_movie_bookings[movie_id][theater] = avail_seats;
    } 
}

string CDatabase::get_all_movies()
{
    list<json> js_main;
    for(auto const& elem : m_map_movies)
    {   
        json js;
        js["movie_id"] = elem.first;     
        js["movie_name"] = elem.second.movie_name;
        js_main.push_back(js);
    }

    json js_out;
    js_out["movies"] = js_main;
    return js_out.dump();
}

bool CDatabase::is_movie_exist(int movie_id)
{
    return (m_map_movies.find(movie_id) != m_map_movies.end());
}

string CDatabase::get_theatres_by_movie(int movie_id)
{
    list<json> js_main;
    for(auto const& theater : m_map_movies[movie_id].theater_list)
    {
        json js;
        js["theater_id"] = theater;
        js["theater_name"] = m_map_theaters[theater].theater_name;
        js_main.push_back(js);
    }

    json js_out;
    js_out["theatres"] = js_main;
    return js_out.dump();
}

bool CDatabase::is_theater_exist(int theater_id)
{
    return (m_map_theaters.find(theater_id) != m_map_theaters.end());
}

bool CDatabase::is_movie_running_in_theater(int movie_id, int theater_id)
{
    if(is_movie_exist(movie_id) && is_theater_exist(theater_id))
    {
        return (m_movie_bookings[movie_id].find(theater_id) != m_movie_bookings[movie_id].end());
    }
    return false;
}

string CDatabase::get_available_seats(int movie_id, int theater_id)
{
    boost::shared_lock<boost::shared_mutex> readlock(m_shared_mutex); 
    json js_main;    
    js_main["available_seats"] = m_movie_bookings[movie_id][theater_id];
    return js_main.dump();
}

string CDatabase::book_seat_number(int movie_id, int theater_id, const list<int>& seat_numbers)
{
    json js;
    cout<<"book seat number"<<endl;
    boost::upgrade_lock<boost::shared_mutex> upgradeLock(m_shared_mutex);    
    if(is_movie_running_in_theater(movie_id, theater_id))
    {
        cout<<"Movie Running"<<endl;
        boost::upgrade_to_unique_lock<boost::shared_mutex> writeLock(upgradeLock);
        cout<<"Aquired lock"<<endl;
        int nSize = m_movie_bookings[movie_id][theater_id].size();

        for(auto seat : seat_numbers)
        {
            m_movie_bookings[movie_id][theater_id].remove(seat);
            cout <<"Removed_seat :"<<seat<<endl;
        }

        if(nSize != m_movie_bookings[movie_id][theater_id].size())
        {
            js["status"] = "BOOKED";
            return js.dump();
        }
    }
    js["status"] = "FAILED";
    return js.dump();
}
