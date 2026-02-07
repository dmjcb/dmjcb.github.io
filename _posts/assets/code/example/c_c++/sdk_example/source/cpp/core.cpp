#include "core.hpp"

namespace sdk {

Core::Core(int base) : base_(base) {}

Core::~Core() = default;

int Core::add(int v) const {
    return base_ + v;
}

std::string Core::name() const {
    return "sdk_core";
}

} // namespace sdk
