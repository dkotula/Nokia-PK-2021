#pragma once
#include <vector>
#include <memory>
#include "SmsForDb/Sms.hpp"
#include "ISmsDbPort.hpp"
namespace ue
{
class SmsDb : public ISmsDb
{
    std::vector<Sms> obiekty;

public:
    SmsDb();
    SmsDb(std::vector<Sms>);
    Sms* get(int id) override;
    std::vector<Sms> getAll() override;
    void remove(int id) override;
    void removeAll() override;
    void insert(Sms sms) override;
    long size() override;
};
}