#include "TestCommandController.h"

namespace WPEFramework {
namespace TestCore {

/* static */ TestCommandController& TestCommandController::Instance()
{
    static TestCommandController _singleton;
    return (_singleton);
}

string /*JSON*/ TestCommandController::TestCommands(void)
{
    string response;
    Metadata testCommands;

    for (auto& testCommand : _commands)
    {
        Core::JSON::String name;
        name = testCommand.first;
        testCommands.TestCommands.Add(name);
    }
    testCommands.ToString(response);

    return response;
}

void TestCommandController::Announce(Exchange::ITestUtility::ICommand* command)
{
    ASSERT(command != nullptr);

    _adminLock.Lock();
    _commands[command->Name()] = command;
    _adminLock.Unlock();
}

void TestCommandController::Revoke(Exchange::ITestUtility::ICommand* command)
{
    ASSERT(command != nullptr);

    _adminLock.Lock();
    _commands.erase(command->Name());
    _adminLock.Unlock();
}

Exchange::ITestUtility::ICommand* TestCommandController::Command(const string& name)
{
     Exchange::ITestUtility::ICommand* command = nullptr;
    _adminLock.Lock();
    command = _commands[name];
    _adminLock.Unlock();
    return command;
}

Exchange::ITestUtility::ICommand::IIterator* TestCommandController::Commands(void) const
{
    Exchange::ITestUtility::ICommand::IIterator* iterator = nullptr;
    _adminLock.Lock();
    iterator = Core::Service<Iterator>::Create<Exchange::ITestUtility::ICommand::IIterator>(_commands);
    _adminLock.Unlock();
    return iterator;
}

} // namespace TestCore
} // namespace WPEFramework