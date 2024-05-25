#pragma once

#include <string>

struct Node {
    std::string key;
    std::string value;
    bool isOccupied;

    Node() : key(""), value(""), isOccupied(false) {}
};
