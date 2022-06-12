//
// Created by 黎明余光 on 2022/6/12.
//

#ifndef CPP_TERM_PROJECT_CONFIG_H
#define CPP_TERM_PROJECT_CONFIG_H

#include <string>

class Config {
public:
    int id;
    std::string key;
    std::string value;

    Config();
    Config(std::string key, std::string value);
};


#endif //CPP_TERM_PROJECT_CONFIG_H
