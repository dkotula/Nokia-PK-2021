#pragma once

#include "Messages/PhoneNumber.hpp"

using namespace std;

struct Sms{
    common::PhoneNumber from{};
    common::PhoneNumber to{};
    string text;
    bool read = false;
};
