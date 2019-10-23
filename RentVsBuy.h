#ifndef RENTVSBUY__RENTVSBUY_H_
#define RENTVSBUY__RENTVSBUY_H_

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <tgmath.h>
#include <fstream>


std::vector<double> HomeBuyingInfo();
std::vector<double> HomeBuyingCalculations(double,double,double,double,double,double,double,double,double);
double CommuteFromHome();


std::vector<double> RentingInfo();
double CommuteFromApartment();
std::vector<double> RentingCalculations(double, double, double);

double modeOfTransportation();

std::vector<double> homeInvestmentCalc(double, double, double, double, double, double);
std::vector<double> rentInvestmentCalc(double, double, double, double, double, double, double);


void RunRentVsBuy();



#endif //RENTVSBUY__RENTVSBUY_H_