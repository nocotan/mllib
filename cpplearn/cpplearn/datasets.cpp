#include <curl/curl.h>
#include <string>
#include <iostream>

#include "datasets.hpp"
#include "http_downloader.hpp"
#include "utils.hpp"

namespace cpplearn {
using namespace std;

constexpr char target_url::iris[];

auto datasets::load_iris() -> tuple<matf64, vecf64> {
    matf64 data;
    vecf64 target;

    http_downloader downloader;
    string content = downloader.download(target_url::iris);
    vector<string> content_list = utils::split(content, '\n');

    for(auto&& line : content_list) {
        if(line == "") continue;
        vector<string> splitted_line = utils::split(line, ',');
        vector<double> tmp;

        for(int i=0; i<splitted_line.size()-1; ++i)
            tmp.push_back(stof(splitted_line[i]));

        data.push_back(tmp);

        string label = splitted_line[splitted_line.size()-1];
        if(label == "Iris-setosa") target.push_back(0);
        else if(label == "Iris-versicolor") target.push_back(1);
        else if(label == "Iris-virginica") target.push_back(2);
    }

    cout << "Iris data size: [" << data[0].size() << ", " << data.size() << "]" << endl;
    cout << "Iris target size: " << target.size() << endl;

    return make_tuple(data, target);
}

auto datasets::load_wine() -> tuple<matf64, vecf64> {
    matf64 data;
    vecf64 target;

    http_downloader downloader;
    string content = downloader.download(target_url::wine);
    vector<string> content_list = utils::split(content, '\n');

    for(auto&& line : content_list) {
        if(line == "") continue;
        vector<string> splitted_line = utils::split(line, ',');
        vector<double> tmp;

        for(int i=1; i<splitted_line.size(); ++i)
            tmp.push_back(stof(splitted_line[i]));

        data.push_back(tmp);
        target.push_back(stoi(splitted_line[0]));
    }

    cout << "Wine data size: [" << data[0].size() << ", " << data.size() << "]" << endl;
    cout << "Wine target size: " << target.size() << endl;
}

} // namespace cpplearn
