#pragma once
#include <gmock/gmock.h>
#include "Ports/ISmsDbPort.hpp"
#include "SmsForDb/Sms.hpp"
namespace ue
{


class ISmsDbMock : public ISmsDb
{
public:
    ISmsDbMock();
    ~ISmsDbMock() override;
    MOCK_METHOD(Sms*, get, (int), (final));
    MOCK_METHOD(std::vector<Sms>, getAll, (), (final));
    MOCK_METHOD(void, remove, (int), (final));
    MOCK_METHOD(void, removeAll, (), (final));
    MOCK_METHOD(void, insert, (Sms), (final));
    MOCK_METHOD(long, size, (), (final));
};

}