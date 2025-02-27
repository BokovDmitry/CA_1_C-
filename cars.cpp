#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <limits.h>
#include <list>

struct Car
{
    std::string make;
    std::string model;
    int year;
    double engineSize;
    bool isElectric;
};

void parse(const std::string& line, std::string& make, std::string& model, int& year, double& engineSize, bool& isElectric)
{
    std::stringstream ss(line);
    std::string temp;

    getline(ss, make, ',');
    getline(ss, model, ',');
    getline(ss, temp, ',');
    year = std::stoi(temp);

    getline(ss, temp, ',');
    engineSize = std::stod(temp);
    getline(ss, temp);
    isElectric = (temp == "Electric" || temp == "Yes" || temp == "True");
}

std::vector<Car> readCarsFromFile(const std::string &filename)
{
    std::vector<Car> cars;
    std::ifstream fin(filename);

    if (fin)
    {
        std::string line;
        while (getline(fin, line))
        {
            std::string make, model;
            int year = 0;
            double engineSize = 0.0;
            bool isElectric = false;

            parse(line, make, model, year, engineSize, isElectric);
            cars.push_back({make, model, year, engineSize, isElectric});
        }
    }
    return cars;
}

void displayCars(const std::vector<Car>& cars)
{
    std::cout << std::left << std::setw(15) << "Make" << std::setw(20) << "Model" << std::setw(10) << "Year" << std::setw(15) << "Engine Size" << std::setw(15) << "Fuel Type" << std::endl;
    for (const Car& car : cars)
    {
        std::cout << std::left << std::setw(15) << car.make << std::setw(20) << car.model << std::setw(10) << car.year << std::setw(15) << car.engineSize << std::setw(15) << (car.isElectric ? "Electric" : "Gas") << std::endl;
    }
}

void displayCars(const std::list<Car>& cars)
{
    std::list<Car>::const_iterator it;
    std::cout << std::left << std::setw(15) << "Make" << std::setw(20) << "Model" << std::setw(10) << "Year" << std::setw(15) << "Engine Size" << std::setw(15) << "Fuel Type" << std::endl;

    for(it = cars.cbegin(); it != cars.cend(); it++)
    {
        std::cout << std::left << std::setw(15) << it->make << std::setw(20) << it->model << std::setw(10) << it->year << std::setw(15) << it->engineSize << std::setw(10) << (it->isElectric ? "Electric" : "Gas") << std::endl;
    }
}

void displayCar(const Car& car)
{
    std::cout << "Make: " << car.make << ", Model: " << car.model << ", Year: " << car.year << ", Engine Size: " << car.engineSize <<", Fuel Tyre: "<< (car.isElectric ? "Electric" : "Gas") << std::endl;
}

int findIndexOfCarByModel(const std::vector<Car>& cars, const std::string& model)
{
    for(int i = 0; i < cars.size(); i++)
    {
        if(cars[i].model == model)
        {
            return i;
        }
    }
    return -1;
}

std::map<std::string, int> countCarMakes (const std::vector<Car>& Cars)
{
    std::map<std::string, int> makes;
    for (const Car& car : Cars)
    {
        makes[car.make]++;
    }
    return makes;
}

std::vector<Car> findCarsByMake(const std::vector<Car>& cars, const std::string& make)
{
    std::vector<Car> carsByMake;
    for (const Car& car : cars)
    {
        if(car.make == make)
        {
            carsByMake.push_back(car);
        }
    }
    return carsByMake;
}

int avgYear(const std::vector<Car>& cars)
{
    int sum = 0;
    int maxEngine = 0;
    Car minEngineCar = Car();
    Car maxEngineCar = Car();
    int minEngine = INT_MAX;

    for (const Car& car : cars)
    {
        if(car.engineSize > maxEngine)
        {
            maxEngine = car.engineSize;
            maxEngineCar = car;
        }

        if(car.engineSize < minEngine)
        {
            minEngine = car.engineSize;
            minEngineCar = car;
        }
            
        sum += car.engineSize;
    }
    std::cout << "Average Car Engime Size: " << sum / cars.size() << "L";
    std::cout << "\nCar with the smallest engine: ";
    displayCar(minEngineCar);
    std::cout << "\nCar with the largest engine: ";
    displayCar(maxEngineCar);
    return sum / cars.size();
}

std::list<Car> findMatch(const std::vector<Car>& cars, const std::string& text)
{
    std::list<Car> carMatches;
    std::vector<Car>::const_iterator it;
    for(it = cars.cbegin(); it != cars.cend(); it++)
    {
        if(it->make.find(text) != std::string::npos || it->model.find(text) != std::string::npos)
        {
            carMatches.push_back(*it);
        }
    }

    return carMatches;
}

std::vector<Car> sortDescending(std::vector<Car> cars)
{
    std::sort(cars.begin(), cars.end(), [](const Car& a, const Car& b) {return a.engineSize > b.engineSize;});
    return cars;
}

