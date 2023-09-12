
#include "clientui.h"

#include <memory>
#include <utility>

// ClientUI
void ClientUI::setCui(std::unique_ptr<IClientUI> cui_) {
    cui = std::move(cui_);
}
void ClientUI::init(ClientCtrl* ctrl_){
    if (cui) cui->init(ctrl_);
}
void ClientUI::mainmenu() {
    if (cui) cui->mainmenu();
}
void ClientUI::newSession() {
    if (cui) cui->newSession();
}
void ClientUI::trading() {
    if (cui) cui->trading();
}
void ClientUI::renderWLPrice() {
    if (cui) cui->renderWLPrice();
}

void ClientUI::renderOpenPositions() {
    if (cui) cui->renderOpenPositions();
}

void ClientUI::pullWatchlist() {
    if (cui) cui->pullWatchlist();
}

void ClientUI::makeTransaction() {
    if (cui) cui->makeTransaction();
}

void ClientUI::advanceTime() {
    if (cui) cui->advanceTime();
}


// IClientUI
void IClientUI::init(ClientCtrl* ctrl_) {
    ctrl = ctrl_;
}