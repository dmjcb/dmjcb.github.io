#pragma once
#include <string>
#include <vector>

namespace sdk {

class Core {
public:
    explicit Core(int base);
    ~Core();

    int add(int v) const;
    std::string name() const;

private:
    int base_;
};

} // namespace sdk
