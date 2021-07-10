#pragma once

#include "../common.h"
#include "vm/Value.h"
#include "vm/Object.h"
#include "vm/constants.h"

namespace vm {

enum class SystemCall {
    kAdd,                       // Add(lhs as Number, rhs as Number) as Number
    kAvailableLocales,          // AvailableLocales() as List of String
    kAvailableTimeZones,        // AvailableTimeZones() as List of TimeZone
    kCharacters1,               // Characters(input as String) as List of String
    kCharacters2,               // Characters(input as String, locale as String) as List of String
    kChr,                       // Chr(input as Number) as String
    kDateFromParts,             // DateFromParts(year as Number, month as Number, day as Number) as Date
    kDateTimeFromParts,         // DateFromParts(year as Number, ...) as DateTime
    kDateTimeOffsetFromParts,   // DateOffsetFromParts(year as Number, ..., timeZone as TimeZone) as DateTimeOffset
    kDays,                      // Days(count as Number) as TimeSpan
    kFlushConsoleOutput,        // FlushConsoleOutput()
    kHasValueO,                 // HasValue(input as Optional Object) as Boolean
    kHasValueV,                 // HasValue(input as Optional Value) as Boolean
    kHours,                     // Hours(count as Number) as TimeSpan
    kLen,                       // Len(input as String) as Number
    kMilliseconds,              // Milliseconds(count as Number) as TimeSpan
    kMinutes,                   // Minutes(count as Number) as TimeSpan
    kNumberToString,            // NumberToString(input as Number) as String
    kObjectListGet,             // ObjectListGet(input as ObjectList, index as Number) as Object
    kObjectListLength,          // ObjectListLength(input as ObjectList) as Number
    kObjectOptionalNewMissing,  // ObjectOptionalNewMissing() as ObjectOptional
    kObjectOptionalNewPresent,  // ObjectOptionalNewPresent(input as Object) as ObjectOptional
    kPrintString,               // PrintString(input as String)
    kSeconds,                   // Seconds(count as Number) as TimeSpan
    kTimeZoneFromName,          // TimeZoneFromName(name as String) as TimeZone
    kTotalDays,                 // TotalDays(span as TimeSpan) as Number
    kTotalHours,                // TotalHours(span as TimeSpan) as Number
    kTotalMilliseconds,         // TotalMilliseconds(span as TimeSpan) as Number
    kTotalMinutes,              // TotalMinutes(span as TimeSpan) as Number
    kTotalSeconds,              // TotalSeconds(span as TimeSpan) as Number
    kUtcOffset,                 // UtcOffset(timeZone as TimeZone, dateTime as DateTime) as TimeSpan
    kValueO,                    // ValueO(input as Optional Object) as Boolean
    kValueOptionalNewMissing,   // ValueOptionalNewMissing() as ValueOptional
    kValueOptionalNewPresent,   // ValueOptionalNewPresent(input as Value) as ValueOptional
    kValueV,                    // ValueV(input as Optional Value) as Boolean
};

class SystemCallInput {
   public:
    const std::array<Value, kValueStackSize>& valueStack;
    const std::array<boost::local_shared_ptr<Object>, kObjectStackSize>& objectStack;
    int valueStackIndex;
    int objectStackIndex;
    std::istream* consoleInputStream;
    std::ostream* consoleOutputStream;
    SystemCallInput(
        const std::array<Value, kValueStackSize>& valueStack,
        const std::array<boost::local_shared_ptr<Object>, kObjectStackSize>& objectStack,
        int valueStackIndex,
        int objectStackIndex,
        std::istream* consoleInputStream,
        std::ostream* consoleOutputStream);
    const Value& getValue(const int vsiOffset) const;
    const Object& getObject(const int osiOffset) const;
    boost::local_shared_ptr<Object> getObjectPtr(const int osiOffset) const;
};

class SystemCallResult {
   public:
    Value returnedValue = {};
    boost::local_shared_ptr<Object> returnedObject = nullptr;
    bool hasError = false;
    std::string errorMessage = "";
    int errorCode = 0;
};

void initSystemCalls();
SystemCallResult systemCall(SystemCall which, const SystemCallInput& input);

}  // namespace vm
