#include "RentVsBuy.h"
#include <fstream>
#include <iostream>

void PrintFile(std::ostream& out, const std::string& fileName){
  std::ifstream infile(fileName);
  char c;
  while((c = infile.get()) != EOF){
    out << c;
  }
}

int main(){

double homeValue = 100000;
double loanInterest = 0.035;
double appreciation = 0.05;
double mortgage = 2694.2756031;
  double loanAmount = 50000;
  double realHomeValue;

  //double realInterest = ((1+0.035)/(1+(0.035/12))) -1;

  for (int j = 1; j <= 30; j++) {
    for (int i = 1; i < 13; i++) {
      loanAmount = loanAmount * (1. + (loanInterest / 12.));
      loanAmount = loanAmount - (mortgage / 12.);
      homeValue = homeValue * (1. + (appreciation / 12.));
    }
    double nominal = homeValue - loanAmount;
    realHomeValue = nominal / (pow(1+(0.035),j-1));
    std::cout << realHomeValue << std::endl;
  }
  HomeBuyingInfo();
  RentingInfo();
  //RunRentVsBuy();
  PrintFile(std::cout, "RentVsBuy.csv");
  return 0;
}



for (int j = 1; j <= 30; j++) {
  for (int i = 1; i < 13; i++) {
    loanAmount = loanAmount * (1. + (loanInterest / 12.));
    loanAmount = loanAmount - (mortgage / 12.);
    homeValue = homeValue * (1. + (appreciation / 12.));
  }
  double nominalHomeValue = homeValue - loanAmount;
  realHomeValue = nominalHomeValue / (pow(1+(0.035),j-1));
  std::cout << realHomeValue << std::endl;
}