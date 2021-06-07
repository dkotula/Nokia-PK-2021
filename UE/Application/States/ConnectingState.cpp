#include "ConnectingState.hpp"
#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"


namespace ue
{

ConnectingState::ConnectingState(Context &context, common::BtsId btsId)
    : BaseState(context, "ConnectingState")
{
    context.user.showConnecting();
    context.bts.sendAttachRequest(btsId);
    using namespace std::chrono_literals;
    context.timer.startTimer(500ms);
}

void ConnectingState::handleTimeout()
{
    context.setState<NotConnectedState>();
}

void ConnectingState::handleAttachAccept()
{
    context.timer.stopTimer();
    context.setState<ConnectedState>();
}

void ConnectingState::handleAttachReject()
{
    context.timer.stopTimer();
    context.setState<NotConnectedState>();
}

void ConnectingState::handleDisconnected()
{
    logger.logError("Trying to connect BTS, but BTS is ureachable.");
}


void ConnectingState::handleSib(common::BtsId btsId)
{
    logger.logError("BTS disconnected in connecting state cause: Uexpected handleSib=", btsId);
    context.setState<ConnectingState>(btsId);
}
}


