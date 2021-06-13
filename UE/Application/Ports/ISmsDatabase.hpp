#pragma once

#include "Messages/PhoneNumber.hpp"
#include <vector>
#include "Sms.hpp"

using namespace std;

namespace ue
{
class ISmsDb{
public:
    virtual ~ISmsDb() = default;

    virtual void addSms(const common::PhoneNumber from, const common::PhoneNumber to, const string& text) = 0;
    virtual std::vector<Sms>& getAllSms() = 0;
};

}
