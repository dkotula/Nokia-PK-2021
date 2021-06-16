#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include "Messages/PhoneNumber.hpp"
#include "ISmsDatabase.hpp"

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
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber, ISmsDb& db);
    void start(IUserEventsHandler& handler);
    void stop();

    void showNotConnected() override;
    void showConnecting() override;
    void showConnected() override;
    void setSmsComposeMode() override;
    void showSmsReceived() override;
    void setDialMode() override;
    void showSmsList() override;
    void showSms(const int id) override;
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
    ISmsDb &db;
    bool isUserTalking = false;
};

}
