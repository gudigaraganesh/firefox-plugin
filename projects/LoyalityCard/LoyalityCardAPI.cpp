#include "JSObject.h"
#include "DOM/Document.h"
#include "DOM/Window.h"
#include "variant_list.h"
#include "LoyalityCard.h"
#include "ThreadRunnerAPI.h"
#include "swipe.h"

#include "LoyalityCardAPI.h"

LoyalityCardAPI::LoyalityCardAPI(const LoyalityCardPtr& plugin, const FB::BrowserHostPtr& host) : m_host(host), m_pluginWeak(plugin)
{    
    registerMethod(L"swipe_device",  make_method(this, &LoyalityCardAPI::swipe_device));
    registerMethod("testEvent",  make_method(this, &LoyalityCardAPI::testEvent));
    registerMethod("setTimeout",  make_method(this, &LoyalityCardAPI::SetTimeout));
    registerProperty("cardData",
                     make_property(this,
                        &LoyalityCardAPI::get_CardData
                        ));

}

LoyalityCardAPI::~LoyalityCardAPI()
{
    //std::map<int,int>::capacity()
}

LoyalityCardPtr LoyalityCardAPI::getPlugin()
{
    LoyalityCardPtr plugin = m_pluginWeak.lock();
    if (!plugin)
        throw FB::script_error("The plugin object has been destroyed");
    return plugin;
}

std::string LoyalityCardAPI::get_CardData()
{
    return m_CardData;
}


std::string LoyalityCardAPI::swipe_device(long timeout)
{
	char buf[256] = {0};
	int ret = process_swipe_data(buf,timeout);
	//m_CardData<<buf;
	std::string str(buf);
	m_CardData = str;
        return m_CardData;
}





void LoyalityCardAPI::testEvent(const std::string& param)
{
    fire_fired(param);
}


std::string LoyalityCardAPI::asString(const FB::variant& a)
{
    return a.convert_cast<std::string>();
}

bool LoyalityCardAPI::asBool(const FB::variant& a)
{
    return a.convert_cast<bool>();
}

long LoyalityCardAPI::asInt(const FB::variant& a)
{
    return a.convert_cast<long>();
}

double LoyalityCardAPI::asDouble(const FB::variant& a)
{
    return a.convert_cast<double>();
}


std::string LoyalityCardAPI::get_pluginPath()
{
    return getPlugin()->getPluginPath();
}

void LoyalityCardAPI::SetTimeout(const FB::JSObjectPtr& callback, long timeout)
{
    bool recursive = false;
    FB::TimerPtr timer = FB::Timer::getTimer(timeout, recursive, boost::bind(&LoyalityCardAPI::timerCallback, this, callback));
    timer->start();
    //timers.push_back(timer);
}

void LoyalityCardAPI::timerCallback(const FB::JSObjectPtr& callback)
{
    callback->Invoke("", FB::variant_list_of());
    // TODO: delete This timer
}

