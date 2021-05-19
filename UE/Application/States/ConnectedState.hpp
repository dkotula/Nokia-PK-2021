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
    void handleCallRequest(common::PhoneNumber from) final;


    void handleSendMessage(const common::PhoneNumber to, const std::string& message) final;

    void handleReceivedCallDrop(common::PhoneNumber recipient) final;

};

}
