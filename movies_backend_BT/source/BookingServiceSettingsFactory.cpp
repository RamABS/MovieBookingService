#include "../include/BookingServiceSettingsFactory.h"

CBookingServicesSettingsFactory::CBookingServicesSettingsFactory()
{
    m_settings = make_shared<Settings>();
    m_settings->set_port(3000);
    m_settings->set_default_header("Connection", "close");
    m_settings->set_default_header("Access-Control-Allow-Origin", "*");
}

shared_ptr<Settings> CBookingServicesSettingsFactory::get_settings() const
{
    return m_settings;
}