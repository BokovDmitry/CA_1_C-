#include "cars.cpp"

void menu()
{
    std::vector<Car> cars = readCarsFromFile("MOCK_DATA(1).csv");

    int option = 0;
    int index = 0;
    std::string optionStr = "";
    std::string desiredModel = "";
    std::string desiredMake = "";
    std::map<std::string, int> carMakes;
    std::list<Car> carsByMatch;
    std::vector<Car> descendingCars;
    minMaxEngineSize minMax = minMaxEngineSize();

    std::string devider = "----------------------------------------";

    do{
        std::cout << "\n" << devider << std::endl;
        std::cout << "\n1. Display all cars" << std::endl;
        std::cout << "2. Find index of a car by model" << std::endl;
        std::cout << "3. Count car makes" << std::endl;
        std::cout << "4. Display cars by make" << std::endl;
        std::cout << "5. Display average year, car with min/max engine size" << std::endl;
        std::cout << "6. Search a car" << std::endl;
        std::cout << "7. Sort cars in a descendeing order" << std::endl;
        std::cout << "8. Exit\n" << std::endl;
        std::cout << devider << std::endl;

        std::cout << "Enter your choice: ";
        getline(std::cin, optionStr);
        option = stoi(optionStr);

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
            carMakes = countCarMakes(cars);
            for (const auto& make : carMakes)
            {
                std::cout << make.first << ": " << make.second << std::endl;
            }
            break;
        case 4:
            std::cout << "Enter make: ";
            getline(std::cin, desiredMake);
            displayCars(findCarsByMake(cars, desiredMake));
            break;
        case 5:
            minMax = avgEngineSize(cars);
            std::cout << "\nAverage Engine Size: " << minMax.avgEngineSize << "L" << std::endl;
            std::cout << "\nCar with the smallest engine: ";
            displayCar(minMax.minEngineCar);
            std::cout << "\nCar with the largest engine: ";
            displayCar(minMax.maxEngineCar);

            break;
        case 6:
            std::cout << "Enter a part of the car's make or model: ";
            getline(std::cin, desiredModel);
            carsByMatch = findMatch(cars, desiredModel);
            displayCars(carsByMatch);
            break;
        case 7:
            descendingCars = sortDescending(cars);
            displayCars(descendingCars);
            break;
        case 8:
            std::cout << "Exiting..." << std::endl;
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