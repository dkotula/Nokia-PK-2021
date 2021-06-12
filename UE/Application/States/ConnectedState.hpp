#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);

    // IBtsEventsHandler interface
public:
    void handleDisconnected() final;

    void handleSmsReceived(common::PhoneNumber phoneNumber, std::string msg) final;
    void handleCallRequest(common::PhoneNumber from);
    void handleReceivedCallDrop(const common::PhoneNumber recipient) final;
    void handleSendMessage(const common::PhoneNumber to, const std::string& message) final;
    void handleSendCallRequest(const common::PhoneNumber to) final;
    void handleCallAccepted(const common::PhoneNumber from) final;
    void handleSendCallAccepted(const common::PhoneNumber from) final;
    void handleSendCallMessage(const common::PhoneNumber to, const std::string &text) final;
    void handleCallTalk(const common::PhoneNumber from, const std::string &message) final;
    void handleSendCallReject(const common::PhoneNumber to) final;
    void handleUnknownRecipient(const common::PhoneNumber from) final;
    void handleTimeout() final;
private:
    PhoneNumber participant;
};

}
