#pragma once

#include <memory>
#include <restbed>

using namespace std;
using namespace restbed;

///The resource factory interface
///
///The base interface for the all the resource
class IResourceFactory
{
    public:
    virtual shared_ptr<Resource> get_resource() const = 0;
};