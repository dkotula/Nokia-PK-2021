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
                ITimerPort& timer);
    ~Application();

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleDisconnected() override;
    void handleSmsReceived(common::PhoneNumber PhoneNumber, std::string msg) override;
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleSendMessage(common::PhoneNumber from, std::string message) override;
    void handleCallRequest(common::PhoneNumber from) override;
    void handleReceivedCallDrop(common::PhoneNumber PhoneNumber) override;


private:
    Context context;
    common::PrefixedLogger logger;

};

}
