# sinegy-cpp
C++ library for connecting to the [Sinegy API](https://docs.sinegy.com).

## Required libraries
- jsoncpp
- libcurl
- openssl

## Generating API credentials
Go to [INSERT LINK HERE] to generate API credentials.

## Official Sinegy API Documentation
Link to Sinegy's API documentation page is [https://docs.sinegy.com](https://docs.sinegy.com)

## Example
````
#include "marketplace.h"

int main()
{
	string api_key = "API_KEY";
	string secret_key = "SECRET_KEY";

	Json::Value json_result;

	Marketplace::init(api_key, secret_key);

	json_result = Marketplace::ticker("btcmyr");
	cout << json_result << endl;

	return 0;
}
````
