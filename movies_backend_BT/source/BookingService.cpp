#include "../include/BookingService.h"

CBookingService::CBookingService(
    const vector<shared_ptr<IResourceFactory>>&  rs_factory,
    shared_ptr<IServiceSettingsFactory> st_factory
)
{
    m_settings_factory = st_factory;
    
    for(const auto& res : rs_factory)
        m_service.publish(res->get_resource());
}

void CBookingService::start()
{
    m_service.start(m_settings_factory->get_settings());
}