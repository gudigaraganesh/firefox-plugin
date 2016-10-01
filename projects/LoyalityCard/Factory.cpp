
#include "FactoryBase.h"
#include "LoyalityCard.h"
#include <boost/make_shared.hpp>

class PluginFactory : public FB::FactoryBase
{
public:
    FB::PluginCorePtr createPlugin(const std::string& mimetype)
    {
            return boost::make_shared<LoyalityCard>(mimetype);
    }
    
    void globalPluginInitialize()
    {
        LoyalityCard::StaticInitialize();
    }
    
    void globalPluginDeinitialize()
    {
        LoyalityCard::StaticDeinitialize();
    }
};

FB::FactoryBasePtr getFactoryInstance()
{
    static boost::shared_ptr<PluginFactory> factory = boost::make_shared<PluginFactory>();
    return factory;
}

