#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"

using namespace std::chrono_literals;

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


void ConnectedState::handleSmsReceived(const common::PhoneNumber from, const std::string& text)

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

void ConnectedState::handleCallRequest( const common::PhoneNumber from)
{
    participant = from;
    context.timer.startTimer(30s);
    context.user.setCallRequestMode(from);
}

void ConnectedState::handleReceivedCallDrop(const common::PhoneNumber recipient)
{
    context.timer.stopTimer();
    context.user.setCallDropped(recipient);
}

void ConnectedState::handleSendCallRequest(const common::PhoneNumber to)
{
    participant = to;
    context.timer.startTimer(60s);
    context.bts.sendCallRequest(to);
}

void ConnectedState::handleCallAccepted(const common::PhoneNumber from)
{
    context.timer.stopTimer();
    context.timer.startTimer(120s);
    context.user.setConversationMode(from);
}

void ConnectedState::handleSendCallAccepted(const common::PhoneNumber from)
{
    context.timer.stopTimer();
    context.timer.startTimer(120s);
    context.bts.sendCallAccepted(from);
}

void ConnectedState::handleSendCallMessage(const common::PhoneNumber to, const std::string &text)
{
    context.timer.stopTimer();
    context.timer.startTimer(120s);
    context.bts.sendCallMessage(to, text);
}

void ConnectedState::handleCallTalk(const common::PhoneNumber from, const std::string &message)
{
    context.timer.stopTimer();
    context.timer.startTimer(120s);
    context.user.callTalkMessage(from, message);
}

void ConnectedState::handleSendCallReject(const common::PhoneNumber to)
{
    context.timer.stopTimer();
    context.bts.sendCallReject(to);
}

void ConnectedState::handleUnknownRecipient(const common::PhoneNumber from)
{
    if (context.user.isTalking()) {
        context.timer.stopTimer();
        context.user.setUnknownRecipientTalking();
    }
    else {
        //context.db.setUnknownRecipient(from);
    }
}

void ConnectedState::handleTimeout()
{
    context.user.showConnected();
    context.bts.sendCallReject(participant);
}

}
