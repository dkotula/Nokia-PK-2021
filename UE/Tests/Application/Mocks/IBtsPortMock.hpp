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

    MOCK_METHOD(void, handleCallRequest, (common::PhoneNumber), (final));
    MOCK_METHOD(void, handleReceivedCallDrop, (common::PhoneNumber), (final));
    MOCK_METHOD(void, handleSmsReceived, (common::PhoneNumber from, std::string text), (final));
    MOCK_METHOD(void, handleCallAccepted, (common::PhoneNumber from), (final));
};

class IBtsPortMock : public IBtsPort
{
public:
    IBtsPortMock();
    ~IBtsPortMock() override;

    MOCK_METHOD(void, sendAttachRequest, (common::BtsId), (final));
    MOCK_METHOD(void, sendMessage, (const common::PhoneNumber from, const std::string& message), (final));
    MOCK_METHOD(void, sendCallRequest, (const common::PhoneNumber to), (final));
    MOCK_METHOD(void, sendMessage, (const common::PhoneNumber to, const std::string& message), (final));
};

}
