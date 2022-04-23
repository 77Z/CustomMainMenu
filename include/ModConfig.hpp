#include "config-utils/shared/config-utils.hpp"
#include <string>

DECLARE_CONFIG(ModConfig,
	CONFIG_VALUE(SoloText, std::string, "Solo Button Text", "SOLO!");
	CONFIG_VALUE(OnlineText, std::string, "Online Button Text", "ONLINE!");
	CONFIG_VALUE(CampaignText, std::string, "Campaign Button Text", "CAMPAIGN!");
	CONFIG_VALUE(PartyText, std::string, "Party Button Text", "PARTY!");
	
	CONFIG_INIT_FUNCTION(
		CONFIG_INIT_VALUE(SoloText);
		CONFIG_INIT_VALUE(OnlineText);
		CONFIG_INIT_VALUE(CampaignText);
		CONFIG_INIT_VALUE(PartyText);
	)
)