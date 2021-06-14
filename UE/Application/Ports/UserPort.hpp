#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{
enum class View
{
    SmsList,
    SmsReceived,
    NewSms
};

class UserPort : public IUserPort
{
public:
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber);
    void start(IUserEventsHandler& handler);
    void stop();

    void showNotConnected() override;
    void showConnecting() override;
    void showConnected() override;
    void setSmsComposeMode() override;
    void showSmsReceived() override;
    void setDialMode() override;
    void setConversationMode(const common::PhoneNumber from) override;
    void setCallRequestMode(const common::PhoneNumber from) override;
    void callTalkMessage(const common::PhoneNumber from, const std::string &text) override;
    bool isTalking() override;
    void showPhonesAreNotPeered(const common::PhoneNumber from) override;



private:
    common::PrefixedLogger logger;
    IUeGui& gui;
    common::PhoneNumber phoneNumber;
    IUserEventsHandler* handler = nullptr;
    bool isUserTalking = false;
};

}
