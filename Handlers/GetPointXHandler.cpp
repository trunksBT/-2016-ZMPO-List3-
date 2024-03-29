
#include <iostream>

#include "GetPointXHandler.hpp"
#include <Utils/Utils.hpp>
#include <Shapes/Point.hpp>
#include <Flyweight/Flyweight.hpp>
#include <Utils/Logger.hpp>

using namespace defaultVals;
using namespace funs;
using namespace cacheIdx;
using namespace tupleIdx;
using namespace typeLiterals;

CGetPointXHandler::CGetPointXHandler(std::vector<std::string>& inCommand)
    : IHandler(inCommand), IPointHandler(inCommand)
{}

const int CGetPointXHandler::getProperAmountOfArgs()
{
    return 2;
}

std::string CGetPointXHandler::getProperTypesOfArgs()
{
    return "si";
}

CODE CGetPointXHandler::checkArgsAndPerform(CPointWithSize inPointCache)
{
    if (IHandler::checkTypeAndAmountOfArgs() == CODE::DONE)
    {
        return purePerform(inPointCache);
    }
    else
    {
        return CODE::ERROR;
    }
}

CODE CGetPointXHandler::purePerform(CPointWithSize inCache)
{
    std::string receivedId(wholeCommand_[idxOf::ID_OF_POINTS]);
    int idxOrAmount = std::stoi(receivedId);

    if (!isProperIdx(idxOrAmount, std::get<SIZE>(inCache)))
    {
        return CODE::ERROR;
    }

    Logger() << POINT << SPACE << X << SEPARATOR <<
        std::to_string(std::get<ARRAY>(inCache)[idxOrAmount]->getX()) << POST_PRINT;

    return CODE::DONE;
}
