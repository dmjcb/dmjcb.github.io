#include "fmt/core.h"
#include <string>

int main(){
    std::string world = fmt::format("Hello {0}", "World");
    fmt::print("{}\n", world);
}