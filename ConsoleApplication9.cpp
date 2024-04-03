#include <iostream>
#include <cmath>
#include <random>
#include <thread>
#include <omp.h>
using namespace std;
int main() 
{
    setlocale(LC_ALL, "Russian");
    unsigned int n;
    unsigned int count_threads;
    int count_hit_points = 0;
    double x, y;
    cout << "Введите число точек: ";
    cin >> n;
    cout << "Введите число потоков: ";
    cin >> count_threads;
    count_threads = thread::hardware_concurrency();
#pragma omp parallel num_threads(count_threads) reduction(+:count_hit_points) private(x, y)
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(-1.0, 1.0);
#pragma omp for
        for (unsigned int i = 0; i < n; ++i) 
        {
            x = dis(gen);
            y = dis(gen);
            if (pow(x, 2) + pow(y, 2) <= 1) 
            {
                ++count_hit_points;
            }
        }
    }
    double pi_approx = 4.0 * count_hit_points / n;
    cout << "Пи ~= " << pi_approx << endl;
    return 0;
}
