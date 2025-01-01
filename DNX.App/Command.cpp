#include "stdafx.h"
#include "Command.h"
#include "../DNX.Utils/StringUtils.h"

// ReSharper disable CppInconsistentNaming

using namespace std;
using namespace DNX::App;

Command Command::_empty_command = Command(Arguments::Empty(), "", "");

Command::Command(
    Arguments& arguments,
    const string& name,
    const string& description
) :
    _arguments(arguments)
{
    if (StringUtils::Trim(name).empty())
        throw exception("name cannot be empty or blank");

    _name = name;
    _description = description;
}

//Command::Command(const Command& other)
//    :
//    _arguments(other.GetArguments())
//{
//    _name = other.GetName();
//    _description = other.GetDescription();
//}
//
//Command& Command::operator=(const Command& other)
//{
//    _arguments.CopyFrom(other.GetArguments());
//    _name = other.GetName();
//    _description = other.GetDescription();
//    return *this;
//}

bool Command::IsEmpty() const
{
    return _name.empty();
}
Arguments& Command::GetArguments() const
{
    return _arguments;
}
string Command::GetName() const
{
    return _name;
}
string Command::GetDescription() const
{
    return _description;
}

void Command::Execute()
{
}
