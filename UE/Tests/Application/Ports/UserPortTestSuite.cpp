#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Ports/UserPort.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/IUserPortMock.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Mocks/IUeGuiMock.hpp"

namespace ue
{
using namespace ::testing;

class UserPortTestSuite : public Test
{
protected:
    const common::PhoneNumber PHONE_NUMBER{112};
    const common::PhoneNumber PHONE_NUMBER_RECIPIENT{113};
    NiceMock<common::ILoggerMock> loggerMock;
    StrictMock<IUserEventsHandlerMock> handlerMock;
    StrictMock<IUeGuiMock> guiMock;
    StrictMock<IListViewModeMock> listViewModeMock;
    StrictMock<ISmsComposeModeMock> smsComposeModeMock;
    StrictMock<IDialModeMock> dialModeMock;
    StrictMock<ICallModeMock> callModeMock;

    UserPort objectUnderTest{loggerMock, guiMock, PHONE_NUMBER};

    UserPortTestSuite()
    {
        EXPECT_CALL(guiMock, setTitle(HasSubstr(to_string(PHONE_NUMBER))));
        objectUnderTest.start(handlerMock);
    }
    ~UserPortTestSuite()
    {
        objectUnderTest.stop();
    }
};

TEST_F(UserPortTestSuite, shallStartStop)
{
}

TEST_F(UserPortTestSuite, shallShowNotConnected)
{
    EXPECT_CALL(guiMock, showNotConnected());
    objectUnderTest.showNotConnected();
}

TEST_F(UserPortTestSuite, shallShowConnecting)
{
    EXPECT_CALL(guiMock, showConnecting());
    objectUnderTest.showConnecting();
}

TEST_F(UserPortTestSuite, shallShowMenuOnConnected)
{
    std::function<void()> callback;
    EXPECT_CALL(guiMock, setListViewMode()).WillOnce(ReturnRef(listViewModeMock));
    EXPECT_CALL(guiMock, setAcceptCallback).WillOnce(SaveArg<0>(&callback));
    EXPECT_CALL(guiMock, setRejectCallback).WillOnce(SaveArg<0>(&callback));
    EXPECT_CALL(listViewModeMock, clearSelectionList());
    EXPECT_CALL(listViewModeMock, addSelectionListItem(_, _)).Times(AtLeast(1));
    objectUnderTest.showConnected();

}

TEST_F(UserPortTestSuite, shallShowComposeMode)
{
    std::function<void()> callback;
    EXPECT_CALL(guiMock, setSmsComposeMode()).WillOnce(ReturnRef(smsComposeModeMock));
    EXPECT_CALL(smsComposeModeMock, clearSmsText());
    EXPECT_CALL(guiMock, setAcceptCallback).WillOnce(SaveArg<0>(&callback));
    EXPECT_CALL(guiMock, setRejectCallback).WillOnce(SaveArg<0>(&callback));
    objectUnderTest.setSmsComposeMode();
}

TEST_F(UserPortTestSuite, shallShowDialMode)
{
    std::function<void()> callback;
    EXPECT_CALL(guiMock, setDialMode()).WillOnce(ReturnRef(dialModeMock));
    EXPECT_CALL(guiMock, setAcceptCallback).WillOnce(SaveArg<0>(&callback));
    EXPECT_CALL(guiMock, setRejectCallback).WillOnce(SaveArg<0>(&callback));
    objectUnderTest.setDialMode();
}

TEST_F(UserPortTestSuite, shallShowCallMode)
{
    std::function<void()> callback;
    EXPECT_CALL(guiMock, setCallMode()).WillOnce(ReturnRef(callModeMock));
    EXPECT_CALL(callModeMock, clearOutgoingText());
    EXPECT_CALL(callModeMock, clearIncomingText());
    EXPECT_CALL(guiMock, setAcceptCallback).WillOnce(SaveArg<0>(&callback));
    EXPECT_CALL(guiMock, setRejectCallback).WillOnce(SaveArg<0>(&callback));
    objectUnderTest.setConversationMode(PHONE_NUMBER_RECIPIENT);
}

}
