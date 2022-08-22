#pragma once

#include "IServiceSettingFactory.h"

///Settings provider for the service
///
///The class which provides the settings like port number for the service to bes hosted
class CBookingServicesSettingsFactory : public IServiceSettingsFactory
{
    public:
        CBookingServicesSettingsFactory();
        shared_ptr<Settings> get_settings() const final;

    private:
        shared_ptr<Settings> m_settings;       
};  