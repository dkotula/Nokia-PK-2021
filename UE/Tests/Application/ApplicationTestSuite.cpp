#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Application.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/IBtsPortMock.hpp"
#include "Mocks/IUserPortMock.hpp"
#include "Mocks/ITimerPortMock.hpp"
#include "Mocks/ISmsDatabaseMock.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Messages/BtsId.hpp"
#include <memory>

namespace ue
{
using namespace ::testing;
using namespace std::chrono_literals;

class ApplicationTestSuite : public Test
{
protected:
    const common::BtsId BTS_ID{42};
    const common::PhoneNumber PHONE_NUMBER{112};
    const common::PhoneNumber PHONE_NUMBER_RECIPIENT{113};
    const std::chrono::milliseconds MINUTE{60s};
    NiceMock<common::ILoggerMock> loggerMock;
    StrictMock<IBtsPortMock> btsPortMock;
    StrictMock<IUserPortMock> userPortMock;
    StrictMock<ITimerPortMock> timerPortMock;
    StrictMock<ISmsDbMock> dbMock;

    Expectation expectShowNotConnected = EXPECT_CALL(userPortMock, showNotConnected());
    Application objectUnderTest{PHONE_NUMBER,
                                loggerMock,
                                btsPortMock,
                                userPortMock,
                                timerPortMock,
                                dbMock};
};

struct ApplicationNotConnectedTestSuite : ApplicationTestSuite
{};

struct ApplicationConnectingTestSuite : ApplicationNotConnectedTestSuite
{
    ApplicationConnectingTestSuite();
    void doConnecting();
};

ApplicationConnectingTestSuite::ApplicationConnectingTestSuite()
{
    doConnecting();
}

void ApplicationConnectingTestSuite::doConnecting()
{
    EXPECT_CALL(userPortMock, showConnecting());
    EXPECT_CALL(btsPortMock, sendAttachRequest(BTS_ID));
    EXPECT_CALL(timerPortMock, startTimer(500ms));
    objectUnderTest.handleSib(BTS_ID);
}

TEST_F(ApplicationNotConnectedTestSuite, shallSendAttachRequestOnSib)
{
    // everything in constructor
}

TEST_F(ApplicationConnectingTestSuite, shallShowNotConnectedOnAttachReject)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    EXPECT_CALL(timerPortMock, stopTimer());
    objectUnderTest.handleAttachReject();
}

TEST_F(ApplicationConnectingTestSuite, shallShowNotConnectedOnAttachTimeout)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    objectUnderTest.handleTimeout();
}

struct ApplicationConnectedTestSuite : ApplicationConnectingTestSuite
{
    ApplicationConnectedTestSuite();
    void doConnected();
};

ApplicationConnectedTestSuite::ApplicationConnectedTestSuite()
{
    doConnected();
}

void ApplicationConnectedTestSuite::doConnected()
{
    EXPECT_CALL(userPortMock, showConnected());
    EXPECT_CALL(timerPortMock, stopTimer());
    objectUnderTest.handleAttachAccept();
}

TEST_F(ApplicationConnectedTestSuite, shallShowConnectedOnAttachAccept)
{
    // see test-suite constructor
}

TEST_F(ApplicationConnectedTestSuite, shallShowNotConnectedOnDisconnectFromBts)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    objectUnderTest.handleDisconnected();
}

TEST_F(ApplicationConnectedTestSuite, shallReattach)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    objectUnderTest.handleDisconnected();

    doConnecting();
    doConnected();
}

TEST_F(ApplicationConnectedTestSuite, shallSendMessageAndAddToDatabase)
{
    EXPECT_CALL(dbMock, addSms(_, PHONE_NUMBER_RECIPIENT, "Wiadomość"));
    EXPECT_CALL(btsPortMock, sendMessage(PHONE_NUMBER_RECIPIENT, "Wiadomość"));
    EXPECT_CALL(dbMock, setType(sent));
    objectUnderTest.handleSendMessage(PHONE_NUMBER_RECIPIENT, "Wiadomość");
}

TEST_F(ApplicationConnectedTestSuite, shallSendCallRequestAndStartTimer)
{
    EXPECT_CALL(timerPortMock, startTimer(MINUTE));
    EXPECT_CALL(btsPortMock, sendCallRequest(PHONE_NUMBER_RECIPIENT));
    objectUnderTest.handleSendCallRequest(PHONE_NUMBER_RECIPIENT);
}

TEST_F(ApplicationConnectedTestSuite, shallSendCallReject)
{
    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(btsPortMock, sendCallReject(PHONE_NUMBER_RECIPIENT));
    objectUnderTest.handleSendCallReject(PHONE_NUMBER_RECIPIENT);
}

TEST_F(ApplicationConnectedTestSuite, shallSendCallAccepted)
{
    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(timerPortMock, startTimer(2 * MINUTE));
    EXPECT_CALL(btsPortMock, sendCallAccepted(PHONE_NUMBER_RECIPIENT));
    objectUnderTest.handleSendCallAccepted(PHONE_NUMBER_RECIPIENT);
}

TEST_F(ApplicationConnectedTestSuite, shallSetConversationMode)
{
    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(timerPortMock, startTimer(2 * MINUTE));
    EXPECT_CALL(userPortMock, setConversationMode(PHONE_NUMBER_RECIPIENT));
    objectUnderTest.handleCallAccepted(PHONE_NUMBER_RECIPIENT);
}

TEST_F(ApplicationConnectedTestSuite, shallSendCallMessage)
{
    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(timerPortMock, startTimer(2 * MINUTE));
    EXPECT_CALL(btsPortMock, sendCallMessage(PHONE_NUMBER_RECIPIENT, "Wiadomość"));
    objectUnderTest.handleSendCallMessage(PHONE_NUMBER_RECIPIENT, "Wiadomość");
}
TEST_F(ApplicationConnectedTestSuite, shallCallRequest)
{
    EXPECT_CALL(userPortMock, isTalking());
    EXPECT_CALL(timerPortMock, startTimer(MINUTE/2));
    EXPECT_CALL(userPortMock, setCallRequestMode(PHONE_NUMBER_RECIPIENT));
    objectUnderTest.handleCallRequest(PHONE_NUMBER_RECIPIENT);
}

}
