#pragma once

#include <memory>
#include <restbed>

using namespace std;
using namespace restbed;

///The Service Settings Factory interface
class IServiceSettingsFactory
{
    public:
    virtual shared_ptr<Settings> get_settings() const = 0;

};