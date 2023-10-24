#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "polynomial.h"

bool operator<(std::pair<double, double>& a, std::pair<double, double>& b);
Polynomial Newton(std::vector<std::pair<double, double> >& v);

int main() {
	std::vector<std::pair<double, double> > dane = { {-4, -1}, {-2, -7}, {0, -21}, {1, -1}, {3, 573} };
	Polynomial ans = Newton(dane);
	ans.show();
	std::cout << std::endl << ans.value(2);
	return 0;
}

bool operator<(std::pair<double, double>& a, std::pair<double, double>& b) {
	return (a.first < b.first);
}

Polynomial Newton(std::vector<std::pair<double, double> >& v) {
	auto temp = v.end();
	std::sort(v.begin(), v.end());
	if (temp != std::unique(v.begin(), v.end())) {
		std::cerr << "wezly musza byc rozne!!!\n";
		return Polynomial();
	}

	if (v.size() == 0)
		return Polynomial();

	const int SIZE = v.size();

	double** array = new double*[SIZE];							
	for (int i = 0; i < SIZE; i++)
		array[i] = new double[SIZE + 1];

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE + 1; j++)
			array[i][j] = 0;
	}

	for (int i = 0; i < SIZE; i++) {
		array[i][0] = v[i].first;
		array[i][1] = v[i].second;									
	}

	for (int i = 2; i <= SIZE; i++) {					
		for (int j = i - 1; j < SIZE; j++) {			
			array[j][i] = (array[j][i - 1] - array[j - 1][i - 1]) / (array[j][0] - array[j - i + 1][0]);
		}
	}

	Polynomial* temporary = new Polynomial[SIZE - 1];
	for (int i = 0; i < SIZE - 1; i++) {
		temporary[i] = {1, -1 * array[i][0]};
	}

	Polynomial result;
	result = Polynomial{array[0][1]};
	Polynomial t;
	for (int i = 0; i < SIZE - 1; i++) {
		t = Polynomial({ array[i + 1][i + 2] });
		for (int j = i; j >= 0; j--)
			t *= temporary[j];
		result += t;
	}

	delete[] temporary;
	for (int i = 0; i < SIZE; i++)
		delete[] array[i];
	delete[] array;

	result.setLim(v[0].first, v[SIZE - 1].first);

	return result;
}