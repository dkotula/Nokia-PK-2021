#pragma once

#include <gmock/gmock.h>
#include "Ports/IBtsPort.hpp"

namespace ue
{

class IBtsEventsHandlerMock : public IBtsEventsHandler
{
public:
    IBtsEventsHandlerMock();
    ~IBtsEventsHandlerMock() override;

    MOCK_METHOD(void, handleDisconnected, (), (final));
    MOCK_METHOD(void, handleSib, (common::BtsId), (final));
    MOCK_METHOD(void, handleAttachAccept, (), (final));
    MOCK_METHOD(void, handleAttachReject, (), (final));

    MOCK_METHOD(void, handleCallRequest, (const common::PhoneNumber), (final));
    MOCK_METHOD(void, handleReceivedCallDrop, (const common::PhoneNumber), (final));
    MOCK_METHOD(void, handleSmsReceived, (const common::PhoneNumber from, const std::string &text), (final));
    MOCK_METHOD(void, handleCallAccepted, (const common::PhoneNumber from), (final));
    MOCK_METHOD(void, handleCallTalk, (common::PhoneNumber from, const std::string &message), (final));
    MOCK_METHOD(void, handleUnknownRecipient, (const common::PhoneNumber from), (final));

};

class IBtsPortMock : public IBtsPort
{
public:
    IBtsPortMock();
    ~IBtsPortMock() override;

    MOCK_METHOD(void, sendAttachRequest, (common::BtsId), (final));
    MOCK_METHOD(void, sendCallRequest, (const common::PhoneNumber to), (final));
    MOCK_METHOD(void, sendMessage, (const common::PhoneNumber to, const std::string& message), (final));
    MOCK_METHOD(void, sendCallAccepted, (const common::PhoneNumber from), (final));
    MOCK_METHOD(void, sendCallMessage, (const common::PhoneNumber to, const std::string &text), (final));
    MOCK_METHOD(void, sendCallReject, (const common::PhoneNumber to), (final));
};

}
