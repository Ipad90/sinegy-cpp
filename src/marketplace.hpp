#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>

#include "base64.hpp"

#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <openssl/hmac.h>

const std::string MARKETPLACE_HOST = "https://api.sinegy.com";
const std::string API_VERSION = "/api/v1";

class Marketplace
{
    private:
        std::string api_key;
        std::string secret_key;

        CURL *curl;

        std::chrono::milliseconds timestamp();
        std::string signature(std::string method, std::string path, std::vector<std::pair<std::string, std::string>> &parameters);
        std::string build_query(std::vector<std::pair<std::string, std::string>> parameters, std::string url);

        static size_t curl_call_back(void *contents, size_t size, size_t nmemb, std::string *buffer);

        Json::Value curl_api(std::string method, std::string path, std::vector<std::pair<std::string, std::string>> parameters);

    public:
        Marketplace(std::string api_key, std::string secret_key);

        Json::Value get_currency();
        Json::Value get_currency_pairs();

        Json::Value get_server_time();
        Json::Value get_server_status();

        Json::Value ticker(std::string pair);
        Json::Value get_orderbook(std::string pair);
        Json::Value get_recent_trades(std::string pair, int page = 1, int limit = 250);
        Json::Value get_chart_data(std::string pair, int to_ts, std::string reso);

        Json::Value get_funding_fees(std::string currency);
        Json::Value get_account_information(int recv_window = 5000);
        Json::Value get_account_balance(std::string currency = "", int recv_window = 5000);
        Json::Value get_transactions(std::string currency, int page = 1, int limit = 250, int start_time = 0, int end_time = 0, int recv_window = 5000);
        Json::Value get_deposits(std::string currency, int page = 1, int limit = 250, int start_time = 0, int end_time = 0, int recv_window = 5000);
        Json::Value get_withdrawals(std::string currency, int page = 1, int limit = 250, int start_time = 0, int end_time = 0, int recv_window = 5000);

        Json::Value get_trade_fees(std::string pair);
        Json::Value get_specific_order(std::string pair, std::string transaction_no, int recv_window = 5000);
        Json::Value get_active_orders(std::string pair, int page = 1, int limit = 250, int recv_window = 5000);
        Json::Value get_filled_orders(std::string pair, int page = 1, int limit = 250, int start_time = 0, int end_time = 0, int recv_window = 5000);
        Json::Value get_trades(std::string pair, int page = 1, int limit = 250, int start_time = 0, int end_time = 0, int recv_window = 5000);

        Json::Value place_order(std::string pair, std::string price, std::string volume, int side, int order_type, int time_inforce = 1, int recv_window = 5000);
        Json::Value place_test_order(std::string pair, std::string price, std::string volume, int side, int order_type, int time_inforce = 1, int recv_window = 5000);
        Json::Value cancel_order(std::string pair, std::string order_id, int recv_window = 5000);

        ~Marketplace();
};
