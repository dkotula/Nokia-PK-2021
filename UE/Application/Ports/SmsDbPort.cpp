#include "SmsDbPort.hpp"
#include "SmsForDb/Sms.hpp"
#include <memory>
namespace ue
{
SmsDb::SmsDb(){}
SmsDb::SmsDb(std::vector<Sms> smsList):obiekty(smsList){}
Sms* SmsDb::get(int id)
{
    try
    {
        return &obiekty.at(id);
    }
    catch (const std::out_of_range& oor)
    {
        throw(oor);
    }

}
std::vector<Sms> SmsDb::getAll()
{
    return obiekty;
}

void SmsDb::remove(int id)
{
    obiekty.erase(obiekty.begin() + id);
        for(int i=id;i<this->size();i++)
        {
            obiekty.at(i).messageId--;
        }
}
void SmsDb::removeAll()
{
    obiekty.clear();
}
void SmsDb::insert(Sms sms)
{
    sms.messageId=obiekty.size();
    obiekty.push_back(sms);
}
long SmsDb::size()
{
    return obiekty.size();
}
}