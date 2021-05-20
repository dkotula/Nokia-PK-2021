#include "Sms.hpp"

namespace ue
{

Sms::Sms()
    {

    }

Sms::Sms(PhoneNumber from, std::string text) : Sms()
    {
        this->from=from;
        this->message=text;
    }
}
