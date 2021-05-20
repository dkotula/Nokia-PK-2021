#pragma once

#include "IEventsHandler.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Context.hpp"
#include "Messages/PhoneNumber.hpp"
namespace ue
{

class BaseState : public IEventsHandler
{
public:
    BaseState(Context& context, const std::string& name);
    ~BaseState() override;

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleDisconnected() override;
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleSmsReceived(common::PhoneNumber from, std::string text) override;
    void handleCallRequest(common::PhoneNumber from) override;
    void handleSendCallRequest(const common::PhoneNumber to) override;
    void handleCallAccepted(const common::PhoneNumber from) override;
    void handleSendMessage(const common::PhoneNumber to, const std::string& message) override;
    void handleReceivedCallDrop(common::PhoneNumber recipient) override;

protected:
    Context& context;
    common::PrefixedLogger logger;
};

}
