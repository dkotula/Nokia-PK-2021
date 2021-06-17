#pragma once

#include "Messages/PhoneNumber.hpp"

using namespace std;

enum smstype{
    rread,
    unread,
    unknown_recipient,
    sent
};

struct Sms{
    common::PhoneNumber from{};
    common::PhoneNumber to{};
    string text;
    int id = 0;
    smstype type = unread;
};
