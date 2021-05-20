#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"
#include "UeGui/IDialMode.hpp"
#include "UeGui/ICallMode.hpp"

namespace ue
{

UserPort::UserPort(common::ILogger &logger, IUeGui &gui, common::PhoneNumber phoneNumber)
    : logger(logger, "[USER-PORT]"),
      gui(gui),
      phoneNumber(phoneNumber)
{}

void UserPort::start(IUserEventsHandler &handler)
{
    this->handler = &handler;
    gui.setTitle("Nokia " + to_string(phoneNumber));
}

void UserPort::stop()
{
    handler = nullptr;
}

void UserPort::showNotConnected()
{
    gui.showNotConnected();
}

void UserPort::showConnecting()
{
    gui.showConnecting();
}

void UserPort::showConnected()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("Compose SMS", "");
    menu.addSelectionListItem("View SMS", "");
    menu.addSelectionListItem("Call", "");
    gui.setAcceptCallback([&](){
        switch (menu.getCurrentItemIndex().second) {
        case 0:
            setSmsComposeMode();
            break;
        case 1:
            //showSmsList();
            break;
        case 2:
            setDialMode();
            break;
        }
    });
}

void UserPort::setSmsComposeMode()
{
    IUeGui::ISmsComposeMode& sms = gui.setSmsComposeMode();
    sms.clearSmsText();
    gui.setAcceptCallback([&](){
        handler->handleSendMessage(sms.getPhoneNumber(), sms.getSmsText());
        showConnected();
        sms.clearSmsText();
    });
}

void UserPort::showSmsReceived()
{
    gui.showNewSms();
}

void UserPort::setDialMode()
{
    IUeGui::IDialMode& dial = gui.setDialMode();
    gui.setAcceptCallback([&](){
        handler->handleSendCallRequest(dial.getPhoneNumber());
    });
}

void UserPort::setConversationMode(const common::PhoneNumber from)
{
    IUeGui::ICallMode& call = gui.setCallMode();
}

}
