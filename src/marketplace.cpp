#include "marketplace.hpp"

string Marketplace::api_key = "";
string Marketplace::secret_key = "";
CURL* Marketplace::curl = NULL;

void Marketplace::init(string &api_key, string &secret_key)
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
	Marketplace::api_key = api_key;
	Marketplace::secret_key = secret_key;
	Marketplace::curl = curl_easy_init();
}

void Marketplace::cleanup()
{
	curl_easy_cleanup(Marketplace::curl);
	curl_global_cleanup();
}

Json::Value Marketplace::get_currency()
{
	return Marketplace::curl_api("GET", "/api/v1/general/currency", vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_countries(int page, int limit)
{
	string url = "/api/v1/general/countries?";
	vector<std::pair<string, string>> path = {
		{"page", to_string(page)},
		{"limit", to_string(limit)}
	};
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_states(string country_code, int page, int limit)
{
	string url = "/api/v1/general/states?";
	vector<std::pair<string, string>> path = {
		{"countryCode", country_code},
		{"page", to_string(page)},
		{"limit", to_string(limit)},
	};
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_currency_pairs()
{
	return Marketplace::curl_api("GET", "/api/v1/general/currency-pair", vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_sinegy_company_bank_accounts()
{
	return Marketplace::curl_api("GET", "/api/v1/general/sinegy/funding-account", vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_server_time()
{
	return Marketplace::curl_api("GET", "/api/v1/server/time", vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_server_status()
{
	return Marketplace::curl_api("GET", "/api/v1/server/status", vector<std::pair<string, string>>());
}

Json::Value Marketplace::ticker(string pair)
{
	string url = "/api/v1/market/spot/chart/ticker/24hr?";
	vector<std::pair<string, string>> path = {
		{"currencyPair", pair}
	};
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_orderbook(string pair)
{
	string url = "/api/v1/market/spot/orderbook?";
	vector<std::pair<string, string>> path = {
		{"currencyPair", pair}
	};
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_recent_trades(string pair, int page, int limit)
{
	string url = "/api/v1/market/spot/trades?";
	vector<std::pair<string, string>> path = {
		{"currencyPair", pair},
		{"page", to_string(page)},
		{"limit", to_string(limit)},
	};
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_chart_data(string pair, int to_ts, string reso)
{
	string url = "/api/v1/market/spot/chart/klines?";
	vector<std::pair<string, string>> path = {
		{"currencyPair", pair},
		{"reso", reso},
		{"to_ts", to_string(to_ts)}
	};
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_funding_fees(string currency)
{
	string url = "/api/v1/general/fuding/fees?";
	vector<std::pair<string, string>> path = {
		{"currency", currency}
	};
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_funding_status()
{
	return Marketplace::curl_api("GET", "/api/v1/general/fuding/status", vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_funding_types()
{
	return Marketplace::curl_api("GET", "/api/v1/general/funding/types", vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_funding_transfer_types()
{
	return Marketplace::curl_api("GET", "/api/v1/general/funding/transfer-types", vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_funding_payment_types()
{
	return Marketplace::curl_api("GET", "/api/v1/general/funding/payment-types", vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_account_information(int recv_window)
{
	string url = "/api/v1/account/user?";
	vector<std::pair<string, string>> path = {
		{"recvWindow", to_string(recv_window)}
	};
	path.push_back(make_pair("signature", Marketplace::signature("GET", "/api/v1/account", path)));
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_account_balance(string currency, int recv_window)
{
	string url = "/api/v1/account/balance?";
	vector<std::pair<string, string>> path = {
		{"recvWindow", to_string(recv_window)}
	};
	if (currency != "") {
		path.push_back(make_pair("currency", currency));
	}
	path.push_back(make_pair("signature", Marketplace::signature("GET", "/api/v1/account/balance", path)));
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_deposits(string currency, int page, int limit, int start_time, int end_time, int recv_window)
{
	string url = "/api/v1/account/transaction?";
	vector<std::pair<string, string>> path = {
		{"currency", currency},
		{"page", to_string(page)},
		{"limit", to_string(limit)},
		{"recvWindow", to_string(recv_window)}
	};
	if (start_time > 0) {
		path.push_back(make_pair("start_time", to_string(start_time)));
	}
	if (end_time > 0) {
		path.push_back(make_pair("end_time", to_string(end_time)));
	};
	path.push_back(make_pair("signature", Marketplace::signature("GET", "/api/v1/account/transaction", path)));
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_withdrawals(string currency, int page, int limit, int start_time, int end_time, int recv_window)
{
	string url = "/api/v1/account/transaction?";
	vector<std::pair<string, string>> path = {
		{"currency", currency},
		{"page", to_string(page)},
		{"limit", to_string(limit)},
		{"recvWindow", to_string(recv_window)}
	};
	if (start_time > 0) {
		path.push_back(make_pair("start_time", to_string(start_time)));
	}
	if (end_time > 0) {
		path.push_back(make_pair("end_time", to_string(end_time)));
	};
	path.push_back(make_pair("signature", Marketplace::signature("GET", "/api/v1/account/transaction", path)));
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_transactions(string currency, int page, int limit, int start_time, int end_time, int recv_window)
{
	string url = "/api/v1/account/transaction?";
	vector<std::pair<string, string>> path = {
		{"currency", currency},
		{"page", to_string(page)},
		{"limit", to_string(limit)},
		{"recvWindow", to_string(recv_window)}
	};
	if (start_time > 0) {
		path.push_back(make_pair("start_time", to_string(start_time)));
	}
	if (end_time > 0) {
		path.push_back(make_pair("end_time", to_string(end_time)));
	};
	path.push_back(make_pair("signature", Marketplace::signature("GET", "/api/v1/account/transaction", path)));
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_trade_fees(string pair)
{
	string url = "/api/v1/general/trade/fees?";
	vector<std::pair<string, string>> path = {
		{"currencyPair", pair}
	};
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_order_message_types(string pair)
{
	string url = "/api/v1/general/order/message-types?";
	vector<std::pair<string, string>> path = {
		{"currencyPair", pair}
	};
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_order_status(string pair)
{
	string url = "/api/v1/general/order/status?";
	vector<std::pair<string, string>> path = {
		{"currencyPair", pair}
	};
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_order_types(string pair)
{
	string url = "/api/v1/general/order/types?";
	vector<std::pair<string, string>> path = {
		{"currencyPair", pair}
	};
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_order_time_inforce(string pair)
{
	string url = "/api/v1/general/order/time-inforce?";
	vector<std::pair<string, string>> path = {
		{"currencyPair", pair}
	};
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_order_sides(string pair)
{
	string url = "/api/v1/general/order/sides?";
	vector<std::pair<string, string>> path = {
		{"currencyPair", pair}
	};
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_order_flags(string pair)
{
	string url = "/api/v1/general/order/flags?";
	vector<std::pair<string, string>> path = {
		{"currencyPair", pair}
	};
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_specific_order(string pair, string transaction_no, int recv_window)
{
	string result;
	string url = "/api/v1/account/orders/check?";
	vector<std::pair<string, string>> path = {
		{"currencyPair", pair},
		{"transactionNo", transaction_no},
		{"recvWindow", to_string(recv_window)}
	};
	path.push_back(make_pair("signature", Marketplace::signature("GET", "/api/v1/account/orders/check", path)));
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_active_orders(string pair, int page, int limit, int recv_window)
{
	string result;
	string url = "/api/v1/account/orders?";
	vector<std::pair<string, string>> path = {
		{"currencyPair", pair},
		{"page", to_string(page)},
		{"limit", to_string(limit)},
		{"recvWindow", to_string(recv_window)}
	};
	path.push_back(make_pair("signature", Marketplace::signature("GET", "/api/v1/account/orders", path)));
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_filled_orders(string pair, int page, int limit, int start_time, int end_time, int recv_window)
{
	string result;
	string url = "/api/v1/account/orders/history?";
	vector<std::pair<string, string>> path = {
		{"currencyPair", pair},
		{"page", to_string(page)},
		{"limit", to_string(limit)},
		{"recvWindow", to_string(recv_window)}
	};
	if (start_time > 0) {
		path.push_back(make_pair("start_time", to_string(start_time)));
	}
	if (end_time > 0) {
		path.push_back(make_pair("end_time", to_string(end_time)));
	};
	path.push_back(make_pair("signature", Marketplace::signature("GET", "/api/v1/account/orders/history", path)));
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api( "GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::get_trades(string pair, int page, int limit, int start_time, int end_time, int recv_window)
{
	string result;
	string url = "/api/v1/account/orders?";
	vector<std::pair<string, string>> path = {
		{"currencyPair", pair},
		{"page", to_string(page)},
		{"limit", to_string(limit)},
		{"recvWindow", to_string(recv_window)}
	};
	if (start_time > 0) {
		path.push_back(make_pair("start_time", to_string(start_time)));
	}
	if (end_time > 0) {
		path.push_back(make_pair("end_time", to_string(end_time)));
	}
	path.push_back(make_pair("signature", Marketplace::signature("GET", "/api/v1/account/orders", path)));
	url = Marketplace::build_query(path, url);
	return Marketplace::curl_api("GET", url, vector<std::pair<string, string>>());
}

Json::Value Marketplace::place_order(string pair, string price, string volume, int side, int order_type, int time_inforce, int recv_window)
{
	string result;
	string url = "/api/v1/account/orders/place";
	vector<std::pair<string, string>> parameters = {
		{"currencyPair", pair},
		{"unitPrice", price},
		{"volume", volume},
		{"orderSideId", to_string(side)},
		{"orderTypeId", to_string(order_type)},
		{"timeInForce", to_string(time_inforce)},
		{"recvWindow", to_string(recv_window)}
	};
	parameters.push_back(make_pair("signature", Marketplace::signature("POST", url, parameters)));
	return Marketplace::curl_api("POST", url, parameters);
}

Json::Value Marketplace::place_test_order(string pair, string price, string volume, int side, int order_type, int time_inforce, int recv_window)
{
	string result;
	string url = "/api/v1/account/orders/test";
	vector<std::pair<string, string>> parameters = {
		{"currencyPair", pair},
		{"unitPrice", price},
		{"volume", volume},
		{"orderSideId", to_string(side)},
		{"orderTypeId", to_string(order_type)},
		{"timeInForce", to_string(time_inforce)},
		{"recvWindow", to_string(recv_window)}
	};
	parameters.push_back(make_pair("signature", Marketplace::signature("POST", url, parameters)));
	return Marketplace::curl_api("POST", url, parameters);
}

Json::Value Marketplace::cancel_order(string pair, string order_id, int recv_window)
{
	string result;
	string url = "/api/v1/account/orders/cancel";
	vector<std::pair<string, string>> parameters = {
		{"currencyPair", pair},
		{"orderId", order_id},
		{"recvWindow", to_string(recv_window)}
	};
	parameters.push_back(make_pair("signature", Marketplace::signature("DELETE", url, parameters)));
	return Marketplace::curl_api("DELETE", url, parameters);
}

size_t Marketplace::curl_call_back(void *contents, size_t size, size_t nmemb, string *buffer)
{
	buffer->append((char*)contents, size * nmemb);
	return size * nmemb;
}

string Marketplace::signature(string method, string url, vector<std::pair<string, string>> &parameters)
{
	parameters.push_back(make_pair("timestamp", to_string(Marketplace::timestamp().count())));
	string signature = method + "|" + url + "|" + Marketplace::build_query(parameters, "");
	unsigned int md_len;
	unsigned char *str = HMAC(EVP_sha256(),
		Marketplace::secret_key.c_str(),
		strlen(Marketplace::secret_key.c_str()),
		reinterpret_cast<const unsigned char*>(signature.c_str()),
		signature.size(),
		nullptr,
		&md_len
	);
	return base64::to_base64(reinterpret_cast<char*>(str));
}

chrono::milliseconds Marketplace::timestamp()
{
	return chrono::duration_cast<chrono::milliseconds>(
		chrono::system_clock::now().time_since_epoch()
	);
}

string Marketplace::build_query(vector<std::pair<string, string>> parameters, string url)
{
	for (auto it = parameters.begin(); it != parameters.end(); ++it) {
		url += it->first + "=" + it->second;
		if (next(it) != parameters.end()) {
			url += "&";
		}
	}
	return url;
}

Json::Value Marketplace::curl_api(string method, string path, vector<std::pair<string, string>> parameters)
{
	Json::Reader reader;
	Json::Value json_result;
	string result;
	string url(MARKETPLACE_HOST);
	url += path;
	CURLcode res;
	struct curl_slist *headers = NULL;

	headers = curl_slist_append(headers, ("api-key: " + Marketplace::api_key).c_str());
	headers = curl_slist_append(headers, ("User-Agent: Ur mom gay"));
	headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

	string stringed_parameters = Marketplace::build_query(parameters, "");

	if (Marketplace::curl) {
		curl_easy_setopt(Marketplace::curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(Marketplace::curl, CURLOPT_CUSTOMREQUEST, method.c_str());
		curl_easy_setopt(Marketplace::curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(Marketplace::curl, CURLOPT_WRITEDATA, &result);
		curl_easy_setopt(Marketplace::curl, CURLOPT_SSL_VERIFYHOST, false);
		curl_easy_setopt(Marketplace::curl, CURLOPT_SSL_VERIFYPEER, false);

		if (method != "GET") {
			curl_easy_setopt(Marketplace::curl, CURLOPT_POSTFIELDS, stringed_parameters.c_str());
			curl_easy_setopt(Marketplace::curl, CURLOPT_POSTFIELDSIZE, stringed_parameters.length());
		}

		curl_easy_setopt(Marketplace::curl, CURLOPT_WRITEFUNCTION, Marketplace::curl_call_back);
		res = curl_easy_perform(Marketplace::curl);
	}
	reader.parse(result, json_result);
	return json_result;
}