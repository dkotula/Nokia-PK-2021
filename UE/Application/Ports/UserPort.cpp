#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"
#include "UeGui/IDialMode.hpp"
#include "UeGui/ICallMode.hpp"
#include "UeGui/ITextMode.hpp"

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
    gui.setRejectCallback([](){});
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
    gui.setRejectCallback([&](){
        sms.clearSmsText();
        showConnected();
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
        IUeGui::ITextMode& call = gui.setAlertMode();
        call.setText("Calling to " + to_string(dial.getPhoneNumber()));

        handler->handleSendCallRequest(dial.getPhoneNumber());
        gui.setRejectCallback([&, to = dial.getPhoneNumber()](){
            handler->handleSendCallReject(to);
            showConnected();
        });
    });
    gui.setRejectCallback([&](){
        showConnected();
    });
}

void UserPort::setConversationMode(const common::PhoneNumber from)
{
    IUeGui::ICallMode& call = gui.setCallMode();
    call.clearOutgoingText();
    gui.setAcceptCallback([&, from](){
        handler->handleSendCallMessage(from, call.getOutgoingText());
        call.clearOutgoingText();
    });

    gui.setRejectCallback([&, from](){
        handler->handleSendCallReject(from);
        call.clearOutgoingText();
        showConnected();
    });
}

void UserPort::setCallRequestMode(const common::PhoneNumber from)
{
    IUeGui::ITextMode& call = gui.setAlertMode();
    call.setText(to_string(from) + " is calling");

    gui.setAcceptCallback([&, from](){
        handler->handleSendCallAccepted(from);
        setConversationMode(from);

    });
    gui.setRejectCallback([&, from](){
        handler->handleSendCallReject(from);
        showConnected();

    });
}

void UserPort::callTalkMessage(const common::PhoneNumber from, const std::string &text)
{
    gui.setCallMode().appendIncomingText(text);
}

void UserPort::setCallDropped(const common::PhoneNumber recipient)
{
    showConnected();
}
void UserPort::showPhonesAreNotPeered(const common::PhoneNumber from)
{
    gui.showPeerUserNotAvailable(from);
}

}
