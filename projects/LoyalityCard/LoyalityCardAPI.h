#include <string>
#include <sstream>
#include "Timer.h"
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "FBPointers.h"

FB_FORWARD_PTR(ThreadRunnerAPI);
FB_FORWARD_PTR(SimpleMathAPI);
FB_FORWARD_PTR(LoyalityCard);

class LoyalityCardAPI : public FB::JSAPIAuto
{
public:
    LoyalityCardAPI(const LoyalityCardPtr& plugin, const FB::BrowserHostPtr& host);
    virtual ~LoyalityCardAPI();

    FB_JSAPI_EVENT(fired, 1, (const std::string));

    LoyalityCardPtr getPlugin();
    
    ThreadRunnerAPIPtr createThreadRunner();

    std::string get_CardData();
    std::string swipe_device(long timeout);

    FB::variant echo(const FB::variant& a);

    std::string asString(const FB::variant& a);
    bool asBool(const FB::variant& a);
    long asInt(const FB::variant& a);
    double asDouble(const FB::variant& a);

    void testEvent(const std::string& param);
      std::string get_pluginPath();
	void SetTimeout(const FB::JSObjectPtr& callback, long timeout);
	void timerCallback(const FB::JSObjectPtr& callback);
private:
    FB::BrowserHostPtr m_host;
    SimpleMathAPIPtr m_simpleMath;
    LoyalityCardWeakPtr m_pluginWeak;
    std::string m_CardData;
};

