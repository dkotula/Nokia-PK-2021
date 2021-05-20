#pragma once
#include "Messages/PhoneNumber.hpp"
#include "IUeGui.hpp"



#include "IUeGui.hpp"


namespace ue
{
enum class View {
    Status,
    HomeMenu,
    NewSms,
    SmsList,
    SmsSent,
    SmsReceived,
    SmsView,
    SentSmsView,
    IncomingCall,
    OutgoingCall,
    NewCall,
    Call
};

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
    virtual void showNewSms() = 0;
    virtual void showSmsList() = 0;
    virtual void showMenu() = 0;
    virtual void showSms(int id) = 0;
    virtual void showComposeSmsMode() = 0;
    virtual void showSentSMSList() = 0;
    virtual void showSentSMS(int id) = 0;
    virtual void setCurMode(View curView, IUeGui::BaseMode* mode) = 0;
    virtual void setSmsComposeMode() = 0;
    virtual void showSmsReceived() = 0;
    virtual void setDialMode() = 0;
    virtual void setConversationMode(const common::PhoneNumber from) = 0;
};

}
