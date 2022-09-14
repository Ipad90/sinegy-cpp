#include "src/marketplace.hpp"

int main(void)
{
	std::string api_key = "API_KEY";
	std::string secret_key = "SECRET_KEY";

	Json::Value json_result;

	Marketplace SinegyMarketplace = Marketplace(api_key, secret_key);

	json_result = SinegyMarketplace.ticker("btcmyr");
	std::cout << json_result << std::endl;

	return 0;
}
