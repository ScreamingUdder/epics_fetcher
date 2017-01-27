#include <iostream>
#include <pv/pvaClient.h>

using namespace std;
using std::tr1::static_pointer_cast;
using namespace epics::pvData;
using namespace epics::pvAccess;
using namespace epics::pvaClient;

template <typename T>
class NTScalar {
    public:
        static void getValue(PVStructurePtr& pvStruct) {
            auto valField = pvStruct->getSubField<epics::pvData::PVScalarValue<T>>("value");
            std::cout << "    Value: " << valField->get() << std::endl;
        }
};

int main(int argc,char *argv[])
{
    PvaClientPtr pva = PvaClient::create();

    // Specify "pva" for PV Access or "ca" for Channel Access
    PvaClientChannelPtr channel = pva->channel("THIS_PC:TEMP:SP", "pva", 2.0); 

    // Do some introspection to find out details

    PVStructurePtr pv_structure = channel->get()->getData()->getPVStructure();
    // This didn't do what I expect!
    // std::cout << "Name = " << pv_structure->getFullName() << std::endl;

    StructureConstPtr structure = pv_structure->getStructure();

    Type main_type = structure->getType();
    std::cout << "Type = " << main_type << std::endl;

    std::vector<std::string> names = structure->getFieldNames();

    std::cout << std::endl << "Fields" << std::endl;
    for (int i = 0; i < structure->getNumberFields(); ++i) {
        std::cout << "  " << structure->getFieldName(i) << std::endl;
        FieldConstPtr field = structure->getField(i);
        std::cout << "    Type = " << field->getType() << std::endl;
        std::cout << "    ID = " << field->getID() << std::endl;
    }
    

    // Get value and timestamp
    std::cout << std::endl << "Data Values" << std::endl;

    // Using PVStructure
    std::cout << "  Using PvaClientGetDataPtr" << std::endl;
    NTScalar<double>::getValue(pv_structure);

    PVStructurePtr tsStructure = pv_structure->getSubField<PVStructure>("timeStamp");
    auto tsField = tsStructure->getSubField<PVScalarValue<int64_t>>("secondsPastEpoch");
    std::cout << "    Seconds past Epoch: " << tsField->get() << std::endl;

    
    // Use PvaClientGetData instead - easier to get timestamp this way?
    // However, it is synchronous
    std::cout << "  Using PvaClientGetDataPtr" << std::endl;
    PvaClientGetDataPtr get = channel->get()->getData();
    
    PVFieldPtr valField = get->getValue();
    auto val_field = static_cast<epics::pvData::PVScalarValue<double>*>(valField.get());
    std::cout << "    Value: " << val_field->get() << std::endl;
    std::cout << "    Seconds past Epoch: " << get->getTimeStamp().getSecondsPastEpoch() << std::endl;

    return 0;
}