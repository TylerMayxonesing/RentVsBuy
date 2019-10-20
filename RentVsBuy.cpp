//
// Created by T Alpha 1 on 10/13/2019.
//

#include "RentVsBuy.h"

void HomeBuyingInfo() {
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


  std::cout << "Enter the property tax rate on the home: ";
  std::cin >> propertyTax;
  taxes = propertyTax*homeValue;


  double maintenance = 0.01 * homeValue;


  std::cout << "Enter the rate at which you expect your home to appreciate each year: ";
  std::cin >> appreciation;

  double realTax = propertyTax*homeValue*pow(1+(appreciation/12),0);

  double transportation = CommuteFromHome();



  totalCost = maintenance + mortgage + downPayment + transportation + taxes - downPayment;
  for (int i = 1; i <= 12; i++) {
    loanAmount = loanAmount*(1+loanInterest/12);
    loanAmount = loanAmount - (mortgage/12);
    homeValue = homeValue*((appreciation/12)+1);

  }
  double realHomeValue = homeValue - loanAmount;


  std::cout << "Mortgage,Taxes(real),Home Transportation(real),Home Maintenance(real),Home Costs Total(real),Home Value(real)\n"
               <<round(mortgage)<<","<<round(realTax)<<","<<round(transportation)<<","<<round(maintenance)<<","<<round(totalCost) << "," << round (realHomeValue) << std::endl;
}




















void RentingInfo() {
  double monthlyRent;
  double returnRate;

  std::cout << "Enter your monthly rent payment: ";
  std::cin >> monthlyRent;
  std::cout << "Rental: " << monthlyRent*12 << std::endl;

  std::cout << "Enter your expected annual average rate of return on your investments: ";
  std:: cin >> returnRate;

  double transportation = round(CommuteFromApartment());

  int total = monthlyRent*12 + returnRate + transportation;

  std::cout << "Total: " << total;
}

double CommuteFromHome() {
  double miles;
  double cost;
  std::cout << "Enter how many miles from work your home is: ";
  std::cin >> miles;
  double mpg = modeOfTransportation();
  cost = mpg * miles*2*261;
  return cost;
}

double CommuteFromApartment() {
  double miles;
  double cost;
  double inflationRate;
  double years;

  std::cout << "Enter how many miles from work your apartment is: ";
  std::cin >> miles;
  double mpg = modeOfTransportation();

  cost = mpg * 12;

  std::cout << "Enter the expected average yearly inflation rate: ";
  std::cin >> inflationRate;

  std::cout << "Enter how many years in the future you want to look: ";
  std::cin >> years;

  return cost;
}



double modeOfTransportation() {
  int choice;
  double cost;
  std::cout << "How will you be getting to work from your apartment?\n"
               "Enter 1 for driving.\n"
               "Enter 2 for public transit.\n"
               "Enter 3 for biking, walking, etc.\n"
               "Enter your choice: ";
  std::cin >> choice;
  if (choice == 1){
    std::cout << "Enter how much it costs to drive your car per mile: ";
    std::cin >> cost;
  }
  if (choice == 2){
    std::cout << "Enter your monthly public transit costs: ";
    std::cin >> cost;
  }
  if (choice == 3){
    cost = 0;
  }

  return cost;

}
