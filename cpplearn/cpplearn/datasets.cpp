#include <curl/curl.h>
#include <string>
#include <iostream>

#include "datasets.hpp"
#include "http_downloader.hpp"
#include "utils.hpp"

namespace cpplearn {
using namespace std;

constexpr char target_url::iris[];

auto datasets::load_iris() -> tuple<mat, vec> {
    mat data;
    vec target;

    http_downloader downloader;
    string content = downloader.download(target_url::iris);
    vector<string> content_list = utils::split(content, '\n');

    for(auto&& line : content_list) {
        if(line == "") continue;
        vector<string> splitted_line = utils::split(line, ',');
        vector<double> tmp;

        for(int i=0; i<splitted_line.size()-1; ++i) tmp.push_back(stoi(splitted_line[i]));
        data.push_back(tmp);

        string label = splitted_line[splitted_line.size()-1];
        if(label == "Iris-setosa") target.push_back(0);
        else if(label == "Iris-versicolor") target.push_back(1);
        else if(label == "Iris-virginica") target.push_back(2);
    }

    cout << "Irist data size: [" << data[0].size() << ", " << data.size() << "]" << endl;
    cout << "Iris target size: " << target.size() << endl;

    return make_tuple(data, target);
}

} // namespace cpplearn
