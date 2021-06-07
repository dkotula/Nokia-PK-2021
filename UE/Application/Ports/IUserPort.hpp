#pragma once
#include "Messages/PhoneNumber.hpp"
#include "IUeGui.hpp"




namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;
    virtual void handleSendCallRequest(const common::PhoneNumber to) = 0;
    virtual void handleSendMessage(const common::PhoneNumber to, const std::string& message) = 0;
};

class IUserPort
{
public:
    virtual ~IUserPort() = default;

    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;
    virtual void setSmsComposeMode() = 0;
    virtual void showSmsReceived() = 0;
    virtual void setDialMode() = 0;
    virtual void setConversationMode(const common::PhoneNumber from) = 0;
    virtual void showRetryAttach() = 0;
};

}
