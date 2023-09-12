#ifndef CLIENTUI_H
#define CLIENTUI_H

#include "clientctrl.h"
#include "candle.h"
#include "trade.h"

#include <string>
#include <vector>
#include <memory>

class IClientUI {
    protected:
        ClientCtrl* ctrl;
    public: 
        void init(ClientCtrl* ctrl_);
        // User interface sections
        virtual void mainmenu() = 0;
        virtual void newSession() = 0;
        virtual void trading() = 0;
 
        virtual void renderWLPrice() = 0;
        virtual void pullWatchlist() = 0;

        virtual void renderOpenPositions() = 0;

        virtual void makeTransaction() = 0;

        virtual void advanceTime() = 0;

};

class ClientUIBash : public IClientUI {
    private:
        // Fields and methods unique for the bash implementation
        const int spacing = 20;
        void renderHeader(std::vector<std::string> headers_);
        void renderPriceaction(std::string tick_, Candle prc);
        void renderTradeValue(std::string tick_, TrdStatus stat);
    public:

        void mainmenu() override;
        void newSession() override;
        void trading() override;

        void renderWLPrice() override;
        void pullWatchlist() override;

        void renderOpenPositions() override;

        void makeTransaction() override;

        void advanceTime();

};

//class ClientGraphical : public IClientUI {
    // Implement later...
//};

class ClientUI {
    private:
        std::unique_ptr<IClientUI> cui;
    public:
        void setCui(std::unique_ptr<IClientUI> cui_);

        void init(ClientCtrl* ctrl_);

        // TARVIIKO TASSA VARSINAISESTI OLLA KUIN MAINMENU KUN
        // KAIKKI MUU KUTSUTAAN CLIENUIBASH-METODIEN SISALTA??
        void mainmenu();
        void newSession();
        void trading();

        void renderWLPrice();
        void pullWatchlist();

        void renderOpenPositions();

        void makeTransaction();

        void advanceTime();
};



#endif