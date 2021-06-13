#pragma once

#include "Messages/PhoneNumber.hpp"
#include "Sms.hpp"
#include "ISmsDatabase.hpp"
#include <vector>

namespace ue
{

class SmsDb : public ISmsDb
{
public:
    void addSms(const common::PhoneNumber from, const common::PhoneNumber to, const string& text) override;
    std::vector<Sms>& getAllSms() override;
private:
    std::vector<Sms> db;
};

}
