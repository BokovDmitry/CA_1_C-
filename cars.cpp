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

//Car structure
struct Car
{
    std::string make;
    std::string model;
    int year;
    double engineSize;
    bool isElectric;
};

//Struct to store data for average release year, the newest car and the oldest car  
struct minMaxYear
{
    Car minYearCar;
    Car maxYearCar;
    int avgYear;
};


//parser function to parse the .csv file line into a Car object 
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

//Function to read the .csv file
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

//function to display the vector of Cars 
void displayCars(const std::vector<Car>& cars)
{
    if(cars.empty())
        std::cout << "No cars found\n";
    else 
    {
        std::cout << std::left << std::setw(15) << "Make" << std::setw(20) << "Model" << std::setw(10) << "Year" << std::setw(15) << "Engine Size" << std::setw(15) << "Fuel Type" << std::endl;
        for (const Car& car : cars)
        {
            std::cout << std::left << std::setw(15) << car.make << std::setw(20) << car.model << std::setw(10) << car.year << std::setw(15) << std::fixed << std::setprecision(2) << car.engineSize << std::setw(15) << (car.isElectric ? "Electric" : "Gas") << std::endl;
        }
    }
}

//override function that accepts list instead of a vector 
void displayCars(const std::list<Car>& cars)
{
    if(cars.empty())
        std::cout << "No card found\n";
    else 
    {
        std::list<Car>::const_iterator it;
        std::cout << std::left << std::setw(15) << "Make" << std::setw(20) << "Model" << std::setw(10) << "Year" << std::setw(15) << "Engine Size" << std::setw(15) << "Fuel Type" << std::endl;

        for(it = cars.cbegin(); it != cars.cend(); it++)
        {
            std::cout << std::left << std::setw(15) << it->make << std::setw(20) << it->model << std::setw(10) << it->year << std::setw(15) << std::fixed << std::setprecision(2) << it->engineSize << std::setw(10) << (it->isElectric ? "Electric" : "Gas") << std::endl;
        }
    }
}

//function to display a single Car
void displayCar(const Car& car)
{
    std::cout << "Make: " << car.make << ", Model: " << car.model << ", Year: " << car.year << ", Engine Size: " << car.engineSize <<", Fuel Tyre: "<< (car.isElectric ? "Electric" : "Gas") << std::endl;
}

//function to find an index of a Car by model (entered by user)
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

//function to display the amount of cars of each make
std::map<std::string, int> countCarMakes (const std::vector<Car>& Cars)
{
    std::map<std::string, int> makes;
    for (const Car& car : Cars)
    {
        makes[car.make]++;
    }
    return makes;
}

//find cars by make (entered by the user) 
void findCarsByMake(const std::vector<Car>& cars, const std::string& make)
{
    std::vector<Car> carsByMake;
    for (const Car& car : cars)
    {
        if(car.make == make)
            carsByMake.push_back(car);
    }
    displayCars(carsByMake);
}

//function that returns the average release year for cars and newest/oldest car in the list 
minMaxYear avgYear(const std::vector<Car>& cars)
{
double sum = 0;
    double maxYear = 0;
    double minYear = INT_MAX;
    Car minYearCar = Car();
    Car maxYearCar = Car();

    for (const Car& car : cars)
    {
        if(car.year > maxYear)
        {
            maxYear = car.year;
            maxYearCar = car;
        }

        if(car.year < minYear)
        {
            minYear = car.year;
            minYearCar = car;
        }
            
        sum += car.year;
    }
    return {minYearCar, maxYearCar, sum / cars.size()};
}

//function to search through the vector of cars and find those that have contain substring entered by the user 
std::list<Car> findMatch(const std::vector<Car>& cars, const std::string& text)
{
    std::list<Car> carMatches;
    std::vector<Car>::const_iterator it;
    for(it = cars.cbegin(); it != cars.cend(); it++)
    {
        //std::string::npos in the context of .find() method means "no match"
        if(it->make.find(text) != std::string::npos || it->model.find(text) != std::string::npos)
        {
            carMatches.push_back(*it);
        }
    }

    return carMatches;
}

//funtion to sort the Cars in a descending order based on cars engineSize 
std::vector<Car> sortDescending(std::vector<Car> cars)
{
    std::sort(cars.begin(), cars.end(), [](const Car& a, const Car& b) {return a.engineSize > b.engineSize;});
    return cars;
}

