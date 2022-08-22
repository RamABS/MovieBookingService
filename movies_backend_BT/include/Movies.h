#pragma once

#include "IResourceFactory.h"
#include "string.h"
#include <map>
#include <list>
#include <sstream>
#include "json.hpp"
#include "Database.h"

///Movies class to handle the movie list API
///
///The class provide the handler for the API to list all the movies
class CMovies : public IResourceFactory
{
    public:
    CMovies();
    std::shared_ptr<Resource> get_resource() const final;

    private:
    void get_resource_handler(const shared_ptr<Session> session);
    shared_ptr<Resource> m_resource;
};