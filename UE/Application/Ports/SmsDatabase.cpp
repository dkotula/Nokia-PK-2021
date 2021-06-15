#include "SmsDatabase.hpp"

namespace ue
{
void SmsDb::addSms(const common::PhoneNumber from, const common::PhoneNumber to, const string& text)
{
    Sms newsms = Sms{from, to, text, id++};
    db.push_back(newsms);
}

std::vector<Sms>& SmsDb::getAllSms()
{
    return db;
}

int SmsDb::getSize(){
    return db.size();
}
}
