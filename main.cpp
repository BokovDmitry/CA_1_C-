#include "cars.cpp"

void menu()
{
    std::cout << "1. Display all cars" << std::endl;
    std::cout << "2. Find index of a car by model" << std::endl;
    std::cout << "3. Count car makes" << std::endl;
    std::cout << "4. Display cars by make" << std::endl;
    std::cout << "5. Display average year, car with min/max engine size" << std::endl;
    std::cout << "6. Search a car" << std::endl;
    std::cout << "7. Sort cars in a descendeing order" << std::endl;
    std::cout << "8. Exit" << std::endl;

    
}

int main()
{
    std::vector<Car> cars = readCarsFromFile("MOCK_DATA(1).csv");
    displayCars(cars);
    return 0;
}