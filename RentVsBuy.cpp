//
// Created by T Alpha 1 on 10/13/2019.
//

#include "RentVsBuy.h"

std::vector<double> HomeBuyingInfo(){
  double homeValue;
  double downPayment;
  double transportation;
  double loanInterest;
  double loanTerm;
  double appreciation;
  double propertyTax;
  double loanAmount;

  std::vector <double> values;
  std::cout << "Enter the purchase price of the home: ";
  std::cin >> homeValue;

  std::cout << "Enter your down payment: ";
  std::cin >> downPayment;

  loanAmount = homeValue - downPayment;

  std::cout << "Enter the interest rate on your loan: ";
  std::cin >> loanInterest;

  std::cout << "Enter the term of your loan: ";
  std::cin >> loanTerm;

  std::cout << "Enter the property tax rate on the home: ";
  std::cin >> propertyTax;

  std::cout << "Enter the rate at which you expect your home to appreciate each year: ";
  std::cin >> appreciation;

  transportation = CommuteFromHome();

  values.push_back(transportation);
  values.push_back(homeValue);
  values.push_back(loanInterest);
  values.push_back(loanTerm);
  values.push_back(appreciation);
  values.push_back(propertyTax);
  values.push_back(loanAmount);

  return values;

}


std::vector<double> HomeBuyingCalculations(double transportation,double homeValue, double loanInterest,
    double loanTerm, double appreciation,double propertyTax, double loanAmount, int iterations) {

  std::vector<double> home;
  double taxes;
  double realTax;
  double totalCost;
  double mortgage;
  double realHomeValue;

  mortgage = 12.*(loanAmount * (loanInterest / 12.) * pow((1. + (loanInterest / 12.)), (12. * loanTerm))) / (pow((1. + (loanInterest / 12.)), (12. * loanTerm)) - 1.);
  taxes = propertyTax*homeValue;
  double maintenance = 0.01 * homeValue;
  double purchasePrice = homeValue;

  totalCost = maintenance + mortgage + transportation + taxes;
  home.push_back(mortgage);
  home.push_back(0);
  home.push_back(transportation);
  home.push_back(maintenance);
  home.push_back(totalCost);
  home.push_back(0);

  for (int j = 1; j <= iterations; j++) {
    realTax = (purchasePrice * pow (1 + (appreciation / 12) , 12 * (j - 1)) * propertyTax)/ (pow(1+(0.035),j-1));
    for (int i = 1; i <= 12; i++) {
      loanAmount = loanAmount * (1. + (loanInterest / 12.));
      loanAmount = loanAmount - (mortgage / 12.);
      homeValue = homeValue * (1. + (appreciation / 12.));
    }
    home.at(1) = realTax;
    double nominal = homeValue - loanAmount;
    realHomeValue = nominal / (pow(1+(0.035),j-1));
    home.at(5) = realHomeValue;
  }
  //std::cout<<"RealHomeValue: " << home.at(5) << std::endl;
  //std::cout<<"RealTax: " << home.at(1) << std::endl;

  return home;
}

void RunRentVsBuy(){
  std::vector <double> home;
  std::vector<double> homeValues = HomeBuyingInfo();

  for (int years = 1; years < 50; years++) {
  home = HomeBuyingCalculations(homeValues.at(0), homeValues.at(1), homeValues.at(2), homeValues.at(3), homeValues.at(4),
      homeValues.at(5), homeValues.at(6), years);

    for (int i = 0; i < 6; i++) {
      std::cout << home.at(i)<<",";
    }
    std::cout << "\n";
  }
}




void RentingInfo() {
  double monthlyRent;
  double returnRate;
  double transportation;
  double totalCost;
  double yearlyRent;
  double yearlyTransportation;
  double inflationRate;
  double years;



  std::cout << "Enter your monthly rent payment: ";
  std::cin >> monthlyRent;
  yearlyRent = 12. * monthlyRent;

  std::cout << "Enter your expected annual average rate of return on your investments: ";
  std::cin >> returnRate;

  transportation = round(CommuteFromApartment());

  std::cout << "Enter the expected average yearly inflation rate: ";
  std::cin >> inflationRate;

  std::cout << "Enter how many years in the future you want to look: ";
  std::cin >> years;

  //std::cout << "Rent(real), Rent Transportation(real), Rent Costs Total (real)" << std::endl;
  for (int i = 1; i <= 12; i++) {
    totalCost = transportation*pow(1 + (inflationRate / 12), 12 * i)+ yearlyRent * pow(1 + inflationRate / 12, 12 * i);
  }
  std::cout << "Rent(real): " << round(yearlyRent) << ", "<< "Rent Transportation (real): " << transportation <<
            ", " << "Rent Costs Total: "<< round(totalCost)<< std::endl;

}











double CommuteFromHome() {
  double miles;
  double transportationCost;
  std::cout << "Enter how many miles from work your home is: ";
  std::cin >> miles;
  std::cout << "How will you be getting to work from your home?\n";
  transportationCost = modeOfTransportation()*miles;
  return transportationCost;
}

double CommuteFromApartment() {
  double miles;
  double transportationCost;

  std::cout << "Enter how many miles from work your apartment is: ";
  std::cin >> miles;
  std::cout << "How will you be getting to work from your apartment?\n";
  transportationCost = modeOfTransportation();

  return transportationCost;
}



double modeOfTransportation() {
  int choice;
  double cost;
  double transportationCost;
  std::cout <<"Enter 1 for driving.\n"
              "Enter 2 for public transit.\n"
              "Enter 3 for biking, walking, etc.\n"
              "Enter your choice: ";
  std::cin >> choice;
  if (choice == 1){
    std::cout << "Enter how much it costs to drive your car per mile: ";
    std::cin >> cost;
    transportationCost = 261.*2.*cost;
  }
  if (choice == 2){
    std::cout << "Enter your monthly public transit costs: ";
    std::cin >> cost;
    transportationCost = 12.*cost;
  }
  if (choice == 3){
    cost = 0;
    transportationCost = 0;
  }


  return transportationCost;

}

