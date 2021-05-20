#pragma once

#include <gmock/gmock.h>
#include "Ports/IUserPort.hpp"

namespace ue
{

class IUserEventsHandlerMock : public IUserEventsHandler
{
public:
    IUserEventsHandlerMock();
    ~IUserEventsHandlerMock() override;
    
    MOCK_METHOD(void, handleSendMessage, (const common::PhoneNumber from, const std::string& message), (final));
    MOCK_METHOD(void, handleSendCallRequest, (const common::PhoneNumber to), (final));
    MOCK_METHOD(void, handleSendMessage, (const common::PhoneNumber to, const std::string& message), (final));

};

class IUserPortMock : public IUserPort
{
public:
    IUserPortMock();
    ~IUserPortMock() override;

    MOCK_METHOD(void, showNotConnected, (), (final));
    MOCK_METHOD(void, showConnecting, (), (final));
    MOCK_METHOD(void, showConnected, (), (final));
    MOCK_METHOD(void, showNewSms, (), (final));
    MOCK_METHOD(void, showSmsList, (), (final));
    MOCK_METHOD(void, showMenu, (), (final));
    MOCK_METHOD(void, showSms, (int),(final));
    MOCK_METHOD(void, showComposeSmsMode,(),(final));
    MOCK_METHOD(void, showSmsReceived,(),(final));
    MOCK_METHOD(void, showSentSMSList,(),(final));
    MOCK_METHOD(void, showSentSMS,(int),(final));
    MOCK_METHOD(void, setCurMode,(View, IUeGui::BaseMode*), (final));
    MOCK_METHOD(void, setSmsComposeMode, (), (final));
    MOCK_METHOD(void, setDialMode, (), (final));
    MOCK_METHOD(void, setConversationMode, (const common::PhoneNumber from), (final));
};

}
