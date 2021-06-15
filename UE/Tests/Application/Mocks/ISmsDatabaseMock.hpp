#pragma once

#include <gmock/gmock.h>
#include "Ports/ISmsDatabase.hpp"

namespace ue
{

class ISmsDbMock : public ISmsDb
{
public:
    ISmsDbMock();
    ~ISmsDbMock() override;

    MOCK_METHOD(void, addSms, (const common::PhoneNumber from, const common::PhoneNumber to, const string& text), (final));
    MOCK_METHOD(std::vector<Sms>&, getAllSms, (), (final));
};

}
