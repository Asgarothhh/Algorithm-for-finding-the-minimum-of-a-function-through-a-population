#include <iostream>
#include <random>
#include <vector>
#include <iomanip>
using namespace std;

const size_t SIZE = 1000;;

double targetFunction(double x, int b)
{
    double sum1 = cos(x) + 1.0 / 3 * cos(9 * x + 1);
    double sum2 = 1 / pow(3, 2) * cos(81 * x + 2);
    double sum3 = 1 / pow(3, 3) * cos(729 * x + 3);
    double sum4 = 1 / pow(3, 4) * cos(6561 * x + 4);
    return (sum1 + sum2 + sum3 + sum4);
}

void initPopulation(vector<vector<double>>& population, vector<vector<double>>& functionValues, int b)
{
    mt19937 gen(time(nullptr));
    uniform_real_distribution<double> dis(-15.0, 15.0);
    for (size_t i = 0; i < population.size(); ++i)
    {
        for (size_t j = 0; j < population[i].size(); ++j)
        {
            population[i][j] = dis(gen);
            functionValues[i][j] = targetFunction(population[i][j], b);
        }
    }
}

void movePoints(vector<vector<double>>& population, vector<vector<double>>& functionValues, double& stepSize, double decayRate, int b)
{
    for (size_t i = 0; i < population.size(); ++i)
    {
        for (size_t j = 0; j < population[i].size(); ++j)
        {
            double newPosition = population[i][j] + stepSize;
            double newValue = targetFunction(newPosition, b);

            if (newValue < functionValues[i][j])
            {
                population[i][j] = newPosition;
                functionValues[i][j] = newValue;
            }
        }
        stepSize *= decayRate;
    }
}

int main()
{
	setlocale(LC_ALL, "Russian");

    vector<vector<double>> Population(SIZE, vector<double>(3));
    vector<vector<double>> FunctionValues(SIZE, vector<double>(3));
    const double decayRate = 0.99;
    const double minStepSize = 0.0000001;
    double stepSize = 7;
    int b;

    cout << "Введите значение b: ";
    cin >> b;

    initPopulation(Population, FunctionValues, b);

    while (stepSize > minStepSize)
    {
        movePoints(Population, FunctionValues, stepSize, decayRate, b);
    }

    cout << "\nСгенерированная популяция:\n";
    for (size_t i = 0; i < Population.size(); ++i)
    {
        cout << "Номер популяции: " << i + 1 << setw(6);
        for (size_t j = 0; j < Population[i].size(); ++j)
        {
            cout << j+1 << ") " << Population[i][j] << setw(9);
        }
        cout << endl;
    }

    cout << "\nПолученные значения функции:\n";
    for (size_t i = 0; i < FunctionValues.size(); ++i)
    {
        cout << "Номер группы: " << i + 1 << setw(5);
        for (size_t j = 0; j < FunctionValues[i].size(); ++j)
        {
            cout << j + 1 << ") " << FunctionValues[i][j] << setw(9);
        }
        cout << endl;
    }

    vector <double> BestFunctionValues(3);
    vector <double> BestIndividuals(3);
    for (size_t j = 0; j < 3; ++j)
    {
        double minFunctionValue = FunctionValues[0][j];
        double bestIndividual=Population[0][j];
        for (size_t i = 0; i<1000; ++i)
        {
           if (FunctionValues[i][j] < minFunctionValue)
           {
               minFunctionValue = FunctionValues[i][j];
               bestIndividual = Population[i][j];
           }
        }
        BestFunctionValues[j] = minFunctionValue;
        BestIndividuals[j] = bestIndividual;
    }

    cout << "\nЛучшие значения функции: \n";
    for (size_t i = 0; i < BestFunctionValues.size(); ++i)
        cout << i+1 << ") " << BestFunctionValues[i] << endl;

    cout << "\nСоответствующие значениям функции лучшие <особи>: \n";
    for (size_t i = 0; i < BestIndividuals.size(); ++i)
        cout << i + 1 << ") " << BestIndividuals[i] << endl;
     
    double minOfFunction = BestFunctionValues[0];
    size_t indexOfBestIndividuals=0;
    for (size_t i = 1; i < BestFunctionValues.size(); ++i)
    {
        if (BestFunctionValues[i] < minOfFunction)
        {
            minOfFunction = BestFunctionValues[i];
            indexOfBestIndividuals = i;
        }
    }

    cout << "\nИскомые лучшие экземпляры <особи> и минимального значения функции: \n";
    cout << "<Особь>: " << setw(6) << BestIndividuals[indexOfBestIndividuals] << ", минимум функции: " << setw(6) << minOfFunction << endl;
    return 0;
}
