#include <iostream>
#include <pv/pvaClient.h>

using namespace std;
using std::tr1::static_pointer_cast;
using namespace epics::pvData;
using namespace epics::pvAccess;
using namespace epics::pvaClient;

int main(int argc,char *argv[])
{
    PvaClientPtr pva = PvaClient::create();
    PvaClientChannelPtr channel = pva->channel("THIS_PC:TEMP:SP", "pva", 2.0); 
    //channel->connect();
    //channel->waitConnect();

    PvaClientGetDataPtr get = channel->get()->getData();


    //double val = channel->getDouble();
    std::cout << "Got a value: " << get->getDouble() << std::endl;
    std::cout << "Got a timestamp: " << get->getTimeStamp().getSecondsPastEpoch() << std::endl;

    return 0;
}