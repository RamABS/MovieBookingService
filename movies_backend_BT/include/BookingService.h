#pragma once

#include "IService.h"
#include "IResourceFactory.h"
#include "IServiceSettingFactory.h"

///Booking Service class
///
///The class will publish the resources and start the service for usuage
///The class implements the IService interface
class CBookingService : public IService
{
    public:
        /*
        The constructor takes the list of resources which has to published
        */
        CBookingService(const vector<shared_ptr<IResourceFactory>>& rs_factory,         
        shared_ptr<IServiceSettingsFactory> st_factory);

    //Function to start the service
    void start() final;

    private:
        Service m_service;
        shared_ptr<IServiceSettingsFactory> m_settings_factory;
};