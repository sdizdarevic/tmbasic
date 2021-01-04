#include "Value.h"

#include <utility>

#include <utility>
#include "shared/util/decimal.h"

namespace vm {

Value::Value() = default;

Value::Value(decimal::Decimal num) : num(std::move(std::move(num))) {}

bool Value::operator==(const Value& rhs) const {
    return num == rhs.num;
}

bool Value::getBoolean() const {
    return num != 0;
}

void Value::setBoolean(bool value) {
    num = value ? 1 : 0;
}

int64_t Value::getInt64() const {
    return num.floor().i64();
}

std::string Value::getString() const {
    return util::decimalToString(num);
}

}  // namespace vm
