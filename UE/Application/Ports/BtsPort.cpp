#include "BtsPort.hpp"
#include "Messages/IncomingMessage.hpp"
#include "Messages/OutgoingMessage.hpp"

namespace ue
{

BtsPort::BtsPort(common::ILogger &logger, common::ITransport &transport, common::PhoneNumber phoneNumber)
    : logger(logger, "[BTS-PORT]"),
      transport(transport),
      phoneNumber(phoneNumber)
{}

void BtsPort::start(IBtsEventsHandler &handler)
{
    transport.registerMessageCallback([this](BinaryMessage msg) {handleMessage(msg);});
    transport.registerDisconnectedCallback([this]() {handleDisconnected();});
    this->handler = &handler;
}

void BtsPort::stop()
{
    transport.registerMessageCallback(nullptr);
    transport.registerDisconnectedCallback(nullptr);
    handler = nullptr;
}

void BtsPort::handleDisconnected()
{
    handler->handleDisconnected();
}

void BtsPort::handleMessage(BinaryMessage msg)
{
    try
    {
        common::IncomingMessage reader{msg};
        auto msgId = reader.readMessageId();
        auto from = reader.readPhoneNumber();
        auto to = reader.readPhoneNumber();

        switch (msgId)
        {
        case common::MessageId::Sib:
        {
            auto btsId = reader.readBtsId();
            handler->handleSib(btsId);
            break;
        }
        case common::MessageId::AttachResponse:
        {
            bool accept = reader.readNumber<std::uint8_t>() != 0u;
            if (accept)
                handler->handleAttachAccept();
            else
                handler->handleAttachReject();
            break;
        }
        case common::MessageId::Sms:
        {
            std::string message = reader.readRemainingText();
            logger.logDebug("BtsPort, SmsReceived from: ", from);
            logger.logDebug("BtsPort, SmsReceived message: ", message);
            handler->handleSmsReceived(from, message);
            break;
        }
        case common::MessageId::CallAccepted:
        {
            logger.logDebug("BtsPort, CallAccepted from: ", from);
            handler->handleCallAccepted(from);
            break;
        }
        case common::MessageId::CallRequest:
        {
            logger.logDebug("BtsPort, CallRequest from: ", from);
            if (from == to) {
                handler->handleReceivedCallDrop(from);
            }
            else {
                handler->handleCallRequest(from);
            }
            break;
        }
        case common::MessageId::CallDropped:
        {
            logger.logDebug("Call dropped from: ", from);
            handler->handleReceivedCallDrop(from);
            break;
        }
        case common::MessageId::CallTalk:
        {
            std::string message = reader.readRemainingText();
            logger.logDebug("BtsPort, CallTalk from: ", from);
            logger.logDebug("BtsPort, CallTalk message: ", message);
            handler->handleCallTalk(from, message);
            break;
        }
        case common::MessageId::UnknownRecipient:
        {
            logger.logDebug("Unknown recipient : ", from);
            handler->handleUnknownRecipient(from);
            break;
        }
        default:
            logger.logError("unknow message: ", msgId, ", from: ", from);

        }
    }
    catch (std::exception const& ex)
    {
        logger.logError("handleMessage error: ", ex.what());
    }
}


void BtsPort::sendAttachRequest(common::BtsId btsId)
{
    logger.logDebug("sendAttachRequest: ", btsId);
    common::OutgoingMessage msg{common::MessageId::AttachRequest,
                                phoneNumber,
                                common::PhoneNumber{}};
    msg.writeBtsId(btsId);
    transport.sendMessage(msg.getMessage());


}

void BtsPort::sendMessage(const common::PhoneNumber to, const std::string& message)
{
    logger.logDebug("sendMessage: ", to);
    common::OutgoingMessage msg{common::MessageId::Sms,
                                phoneNumber,
                                to};
    msg.writeText(message);
    transport.sendMessage(msg.getMessage());
}

void BtsPort::sendCallRequest(const common::PhoneNumber to)
{
    logger.logDebug("sendCallRequest: ", to);
    common::OutgoingMessage msg{common::MessageId::CallRequest,
                                phoneNumber,
                                to};
    transport.sendMessage(msg.getMessage());
}

void BtsPort::sendCallAccepted(const common::PhoneNumber from)
{
    logger.logDebug("sendCallAccepted: ", from);
    common::OutgoingMessage msg{common::MessageId::CallAccepted,
                                phoneNumber,
                                from};
    transport.sendMessage(msg.getMessage());
}

void BtsPort::sendCallMessage(const common::PhoneNumber to, const std::string &text)
{
    logger.logDebug("sendCallMessage: ", to);
    common::OutgoingMessage msg{common::MessageId::CallTalk,
                                phoneNumber,
                                to};
    msg.writeText(text);
    transport.sendMessage(msg.getMessage());
}

void BtsPort::sendCallReject(const common::PhoneNumber to)
{
    logger.logDebug("sendCallReject: ", to);
    common::OutgoingMessage msg{common::MessageId::CallDropped,
                                phoneNumber,
                                to};
    transport.sendMessage(msg.getMessage());
}

}
