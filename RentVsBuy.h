//
// Created by T Alpha 1 on 10/13/2019.
//

#ifndef RENTVSBUY__RENTVSBUY_H_
#define RENTVSBUY__RENTVSBUY_H_

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <tgmath.h>

std::vector<double> HomeBuyingInfo();
std::vector<double> HomeBuyingCalculations(double,double,double,double,double,double,double,double);
double CommuteFromHome();


std::vector<double> RentingInfo();
double CommuteFromApartment();
std::vector<double> RentingCalculations(double, double, double);
double modeOfTransportation();

void RunRentVsBuy();



#endif //RENTVSBUY__RENTVSBUY_H_
