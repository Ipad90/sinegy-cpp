#ifndef MARKETPLACE_H
#define MARKETPLACE_H

#include <chrono>
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>

#include "base64.hpp"

#include <curl/curl.h>
#include <json/json.h>
#include <openssl/hmac.h>

#define MARKETPLACE_HOST "http://54.169.183.250"
#define API_VERSION "/api/v1"

using namespace std;

class Marketplace
{
	static string api_key;
	static string secret_key;
	static CURL* curl;

	public:
		static void init(string &api_key, string &secret_key);
		static void cleanup();

		static Json::Value get_currency();
		static Json::Value get_countries(int page = 1, int limit = 250);
		static Json::Value get_states(string country_code, int page = 1, int limit = 250);
		static Json::Value get_currency_pairs();
		static Json::Value get_sinegy_company_bank_accounts();

		static Json::Value get_server_time();
		static Json::Value get_server_status();

		static Json::Value ticker(string pair);
		static Json::Value get_orderbook(string pair);
		static Json::Value get_recent_trades(string pair, int page = 1, int limit = 250);
		static Json::Value get_chart_data(string pair, int to_ts, string reso);

		static Json::Value get_funding_fees(string currency);
		static Json::Value get_funding_status();
		static Json::Value get_funding_types();
		static Json::Value get_funding_transfer_types();
		static Json::Value get_funding_payment_types();

		static Json::Value get_account_information(int recv_window = 5000);
		static Json::Value get_account_balance(string currency = "", int recv_window = 5000);
		static Json::Value get_transactions(string currency, int page = 1, int limit = 250, int start_time = 0, int end_time = 0, int recv_window = 5000);
		static Json::Value get_deposits(string currency, int page = 1, int limit = 250, int start_time = 0, int end_time = 0, int recv_window = 5000);
		static Json::Value get_withdrawals(string currency, int page = 1, int limit = 250, int start_time = 0, int end_time = 0, int recv_window = 5000);

		static Json::Value get_trade_fees(string pair);
		static Json::Value get_order_message_types(string pair);
		static Json::Value get_order_status(string pair);
		static Json::Value get_order_types(string pair);
		static Json::Value get_order_time_inforce(string pair);
		static Json::Value get_order_sides(string pair);
		static Json::Value get_order_flags(string pair);

		static Json::Value get_specific_order(string pair, string transaction_no, int recv_window = 5000);
		static Json::Value get_active_orders(string pair, int page = 1, int limit = 250, int recv_window = 5000);
		static Json::Value get_filled_orders(string pair, int page = 1, int limit = 250, int start_time = 0, int end_time = 0, int recv_window = 5000);
		static Json::Value get_trades(string pair, int page = 1, int limit = 250, int start_time = 0, int end_time = 0, int recv_window = 5000);

		static Json::Value place_order(string pair, string price, string volume, int side, int order_type, int time_inforce = 1, int recv_window = 5000);
		static Json::Value place_test_order(string pair, string price, string volume, int side, int order_type, int time_inforce = 1, int recv_window = 5000);
		static Json::Value cancel_order(string pair, string order_id, int recv_window = 5000);

	private:
		static string build_query(vector<pair<string, string>> parameters, string url);
		static string signature(string method, string path, vector<pair<string, string>> &parameters);
		static chrono::milliseconds timestamp();
		static size_t curl_call_back(void *contents, size_t size, size_t nmemb, string *buffer);
		static Json::Value curl_api(string method, string path, vector<pair<string, string>> parameters);
};

#endif
