#include "marketplace.hpp"

Marketplace::Marketplace(std::string api_key, std::string secret_key)
{
    this->api_key = api_key;
    this->secret_key = secret_key;
    this->curl = curl_easy_init();
}

Json::Value Marketplace::get_currency()
{
    return this->curl_api("GET", "/api/v1/general/currency", std::vector<std::pair<std::string, std::string>>());
}

Json::Value Marketplace::get_currency_pairs()
{
    return this->curl_api("GET", "/api/v1/general/currency-pair", std::vector<std::pair<std::string, std::string>>());
}

Json::Value Marketplace::get_server_time()
{
    return this->curl_api("GET", "/api/v1/server/time", std::vector<std::pair<std::string, std::string>>());
}

Json::Value Marketplace::get_server_status()
{
    return this->curl_api("GET", "/api/v1/server/status", std::vector<std::pair<std::string, std::string>>());
}

Json::Value Marketplace::ticker(std::string pair)
{
    std::string url = "/api/v1/market/spot/chart/ticker/24hr?";

    std::vector<std::pair<std::string, std::string>> path = {
        {"currencyPair", pair}
    };

    url = this->build_query(path, url);

    return this->curl_api("GET", url, std::vector<std::pair<std::string, std::string>>());
}

Json::Value Marketplace::get_orderbook(std::string pair)
{
    std::string url = "/api/v1/market/spot/orderbook?";

    std::vector<std::pair<std::string, std::string>> path = {
        {"currencyPair", pair}
    };
    
    url = this->build_query(path, url);

    return this->curl_api("GET", url, std::vector<std::pair<std::string, std::string>>());
}

Json::Value Marketplace::get_recent_trades(std::string pair, int page, int limit)
{
    std::string url = "/api/v1/market/spot/trades?";

    std::vector<std::pair<std::string, std::string>> path = {
        {"currencyPair", pair},
        {"page", std::to_string(page)},
        {"limit", std::to_string(limit)},
    };

    url = this->build_query(path, url);

    return this->curl_api("GET", url, std::vector<std::pair<std::string, std::string>>());
}

Json::Value Marketplace::get_chart_data(std::string pair, int to_ts, std::string reso)
{
    std::string url = "/api/v1/market/spot/chart/klines?";

    std::vector<std::pair<std::string, std::string>> path = {
        {"currencyPair", pair},
        {"reso", reso},
        {"to_ts", std::to_string(to_ts)}
    };

    url = this->build_query(path, url);

    return this->curl_api("GET", url, std::vector<std::pair<std::string, std::string>>());
}

Json::Value Marketplace::get_funding_fees(std::string currency)
{
    std::string url = "/api/v1/general/fuding/fees?";

    std::vector<std::pair<std::string, std::string>> path = {
        {"currency", currency}
    };

    url = this->build_query(path, url);

    return this->curl_api("GET", url, std::vector<std::pair<std::string, std::string>>());
}

Json::Value Marketplace::get_account_information(int recv_window)
{
    std::string url = "/api/v1/account/user?";

    std::vector<std::pair<std::string, std::string>> path = {
        {"recvWindow", std::to_string(recv_window)}
    };

    path.push_back(make_pair("signature", this->signature("GET", "/api/v1/account", path)));
    url = this->build_query(path, url);

    return this->curl_api("GET", url, std::vector<std::pair<std::string, std::string>>());
}

Json::Value Marketplace::get_account_balance(std::string currency, int recv_window)
{
    std::string url = "/api/v1/account/balance?";

    std::vector<std::pair<std::string, std::string>> path = {
        {"recvWindow", std::to_string(recv_window)}
    };

    if (currency != "") {
        path.push_back(make_pair("currency", currency));
    }

    path.push_back(make_pair("signature", this->signature("GET", "/api/v1/account/balance", path)));
    url = this->build_query(path, url);

    return this->curl_api("GET", url, std::vector<std::pair<std::string, std::string>>());
}

Json::Value Marketplace::get_deposits(std::string currency, int page, int limit, int start_time, int end_time, int recv_window)
{
    std::string url = "/api/v1/account/transaction?";

    std::vector<std::pair<std::string, std::string>> path = {
        {"currency", currency},
        {"page", std::to_string(page)},
        {"limit", std::to_string(limit)},
        {"recvWindow", std::to_string(recv_window)}
    };

    if (start_time > 0) {
        path.push_back(make_pair("start_time", std::to_string(start_time)));
    }

    if (end_time > 0) {
        path.push_back(make_pair("end_time", std::to_string(end_time)));
    }

    path.push_back(make_pair("signature", this->signature("GET", "/api/v1/account/transaction", path)));
    url = this->build_query(path, url);

    return this->curl_api("GET", url, std::vector<std::pair<std::string, std::string>>());
}

Json::Value Marketplace::get_withdrawals(std::string currency, int page, int limit, int start_time, int end_time, int recv_window)
{
    std::string url = "/api/v1/account/transaction?";
    std::vector<std::pair<std::string, std::string>> path = {
        {"currency", currency},
        {"page", std::to_string(page)},
        {"limit", std::to_string(limit)},
        {"recvWindow", std::to_string(recv_window)}
    };

    if (start_time > 0) {
        path.push_back(make_pair("start_time", std::to_string(start_time)));
    }

    if (end_time > 0) {
        path.push_back(make_pair("end_time", std::to_string(end_time)));
    }

    path.push_back(make_pair("signature", this->signature("GET", "/api/v1/account/transaction", path)));
    url = this->build_query(path, url);

    return this->curl_api("GET", url, std::vector<std::pair<std::string, std::string>>());
}

Json::Value Marketplace::get_transactions(std::string currency, int page, int limit, int start_time, int end_time, int recv_window)
{
    std::string url = "/api/v1/account/transaction?";

    std::vector<std::pair<std::string, std::string>> path = {
        {"currency", currency},
        {"page", std::to_string(page)},
        {"limit", std::to_string(limit)},
        {"recvWindow", std::to_string(recv_window)}
    };

    if (start_time > 0) {
        path.push_back(make_pair("start_time", std::to_string(start_time)));
    }

    if (end_time > 0) {
        path.push_back(make_pair("end_time", std::to_string(end_time)));
    }

    path.push_back(make_pair("signature", this->signature("GET", "/api/v1/account/transaction", path)));
    url = this->build_query(path, url);

    return this->curl_api("GET", url, std::vector<std::pair<std::string, std::string>>());
}

Json::Value Marketplace::get_trade_fees(std::string pair)
{
    std::string url = "/api/v1/general/trade/fees?";

    std::vector<std::pair<std::string, std::string>> path = {
        {"currencyPair", pair}
    };

    url = this->build_query(path, url);

    return this->curl_api("GET", url, std::vector<std::pair<std::string, std::string>>());
}

Json::Value Marketplace::get_specific_order(std::string pair, std::string transaction_no, int recv_window)
{
    std::string result;
    std::string url = "/api/v1/account/orders/check?";

    std::vector<std::pair<std::string, std::string>> path = {
        {"currencyPair", pair},
        {"transactionNo", transaction_no},
        {"recvWindow", std::to_string(recv_window)}
    };

    path.push_back(make_pair("signature", this->signature("GET", "/api/v1/account/orders/check", path)));
    url = this->build_query(path, url);

    return this->curl_api("GET", url, std::vector<std::pair<std::string, std::string>>());
}

Json::Value Marketplace::get_active_orders(std::string pair, int page, int limit, int recv_window)
{
    std::string result;
    std::string url = "/api/v1/account/orders?";

    std::vector<std::pair<std::string, std::string>> path = {
        {"currencyPair", pair},
        {"page", std::to_string(page)},
        {"limit", std::to_string(limit)},
        {"recvWindow", std::to_string(recv_window)}
    };

    path.push_back(make_pair("signature", this->signature("GET", "/api/v1/account/orders", path)));
    url = this->build_query(path, url);

    return this->curl_api("GET", url, std::vector<std::pair<std::string, std::string>>());
}

Json::Value Marketplace::get_filled_orders(std::string pair, int page, int limit, int start_time, int end_time, int recv_window)
{
    std::string result;
    std::string url = "/api/v1/account/orders/history?";

    std::vector<std::pair<std::string, std::string>> path = {
        {"currencyPair", pair},
        {"page", std::to_string(page)},
        {"limit", std::to_string(limit)},
        {"recvWindow", std::to_string(recv_window)}
    };

    if (start_time > 0) {
        path.push_back(make_pair("start_time", std::to_string(start_time)));
    }

    if (end_time > 0) {
        path.push_back(make_pair("end_time", std::to_string(end_time)));
    }

    path.push_back(make_pair("signature", this->signature("GET", "/api/v1/account/orders/history", path)));
    url = this->build_query(path, url);

    return this->curl_api("GET", url, std::vector<std::pair<std::string, std::string>>());
}

Json::Value Marketplace::get_trades(std::string pair, int page, int limit, int start_time, int end_time, int recv_window)
{
    std::string result;
    std::string url = "/api/v1/account/orders?";

    std::vector<std::pair<std::string, std::string>> path = {
        {"currencyPair", pair},
        {"page", std::to_string(page)},
        {"limit", std::to_string(limit)},
        {"recvWindow", std::to_string(recv_window)}
    };

    if (start_time > 0) {
        path.push_back(make_pair("start_time", std::to_string(start_time)));
    }

    if (end_time > 0) {
        path.push_back(make_pair("end_time", std::to_string(end_time)));
    }

    path.push_back(make_pair("signature", this->signature("GET", "/api/v1/account/orders", path)));
    url = this->build_query(path, url);

    return this->curl_api("GET", url, std::vector<std::pair<std::string, std::string>>());
}

Json::Value Marketplace::place_order(std::string pair, std::string price, std::string volume, int side, int order_type, int time_inforce, int recv_window)
{
    std::string result;
    std::string url = "/api/v1/account/orders/place";

    std::vector<std::pair<std::string, std::string>> parameters = {
        {"currencyPair", pair},
        {"unitPrice", price},
        {"volume", volume},
        {"orderSideId", std::to_string(side)},
        {"orderTypeId", std::to_string(order_type)},
        {"timeInForce", std::to_string(time_inforce)},
        {"recvWindow", std::to_string(recv_window)}
    };
    parameters.push_back(make_pair("signature", this->signature("POST", url, parameters)));

    return this->curl_api("POST", url, parameters);
}

Json::Value Marketplace::place_test_order(std::string pair, std::string price, std::string volume, int side, int order_type, int time_inforce, int recv_window)
{
    std::string result;
    std::string url = "/api/v1/account/orders/test";

    std::vector<std::pair<std::string, std::string>> parameters = {
        {"currencyPair", pair},
        {"unitPrice", price},
        {"volume", volume},
        {"orderSideId", std::to_string(side)},
        {"orderTypeId", std::to_string(order_type)},
        {"timeInForce", std::to_string(time_inforce)},
        {"recvWindow", std::to_string(recv_window)}
    };
    parameters.push_back(make_pair("signature", this->signature("POST", url, parameters)));

    return this->curl_api("POST", url, parameters);
}

Json::Value Marketplace::cancel_order(std::string pair, std::string order_id, int recv_window)
{
    std::string result;
    std::string url = "/api/v1/account/orders/cancel";

    std::vector<std::pair<std::string, std::string>> parameters = {
        {"currencyPair", pair},
        {"orderId", order_id},
        {"recvWindow", std::to_string(recv_window)}
    };
    parameters.push_back(make_pair("signature", this->signature("DELETE", url, parameters)));

    return this->curl_api("DELETE", url, parameters);
}

std::chrono::milliseconds Marketplace::timestamp()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}

std::string Marketplace::signature(std::string method, std::string url, std::vector<std::pair<std::string, std::string>> &parameters)
{
    parameters.push_back(make_pair("timestamp", std::to_string(this->timestamp().count())));

    std::string signature = method + "|" + url + "|" + this->build_query(parameters, "");

    unsigned int md_len;
    unsigned char *str = HMAC(EVP_sha256(),
        this->secret_key.c_str(),
        strlen(this->secret_key.c_str()),
        reinterpret_cast<const unsigned char *>(signature.c_str()),
        signature.size(),
        nullptr,
        &md_len
    );

    return base64::to_base64(reinterpret_cast<char *>(str));
}

std::string Marketplace::build_query(std::vector<std::pair<std::string, std::string>> parameters, std::string url)
{
    for (auto it = parameters.begin(); it != parameters.end(); ++it) {
        url += it->first + "=" + it->second;
        if (next(it) != parameters.end()) {
            url += "&";
        }
    }

    return url;
}

size_t Marketplace::curl_call_back(void *contents, size_t size, size_t nmemb, std::string *buffer)
{
    buffer->append((char *)contents, size * nmemb);

    return size * nmemb;
}

Json::Value Marketplace::curl_api(std::string method, std::string path, std::vector<std::pair<std::string, std::string>> parameters)
{
    Json::CharReaderBuilder builder;
    Json::CharReader *reader = builder.newCharReader();
    Json::Value json_result;

    std::string result;
    std::string error;

    std::string url = MARKETPLACE_HOST + path;

    CURLcode res;
    struct curl_slist *headers = NULL;

    headers = curl_slist_append(headers, ("api-key: " + this->api_key).c_str());
    headers = curl_slist_append(headers, ("User-Agent: Ur mom gay"));
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

    std::string stringed_parameters = this->build_query(parameters, "");

    if (this->curl) {
        curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, method.c_str());
        curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &result);
        curl_easy_setopt(this->curl, CURLOPT_SSL_VERIFYHOST, false);
        curl_easy_setopt(this->curl, CURLOPT_SSL_VERIFYPEER, false);

        if (method != "GET") {
            curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, stringed_parameters.c_str());
            curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE, stringed_parameters.length());
        }

        curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, this->curl_call_back);
        res = curl_easy_perform(this->curl);
    }

    reader->parse(result.c_str(), result.c_str() + result.length(), &json_result, &error);

    return json_result;
}

Marketplace::~Marketplace()
{
    curl_easy_cleanup(this->curl);
    curl_global_cleanup();
}
