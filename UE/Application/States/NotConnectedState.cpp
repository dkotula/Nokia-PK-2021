#include "NotConnectedState.hpp"
#include "ConnectingState.hpp"

namespace ue
{

NotConnectedState::NotConnectedState(Context &context)
    : BaseState(context, "NotConnectedState")
{
    context.user.showNotConnected();
}

void NotConnectedState::handleSib(common::BtsId btsId)
{
    context.setState<ConnectingState>(btsId);
}

void NotConnectedState::handleDisconnected()
{
    logger.logError("Trying to connect BTS, but BTS is unreachable.");
    context.user.showRetryAttach();
}

}


