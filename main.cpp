#include <fstream>
#include <iostream>
#include <boost/network.hpp>

using namespace std;
using namespace boost::network;


std::string build_request(std::string& symbol, std::string& startDateString, std::string& endDateString) {

    int startmonth, startday, startyear;
    if(sscanf(startDateString.c_str(), "%d/%d/%d", &startmonth, &startday, &startyear) != 3) {
        throw new runtime_error("sscanf fail");
    }

    int endmonth, endday, endyear;
    if(sscanf(endDateString.c_str(), "%d/%d/%d", &endmonth, &endday, &endyear) != 3) {
        throw new runtime_error("sscanf fail");
    }
    std::string request = "http://ichart.finance.yahoo.com/table.csv?s=" +
                          symbol +
                          "&d=" + std::to_string(endmonth) +
                          "&e=" + std::to_string(endday) +
                          "&f=" + std::to_string(endyear) +
                          "&g=d" +
                          "&a=" + std::to_string(startmonth) +
                          "&b=" + std::to_string(startday) +
                          "&c=" + std::to_string(startyear) +
                          "&ignore=.csv";
    return request;
}

void write_body(const std::string& filename, const std::string& bodyA) {
    std::ofstream out(filename);
    out << bodyA;
    out.close();
}

int main() {
    std::string symbol = "XOM";
    std::string startdate;
    std::string enddate;
    std::cout << "enter a Yahoo! Finance symbol (example: XOM)\n";
    std::cin >> symbol;
    std::cout << "enter a start date (example: 01/01/2010) \n";
    std::cin >> startdate;
    std::cout << "enter an end date (example: 01/01/2011)\n";
    std::cin >> enddate;
    std::string url = build_request(symbol, startdate, enddate);
    http::client::request request(url);
    request << ::boost::network::header("Connection", "close");
    http::client::options client_options;
    client_options.follow_redirects(true);
    http::client client(client_options);
    http::client::response response = client.get(request);
    int response_code = status(response);
    if(response_code != 200) {
        throw new runtime_error("request failed");
    }
    std::string r =  body(response);
    std::string output_file = symbol + "_table.csv";
    write_body(output_file, r);
    return 0;
}