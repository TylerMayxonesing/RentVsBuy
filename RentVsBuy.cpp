//
// Created by T Alpha 1 on 10/13/2019.
//

#include "RentVsBuy.h"

void HomeBuyingInfo() {
  double price;
  double downPayment;
  double loanAmount;
  double loanInterest;
  double loanTerm;
  double taxes;
  double appreciation;
  double homeTax;
  double mortgage;
  double inflationRate;
  int years;

  std::cout << "Enter the purchase price of the home: ";
  std::cin >> price;

  std::cout << "Enter your down payment: ";
  std::cin >> downPayment;

  loanAmount = price - downPayment;

  std::cout << "Enter the interest rate on your loan: ";
  std::cin >> loanInterest;

  std::cout << "Enter the term of your loan: ";
  std::cin >> loanTerm;

  mortgage = 12*(loanAmount * (loanInterest / 12) * pow((1 + (loanInterest / 12)), (12 * loanTerm))) / (pow((1 + (loanInterest / 12)), (12 * loanTerm)) - 1);

  std::cout << "Enter the property tax rate on the home: ";
  std::cin >> taxes;
  homeTax = taxes*price;

  float maintenance = 0.01 * price;

  std::cout << "Enter the rate at which you expect your home to appreciate each year:";
  std::cin >> appreciation;

  std::cout << "Enter the expected average yearly inflation rate: ";
  std::cin >> inflationRate;

  std::cout << "Enter how many years in the future you want to look: ";
  std::cin >> years;

  float equivalence = homeTax*pow((1 + inflationRate),years);

  float total = equivalence + maintenance + mortgage + downPayment;
  std::cout << total;

}








void CommuteFromHome() {
  double miles;
  int choice;
  double cost;

  std::cout << "Enter how many miles from work your home is: ";
  std::cin >> miles;

  std::cout << "How will you be getting to work from your home?\n"
               "Enter 1 for driving.\n"
               "Enter 2 for public transit.\n"
               "Enter 3 for biking, walking, etc.\n"
               "Enter your choice: ";
  std::cin >> choice;

  std::cout << "Enter how much it costs to drive your car per mile: ";
  std::cin >> cost;
}
void RentingInfo() {
  double monthlyRent;
  double returnRate;

  std::cout << "Enter your monthly rent payment: ";
  std::cin >> monthlyRent;

  std::cout << "Enter your expected annual average rate of return on your investments: ";
  std:: cin >> returnRate;

}
void CommuteFromApartment() {
  double miles;
  int choice;
  double transitCost;
  double inflationRate;
  double years;

  std::cout << "Enter how many miles from work your apartment is: ";
  std::cin >> miles;

  std::cout << "How will you be getting to work from your apartment?\n"
               "Enter 1 for driving.\n"
               "Enter 2 for public transit.\n"
               "Enter 3 for biking, walking, etc.\n"
               "Enter your choice: ";
  std::cin >> choice;

  std::cout << "Enter your monthly public transit costs: ";
  std::cin >> transitCost;

  std::cout << "Enter the expected average yearly inflation rate: ";
  std::cin >> inflationRate;

  std::cout << "Enter how many years in the future you want to look: ";
  std::cin >> years;
}
