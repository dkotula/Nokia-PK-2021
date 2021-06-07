#pragma once

#include "BaseState.hpp"
#include <functional>

namespace ue
{

class ConnectingState : public BaseState
{
public:
    ConnectingState(Context& context, common::BtsId btsId);

    // ITimerEventsHandler interface
public:
    void handleTimeout() final;

    // IBtsEventsHandler interface
public:
    void handleAttachAccept() final;
    void handleAttachReject() final;
    void handleDisconnected() override;
    void handleSib(common::BtsId btsId) final;
};

}
