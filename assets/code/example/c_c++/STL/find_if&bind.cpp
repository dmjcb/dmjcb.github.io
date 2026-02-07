#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>


class Item {
private:
    std::string mID;
    int         mCount;
    int         mPrice;

public:
    Item(std::string id, int price, int count) : mID(id), mCount(count), mPrice(price) {}
    
    int GetCount() const { return mCount; }
    
    std::string GetId() const { return mID; }
    
    int GetPrice() const { return mPrice; }

    bool operator==(const Item& item) const {
        return this->GetId().compare(item.GetId()) == 0;
    }
};

int main() {
    std::vector<Item> v = {
        Item("D121", 100, 2),
        Item("D122", 12, 5),
        Item("D123", 28, 6),
        Item("D125", 99, 3)
    };

    int num = 6;
    std::vector<Item>::iterator it = find_if(v.begin(), v.end(), std::bind([](Item& item, int price) {return item.GetPrice() == price; }, std::placeholders::_1, num));
    if (it != v.end()) {
        std::cout << "Item Price :" << it->GetPrice() << " Count : " << it->GetCount() << std::endl;
    }
    else {
        std::cout << "Item not Found" << std::endl;
    }
    return 0;
}
