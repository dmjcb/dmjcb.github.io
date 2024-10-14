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
    int getCount() const { return mCount; }
    std::string getId() const { return mID; }
    int getPrice() const { return mPrice; }

    bool operator==(const Item& obj2) const
    {
        return this->getId().compare(obj2.getId()) == 0;
    }
};

bool complePrice(Item& obj, int y)
{
    return obj.getPrice() == y;
}

std::vector<Item> getList()
{
    std::vector<Item> v;
    v.push_back(Item("D121", 100, 2));
    v.push_back(Item("D122", 12, 5));
    v.push_back(Item("D123", 28, 6));
    v.push_back(Item("D124", 8, 10));
    v.push_back(Item("D125", 99, 3));
    return v;
}

int main()
{
    std::vector<Item> v = getList();

    std::vector<Item>::iterator it;
    int num;
    std::cin >> num;
    it = find_if(v.begin(), v.end(), std::bind(complePrice, std::placeholders::_1, num));
    if (it != v.end())
        std::cout << "Item Price :" << it->getPrice()
        << " Count : " << it->getCount() << std::endl;
    else
        std::cout << "Item not Found" << std::endl;
    return 0;
}
