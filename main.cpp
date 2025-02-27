#include "cars.cpp"

void menu()
{
    std::vector<Car> cars = readCarsFromFile("MOCK_DATA(1).csv");

    int option = 0;
    std::string desiredModel;
    std::string desiredMake;
    int index = 0;

    do{
        std::cout << "1. Display all cars" << std::endl;
        std::cout << "2. Find index of a car by model" << std::endl;
        std::cout << "3. Count car makes" << std::endl;
        std::cout << "4. Display cars by make" << std::endl;
        std::cout << "5. Display average year, car with min/max engine size" << std::endl;
        std::cout << "6. Search a car" << std::endl;
        std::cout << "7. Sort cars in a descendeing order" << std::endl;
        std::cout << "8. Exit" << std::endl;

        std::cout << "Enter your choice: ";
        std::cin >> option;

        switch (option)
        {
        case 1:
            displayCars(cars);
            break;
        case 2:
            std::cout << "Enter model: ";
            getline(std::cin, desiredModel);
            index = findIndexOfCarByModel(cars, desiredModel);
            if(index != -1)
            {
                std::cout << "Car found at index: " << index << std::endl;
            }
            else
            {
                std::cout << "Car not found" << std::endl;
            }
            break;
        case 3:
            countCarMakes(cars);
            break;
        case 4:
            std::cout << "Enter make: ";
            getline(std::cin, desiredMake);
            displayCars(findCarsByMake(cars, desiredMake));
            break;
        case 5:
            avgYear(cars);
            break;
        case 6:
            std::cout << "Enter a part of the car's make or model: ";
            getline(std::cin, desiredModel);
            findMatch(cars, desiredModel);
            break;
        case 7:
            sortDescending(cars);
            break;
        default:
            std::cout << "Invalid option" << std::endl;
            break;
        }
    } while (option != 8);
    
}

int main()
{
    menu();
    return 0;
}