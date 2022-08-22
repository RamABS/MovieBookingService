#pragma once

#include <iostream>
#include <sstream>
#include <map>
#include <list>
#include <set>
#include <string.h>
#include <json.hpp>
#include <boost/thread/shared_mutex.hpp>


using namespace std;
using namespace nlohmann;


struct theater_detail
{
    string theater_name;
    int nTotalSeats;    
    void toJson(json& js)
    {
        js =  json{{"name", theater_name},{"seats", nTotalSeats}};
    }
};

struct movie_detail
{
    string movie_name;
    set<int> theater_list;

    void toJson(json& js) const
    {
        js["name"] = movie_name;
        js["theatres"] = theater_list;
    }
};

///The class is the interface for the database
///
///The class is used to fetch the data from database and provides the interface to access
///Singleton - Single instance which will be used throughout the application
class CDatabase
{
    public:
    static CDatabase& get_instance()
    {
        static CDatabase instance;
        return instance;
    }
    /*
    The function returns all the available movies
    input : NA
    return : JSOn string for the list of movies
    ex:{"movies":[{"movie_id":1,"movie_name":"Movie_1"},{"movie_id":2,"movie_name":"Movie_2"},{"movie_id":3,"movie_name":"Movie_3"}]}
    */
    string get_all_movies();

    /*
    The function returns all the theaters which are running the given movie
    input : Movie ID
    return : JSON string for the list of theater for the given movie
    ex : {"theatres":[{"theater_id":2,"theater_name":"Theater_2"},{"theater_id":8,"theater_name":"Theater_8"}]}
    */
    string get_theatres_by_movie(int movie_id); 

    /*
    The function returns all the available seats for a movie in a given theater
    inputs : Movie ID, Theater ID
    return : Returns the JSON string for the list of available seats
    ex: {"available_seats" : [3, 4, 7]}
    */ 
    string get_available_seats(int movie_id, int theater_id); 

    /*
    The function books/reserves a seat in a theater for a given movies
    inputs : Movie ID, Theater ID, Seat Number
    return : JSON string - status of booking
    FAIL : {"status" : "FAILED"}
    SUCCESS : {"status" : "SUCCESS"}
    */ 
    string book_seat_number(int movie_id, int theater_id, const list<int>& seat_numbers);

    /*
    The function check whether the movie with a given id exist in the database
    input : Movie ID - integer
    return : 
    false : if movie not exist
    true : if movie not exist
    */
    bool is_movie_exist(int movie_id);

    /*
    The function check whether the theater with a given id exist in the database
    input : Theater ID - integer
    return : 
    false : if Theater not exist
    true : if Theater not exist
    */
    bool is_theater_exist(int theater_id);   

    private:
    /*
    Constructor is made private to block instantiation
    */
    CDatabase();
    /*
    Copy operation is blocked
    */
    CDatabase(const CDatabase& copy);
    /*
    assignment operator is blocked
    */
    void operator= (const CDatabase& assign);

    /*
    Internal function to connect the theaters with move
    the function will not be required in realtime
    Just to mock up the data
    */
    void connect_movie_to_theaters(int movie_id, const set<int>& theater_list);
    /*
    Internal function to verify whether the given movie is running the theater
    */
    bool is_movie_running_in_theater(int movie_id, int theater_id);

    map<int, movie_detail> m_map_movies; /*All movies indexed with movie id*/
    map<int, theater_detail> m_map_theaters; /*All theaters indexed with movie id*/
    map<int, map<int, list<int>>> m_movie_bookings; /*All Booking indexed with movie id and theater id*/
    boost::shared_mutex m_shared_mutex;
};