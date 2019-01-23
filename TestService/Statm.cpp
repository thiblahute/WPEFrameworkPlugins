#include "MemoryAllocation.h"
#include "Module.h"

#include "TestCommandController.h"

namespace WPEFramework {

class Statm : public Exchange::ITestUtility::ICommand {
private:
    Statm(const Statm&) = delete;
    Statm& operator=(const Statm&) = delete;

public:
    Statm()
        : _memoryAdmin(MemoryAllocation::Instance())
    {
        TestCore::TestCommandController::Instance().Announce(this);
    }

    virtual ~Statm()
    {
        TestCore::TestCommandController::Instance().Revoke(this);
    }

public:
    // ICommand methods
    virtual string Execute(const string& params) { return EMPTY_STRING; }
    virtual const string& Description() const { return _description; }
    virtual const string& Signature() const { return _signature; }
    virtual const string& Name() const { return _name; }

private:
    BEGIN_INTERFACE_MAP(MemoryAllocationTS)
        INTERFACE_ENTRY(Exchange::ITestUtility::ICommand)
    END_INTERFACE_MAP

private:
    MemoryAllocation& _memoryAdmin;
    const string _description = EMPTY_STRING;
    const string _name = EMPTY_STRING;
    const string _signature = EMPTY_STRING;
};

static Statm* _singleton(Core::Service<Statm>::Create<Statm>());

} // namespace WPEFramework
