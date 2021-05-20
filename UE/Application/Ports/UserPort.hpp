#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include "Messages/PhoneNumber.hpp"
#include "ISmsDbPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"

namespace ue
{
enum class View
{
    SmsList,
    SmsReceived
};

class UserPort : public IUserPort
{
public:
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber, ISmsDb& db, ISmsDb& db_w);
    constexpr static unsigned ListSmsItem = 1;
    constexpr static unsigned NewSmsItem = 0;
    std::pair<View, IUeGui::BaseMode*> getCurMode()
    {
        return std::pair(view, curMode);
    }
    void setCurMode(View curView, IUeGui::BaseMode* mode)
    {
        view = curView;
        curMode = mode;
    }
    void start(IUserEventsHandler& handler);
    void stop();

    void showNotConnected() override;
    void showConnecting() override;
    void showConnected() override;
    void showNewSms() override;
    void showSmsReceived() override;
    void showSmsList() override;
    void showMenu() override;
    void showSms(int id) override;
    void showComposeSmsMode() override;
    void showSentSMSList() override;
    void showSentSMS(int id) override;
    void setSmsComposeMode() override;
    void showSmsReceived() override;
    void setDialMode() override;
    void setConversationMode(const common::PhoneNumber from) override;

private:
    common::PrefixedLogger logger;
    IUeGui& gui;
    common::PhoneNumber phoneNumber;
    IUserEventsHandler* handler = nullptr;
    IUeGui::BaseMode* curMode;
    void handleHomeClicked();
    void handleAcceptClicked();
    void handleRejectClicked();
    View view;
    ISmsDb& db;
    ISmsDb& db_w;
    int test=0;
};

}
