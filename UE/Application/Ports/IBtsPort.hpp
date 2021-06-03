#pragma once

#include "Messages/BtsId.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class IBtsEventsHandler
{
public:
    virtual ~IBtsEventsHandler() = default;

    virtual void handleDisconnected() = 0;
    virtual void handleSib(common::BtsId) = 0;
    virtual void handleAttachAccept() = 0;
    virtual void handleAttachReject() = 0;
    virtual void handleSmsReceived(common::PhoneNumber, std::string) = 0;
    virtual void handleCallAccepted(common::PhoneNumber from) = 0;
    virtual void handleCallRequest(common::PhoneNumber) = 0;
    virtual void handleReceivedCallDrop(common::PhoneNumber) = 0;

};

class IBtsPort
{
public:
    virtual ~IBtsPort() = default;

    virtual void sendAttachRequest(common::BtsId) = 0;
    virtual void sendCallRequest(const common::PhoneNumber to) = 0;
    virtual void sendMessage(const common::PhoneNumber to, const std::string& message) = 0;
    virtual void sendCallAccepted(const common::PhoneNumber from) = 0;
};

}
