#pragma once

#include "Logger/PrefixedLogger.hpp"
#include "Messages/PhoneNumber.hpp"
#include "IEventsHandler.hpp"
#include "Context.hpp"

namespace ue
{

using common::PhoneNumber;
using common::ILogger;

class Application : public IEventsHandler
{
public:
    Application(PhoneNumber phoneNumber,
                ILogger& iLogger,
                IBtsPort& bts,
                IUserPort& user,
                ITimerPort& timer,
                ISmsDb& db,
                ISmsDb& db_w);
    ~Application();

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleDisconnected() override;
    void handleSmsReceived(common::PhoneNumber PhoneNumber, std::string msg) override;
    void handleSib(common::BtsId btsId) override;
    void handleSendCallRequest(const common::PhoneNumber) override;
    void handleCallAccepted(const common::PhoneNumber from) override;
    void handleCallRequest(common::PhoneNumber from) override;
    void handleReceivedCallDrop(common::PhoneNumber PhoneNumber) override;
    void handleSendMessage(const common::PhoneNumber to, const std::string& message) override;

private:
    Context context;
    common::PrefixedLogger logger;

};

}
