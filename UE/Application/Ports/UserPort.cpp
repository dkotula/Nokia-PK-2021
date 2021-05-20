#include "UserPort.hpp"
#include "SmsDbPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ITextMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"
#include "UeGui/IDialMode.hpp"
#include "UeGui/ICallMode.hpp"

namespace ue
{

UserPort::UserPort(common::ILogger &logger, IUeGui &gui, common::PhoneNumber phoneNumber, ISmsDb &db, ISmsDb &db_w)
    : logger(logger, "[USER-PORT]"),
      gui(gui),
      phoneNumber(phoneNumber),
      curMode(nullptr),
      view(View::Status),
      db(db),
      db_w(db_w)
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

void UserPort::showNewSms()
{
    gui.showNewSms();
}

void UserPort::showConnected()
{
    gui.showConnected();
    showMenu();
}

void UserPort::showSmsReceived()
{
//    TODO
}

void UserPort::handleRejectClicked()
{
    switch(view) {
    case View::HomeMenu:
        break;
    case View::SmsList:
        showMenu();
        break;
    case View::SmsView:
        showSmsList();
        break;
    case View::NewSms:
        showMenu();
        break;
    case View::SentSmsView:
        showMenu();;
        break;
    }

}

void UserPort::showNotConnected()
{
    view = View::Status;
    gui.showNotConnected();
}

void UserPort::showConnecting()
{
    view = View::Status;
    gui.showConnecting();
}

void UserPort::showSmsList()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    std::vector<Sms> smsList=db.getAll();
    if(db.size()==0) menu.addSelectionListItem("no messages","");
    else
    {
        for(Sms sms : smsList)
        {
            menu.addSelectionListItem(to_string(sms.from)+(sms.read==false?"\tNew":""),sms.message);
        }
        gui.setAcceptCallback([&](){
            showSms(menu.getCurrentItemIndex().second);
        });
    }
    //setCurMode(View::SmsList,&menu);
}

void UserPort::showSms(int id)
{
    IUeGui::ITextMode& menu = gui.setViewTextMode();
    Sms* sms = db.get(id);
    std::string text="From: "+to_string(sms->from)+"\n\n"+sms->message;
    menu.setText(text);
    sms->read=true;
    bool allRead=true;
    for(Sms sms : db.getAll())
        if(sms.read==false){allRead=false;break;}
    //if(allRead==true)showSmsReceived();
    //setCurMode(View::SmsView, &menu);
}

void UserPort::showMenu()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
	  menu.addSelectionListItem("Compose SMS", "");
    menu.addSelectionListItem("View SMS", "");
    menu.addSelectionListItem("Sent SMS", "");
   // setCurMode(View::HomeMenu, &menu);
    gui.setAcceptCallback([&](){
        switch(menu.getCurrentItemIndex().second){
            case 0:
                showComposeSmsMode();
                break;
            case 1:
                showSmsList();
                break;
            case 2:
                showSentSMSList();
                break;
        }
    });

}

void UserPort::showComposeSmsMode()
{
     IUeGui::ISmsComposeMode& composeMode = gui.setSmsComposeMode();
     composeMode.clearSmsText();
     //setCurMode(View::NewSms, &composeMode);
     gui.setAcceptCallback([&](){
     composeMode.clearSmsText();
     showMenu();
     });
}
void UserPort::showSentSMSList(){

    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    std::vector<Sms> smsList=db_w.getAll();
    if(db_w.size()==0) menu.addSelectionListItem("No messages","");
    else
    {
    for(Sms sms : smsList)
    {
        menu.addSelectionListItem(to_string(sms.from)+(sms.read==false?"\tNew":""),sms.message);
    }
    gui.setAcceptCallback([&](){

        showSentSMS(menu.getCurrentItemIndex().second);

    });
    }
    //setCurMode(View::SmsList,&menu);
}
void UserPort::showSentSMS(int id)
{
    IUeGui::ITextMode& menu = gui.setViewTextMode();
    Sms* sms = db_w.get(id);
    std::string text="To: "+to_string(sms->from)+"\n\n"+sms->message;
    menu.setText(text);
    sms->read=true;
    bool allRead=true;
    for(Sms sms : db_w.getAll())
        if(sms.read==false){allRead=false;break;}
    //if(allRead==true)showSmsReceived();
    //setCurMode(View::SentSmsView, &menu);
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
