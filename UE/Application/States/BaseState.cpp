#include "BaseState.hpp"

namespace ue
{

BaseState::BaseState(Context &context, const std::string &name)
    : context(context),
      logger(context.logger, "[" + name + "]")
{
    logger.logDebug("entry");
}

BaseState::~BaseState()
{
    logger.logDebug("exit");
}

void BaseState::handleTimeout()
{
    logger.logError("Uexpected: handleTimeout");
}

void BaseState::handleDisconnected()
{
    logger.logError("Uexpected: handleDisconnected");
}

void BaseState::handleSib(common::BtsId btsId)
{
    logger.logError("Uexpected: handleSib: ", btsId);
}

void BaseState::handleAttachAccept()
{
    logger.logError("Uexpected: handleAttachAccept");
}

void BaseState::handleAttachReject()
{
    logger.logError("Uexpected: handleAttachReject");
}


void BaseState::handleSmsReceived(common::PhoneNumber from, std::string text)
{
    logger.logError("Unexpected handleSmsReceived: ", from, text);
}

void BaseState::handleSendMessage(const common::PhoneNumber to, const std::string& message)
{
    logger.logError("Uexpected: handleSendMessage");
}

void BaseState::handleSendCallRequest(const common::PhoneNumber to)
{
    logger.logError("Uexpected: handleSendCallRequest");
}

void BaseState::handleCallAccepted(const common::PhoneNumber from)
{
    logger.logError("Uexpected: handleCallAccepted");
}

void BaseState::handleCallRequest(common::PhoneNumber from)
{
    logger.logDebug("Unexpected: handleCallRequest");
}

void BaseState::handleReceivedCallDrop(common::PhoneNumber from)
{
    logger.logError("Unexpected ReceivedCallDrop: ", from);
}

}
