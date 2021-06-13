#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    context.user.showConnected();
}

void ConnectedState::handleDisconnected()
{
    context.setState<NotConnectedState>();
}


void ConnectedState::handleSmsReceived(common::PhoneNumber from,
                                       std::string text)
{
    //Sms incomingSms(from,text);
    //incomingSms.read = false;
    //context.db.insert(incomingSms);
    context.user.showSmsReceived();
}
void ConnectedState::handleSendMessage(const common::PhoneNumber to, const std::string& message)
{
    //Sms incomingSms(from,text);
    //incomingSms.read = false;
    //context.db.insert(incomingSms);
    context.bts.sendMessage(to, message);
}

void ConnectedState::handleCallRequest(common::PhoneNumber from)
{
    context.user.setCallRequestMode(from);
}

void ConnectedState::handleReceivedCallDrop(const common::PhoneNumber recipient)
{
    context.user.setCallDropped(recipient);
}

void ConnectedState::handleSendCallRequest(const common::PhoneNumber to)
{
    context.bts.sendCallRequest(to);
}

void ConnectedState::handleCallAccepted(const common::PhoneNumber from)
{
    context.user.setConversationMode(from);
}

void ConnectedState::handleSendCallAccepted(const common::PhoneNumber from)
{
    context.bts.sendCallAccepted(from);
}

void ConnectedState::handleSendCallMessage(const common::PhoneNumber to, const std::string &text)
{
    context.bts.sendCallMessage(to, text);
}

void ConnectedState::handleCallTalk(const common::PhoneNumber from, const std::string &message)
{
    context.user.callTalkMessage(from, message);
}

void ConnectedState::handleSendCallReject(const common::PhoneNumber to)
{
    context.bts.sendCallReject(to);
}
void ConnectedState::handlePhonesAreNotPeered(const common::PhoneNumber from)
{
    context.user.showPhonesAreNotPeered(from);
}
}
