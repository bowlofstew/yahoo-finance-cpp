#include <iostream>
#include "reader.hpp"

int main() {
    reader r;
    std::string file;
    std::cout << "specify a flat file\n";
    std::cin >> file;
    table t = r.get_from_file(file);
    for(auto& r : t.rows) {
        std::cout << r.adjusted_close << "\n";
    }
    return 0;
}