#include <iostream>
#include <string>

class Overcoat {
public:
    std::string brand;
    double price;
    Overcoat(Overcoat&& other) noexcept
        : brand(std::move(other.brand)), price(other.price) {
        other.price = 0.0;
    }
    friend std::ostream& operator<<(std::ostream& os, const Overcoat& coat) {
        os << "Brand: " << coat.brand << ", Price: " << coat.price;
        return os;
    }
    Overcoat() : brand(""), price(0.0) {}
};

class Flat {

public:
    int area;
    std::string address;
    Flat(Flat&& other) noexcept
        : area(std::exchange(other.area, 0)), address(std::move(other.address)) {}
    Flat& operator=(Flat&& other) noexcept {
        if (this != &other) {
            area = std::exchange(other.area, 0);
            address = std::move(other.address);
        }
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Flat& flat) {
        os << "Address: " << flat.address << ", Area: " << flat.area;
        return os;
    }
    Flat() : area(0), address("") {}
};

int main() {
    Overcoat coat1;
    coat1.brand = "ABC";
    coat1.price = 100.0;

    Overcoat coat2(std::move(coat1));
    std::cout << "Coat 2: " << coat2 << std::endl;

    Flat flat1;
    flat1.area = 100;
    flat1.address = "123 Main Street";

    Flat flat2(std::move(flat1));
    std::cout << "Flat 2: " << flat2 << std::endl;

    return 0;
}
