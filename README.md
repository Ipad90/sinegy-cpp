# sinegy-cpp
C++ library for connecting to the [Sinegy API](https://docs.sinegy.com).

## Required libraries
- jsoncpp
- libcurl
- openssl

## Generating API credentials
Go to [https://marketplace.sinegy.com/user/profile](https://marketplace.sinegy.com/user/profile) to generate API credentials.

## Official Sinegy API Documentation
Link to Sinegy's API documentation page is [https://docs.sinegy.com](https://docs.sinegy.com)

## Example
````
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
````
