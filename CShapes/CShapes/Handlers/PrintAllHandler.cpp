#include "stdafx.h"
#include <iostream>

#include "PrintAllHandler.h"
#include "../Utils.hpp"
#include "../Shapes/Point.hpp"
#include "../Flyweight.h"
#include "../UtilsForMT.h"
#include "../Logger.h"

using namespace defaultVals;
using namespace funs;
using namespace assertWrapper;
using namespace tupleIdx;
using namespace typeLiterals;

CPrintAllHandler::CPrintAllHandler(std::vector<std::string>& inCommand)
    : IHandler(inCommand), IPointHandler(inCommand), IShapeHandler(inCommand), IPointAndRectangleHandler(inCommand)
{}

const int CPrintAllHandler::getProperAmountOfArgs()
{
    return 1;
}

std::string CPrintAllHandler::getProperTypesOfArgs()
{
    return "s";
}

CODE CPrintAllHandler::checkArgsAndPerform(
    CPointWithSize inPointCache,
    CShapeWithSize inRectangleCache)
{
    if (checkTypeAndAmountOfArgs() == CODE::DONE)
    {
        return purePerform(inPointCache, inRectangleCache);
    }
    else
    {
        return CODE::ERROR;
    }
}

CODE CPrintAllHandler::purePerform(
    CPointWithSize inPointCache,
    CShapeWithSize inRectangleCache)
{
    CODE retCode = CODE::ERROR;

    retCode = getFinalResultCode
    ({
        checkArgsAndPerform(inPointCache),
        checkArgsAndPerform(inRectangleCache)
    });

    return retCode;
}

CODE CPrintAllHandler::checkArgsAndPerform(CShapeWithSize inCache)
{
    if (checkTypeAndAmountOfArgs() == CODE::DONE)
    {
        return purePerform(inCache);
    }
    else
    {
        return CODE::ERROR;
    }
}

CODE CPrintAllHandler::checkArgsAndPerform(CPointWithSize inCache)
{
    if (checkTypeAndAmountOfArgs() == CODE::DONE)
    {
        return purePerform(inCache);
    }
    else
    {
        return CODE::ERROR;
    }
}

CODE CPrintAllHandler::purePerform(CPointWithSize inCache)
{
    int cacheSize = std::get<SIZE>(inCache);

    Logger() << POINTS << POST_PRINT;
    std::map<int, bool> isInitializedMap = std::get<INITIALIZED_MAP>(inCache);

    for (int i = 0; i < cacheSize; i++)
    {
        if (isInitializedMap[i])
        {
            Logger() << std::get<ARRAY>(inCache)[i]->toString() << POST_PRINT;
        }
        else
        {
            Logger() << toString(CODE::NOT_INITIALIZED) << POST_PRINT;
        }
    }
    return CODE::DONE;
}

CODE CPrintAllHandler::purePerform(CShapeWithSize inCache)
{
    int cacheSize = std::get<SIZE>(inCache);

    Logger() << SHAPES << POST_PRINT;
    std::map<int, bool> isInitializedMap = std::get<INITIALIZED_MAP>(inCache);

    for (int i = 0; i < cacheSize; i++)
    {
        if (isInitializedMap[i])
        {
            Logger() << std::get<ARRAY>(inCache)[i]->toString();
        }
        else
        {
            Logger() << toString(CODE::NOT_INITIALIZED);
        }
        Logger() << POST_PRINT;
    }

    return CODE::DONE;
}
