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
    void handleSmsReceived(const common::PhoneNumber from, const std::string& text) override;
    void handleCallRequest(const common::PhoneNumber from) override;

    void handleSendCallRequest(const common::PhoneNumber to) override;
    void handleCallAccepted(const common::PhoneNumber from) override;
    void handleSendMessage(const common::PhoneNumber to, const std::string& message) override;
    void handleReceivedCallDrop(const common::PhoneNumber recipient) override;
    void handleSendCallAccepted(const common::PhoneNumber from) override;
    void handleSendCallMessage(const common::PhoneNumber to, const std::string &text) override;
    void handleCallTalk(const common::PhoneNumber from, const std::string &message) override;
    void handleSendCallReject(const common::PhoneNumber to) override;
    void handleUnknownRecipient(const common::PhoneNumber to) override;

protected:
    Context& context;
    common::PrefixedLogger logger;
};

}
