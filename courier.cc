#include "watcardOffice.h"

using namespace std;

WATCardOffice::Courier::Courier( WATCardOffice& watcardOffice ) 
        : watcardOFfice(watcardOFfice) {
}

void WATCardOffice::Courier::main() {
    watcardOffice.requestWork();
}
