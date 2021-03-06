#pragma once

#include "IBtsPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "ITransport.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class BtsPort : public IBtsPort
{
public:
    BtsPort(common::ILogger& logger, common::ITransport& transport, common::PhoneNumber phoneNumber);
    void start(IBtsEventsHandler& handler);
    void stop();

    void sendAttachRequest(common::BtsId) override;
    void sendCallRequest(const common::PhoneNumber to) override;
    void sendMessage(const common::PhoneNumber to, const std::string& message) override;
    void sendCallAccepted(const common::PhoneNumber from) override;
    void sendCallMessage(const common::PhoneNumber to, const std::string &text) override;
    void sendCallReject(const common::PhoneNumber to) override;

private:
    void handleDisconnected();
    void handleMessage(BinaryMessage msg);

    common::PrefixedLogger logger;
    common::ITransport& transport;
    common::PhoneNumber phoneNumber;

    IBtsEventsHandler* handler = nullptr;
};

}
