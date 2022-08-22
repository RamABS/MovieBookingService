#pragma once

#include "IResourceFactory.h"
#include "string.h"
#include <map>
#include <list>
#include <sstream>
#include "json.hpp"
#include "Database.h"

///Theaters class to handle the theater list API
///
///The class provide the handler for the API to list all the theaters for the given movie in the parameter
class CTheaters : public IResourceFactory
{
    public:
    CTheaters();
    std::shared_ptr<Resource> get_resource() const final;

    private:
    void api_error(const shared_ptr<Session> session, const std::string &msg);
    bool check_movie_id(const shared_ptr<Session> &session, int &movie_id);
    void get_resource_handler(const shared_ptr<Session> session);
    shared_ptr<Resource> m_resource;
};