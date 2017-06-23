#include "utils.hpp"
#include <sstream>
#include <string>
#include <vector>

namespace cpplearn {

using namespace std;

auto utils::split(const string& s, char delimiter) -> vector<string> {
    istringstream stream(s);
    string field;
    vector<string> result;

    while (getline(stream, field, delimiter))
        result.push_back(field);

    return result;
}

} // namespace cpplearn
