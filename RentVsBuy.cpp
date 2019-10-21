//
// Created by T Alpha 1 on 10/13/2019.
//

#include "RentVsBuy.h"

std::vector<double> HomeBuyingInfo(int k) {
  double homeValue;
  double downPayment;
  double loanAmount;
  double loanInterest;
  double loanTerm;
  double taxes;
  double appreciation;
  double propertyTax;
  double mortgage;
  double totalCost;
  double realHomeValue;

  std::vector <double> home;
  std::cout << "Enter the purchase price of the home: ";
  std::cin >> homeValue;

  std::cout << "Enter your down payment: ";
  std::cin >> downPayment;

  loanAmount = homeValue - downPayment;

  std::cout << "Enter the interest rate on your loan: ";
  std::cin >> loanInterest;

  std::cout << "Enter the term of your loan: ";
  std::cin >> loanTerm;

  mortgage = 12.*(loanAmount * (loanInterest / 12.) * pow((1. + (loanInterest / 12.)), (12. * loanTerm))) / (pow((1. + (loanInterest / 12.)), (12. * loanTerm)) - 1.);
  home.push_back(mortgage);


  std::cout << "Enter the property tax rate on the home: ";
  std::cin >> propertyTax;
  taxes = propertyTax*homeValue;

  double maintenance = 0.01 * homeValue;


  std::cout << "Enter the rate at which you expect your home to appreciate each year: ";
  std::cin >> appreciation;

  double realTax = propertyTax*homeValue*pow(1+(appreciation/12),0);
  home.push_back(realTax);

  double transportation = CommuteFromHome();
  home.push_back(transportation);
  home.push_back(maintenance);

  totalCost = maintenance + mortgage + transportation + taxes;
  home.push_back(totalCost);
  home.push_back(0);
  home.push_back(0);

  for (int j = 1; j <= k; j++) {
    for (int i = 1; i < 13; i++) {
      loanAmount = loanAmount * (1. + (loanInterest / 12.));
      loanAmount = loanAmount - (mortgage / 12.);
      homeValue = homeValue * (1. + (appreciation / 12.));
    }
    double nominal = homeValue - loanAmount;
    realHomeValue = nominal / (pow(1+(0.035),j-1));
    //std::cout << realHomeValue << std::endl;

    home.at(5) = realHomeValue;

//    for (int k = 0; k < 5; k++){
//      std::cout << home.at(5) << std::endl;
//    }

    //home.push_back(round(mortgage));
    //home.push_back(round(realTax));
    //home.push_back(round(transportation));
    //home.push_back(round(maintenance));
    //home.push_back(round(totalCost));
    //home.push_back(round(homeValue));
    //home.push_back(realHomeValue);
  }
  //std::cout<<home.at(5);
  return home;
}


void RunRentVsBuy(){
  std::vector <double> home;
  for (int years = 1; years < 50; years++) {
    home = HomeBuyingInfo(years);
    //std::cout << "Mortgage: Taxes(real): HomeTransportation: HomeCosts: HomeValue: \n";
    for (int i = 0; i < 6; i++) {
      std::cout << home.at(i);
    }
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

