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
                                           double loanTerm, double appreciation,double propertyTax, double loanAmount, int years) {

  std::vector<double> home;
  double taxes;
  double realTax;
  double totalCost = 0;
  double mortgage;
  double realHomeValue;
  double currentYearTotal;


  mortgage = 12.*(loanAmount * (loanInterest / 12.) * pow((1. + (loanInterest / 12.)), (12. * loanTerm))) / (pow((1. + (loanInterest / 12.)), (12. * loanTerm)) - 1.);
  if (years > loanTerm){
    mortgage = 0;
  }
  taxes = propertyTax*homeValue;
  double maintenance = 0.01 * homeValue;
  double purchasePrice = homeValue;

  home.push_back(round(mortgage));
  home.push_back(0);
  home.push_back(round(transportation));
  home.push_back(round(maintenance));
  home.push_back(0);
  home.push_back(0);
  home.push_back(0);

  for (int j = 1; j <= years; j++) {
    realTax = (taxes* pow (1 + (appreciation / 12) , 12 * (j - 1)))/ (pow(1+(0.035),j-1));
    for (int i = 1; i <= 12; i++) {
      loanAmount = loanAmount * (1. + (loanInterest / 12.));
      loanAmount = loanAmount - (mortgage / 12.);
      homeValue = homeValue * (1. + (appreciation / 12.));
    }
    home.at(1) = round(realTax);
    totalCost = totalCost + maintenance + transportation + realTax + (mortgage / (pow((1. + (loanInterest)), j - 1.)));
    currentYearTotal = maintenance + transportation + realTax + (mortgage / (pow((1. + (loanInterest)), j - 1.)));

    home.at(6) = currentYearTotal;
    home.at(4) = round(totalCost);
    double nominal = homeValue - loanAmount;
    realHomeValue = nominal / (pow(1+(0.035),j-1));
    home.at(5) = round(realHomeValue);
  }
  //std::cout<<"RealHomeValue: " << home.at(5) << std::endl;
  //std::cout<<"RealTax: " << home.at(1) << std::endl;
  return home;
}

void RunRentVsBuy(){
  std::ofstream outputFile;
  outputFile.open("RentVsBuy.csv");
  std::vector <double> home;
  std::vector <double> rent;
  std::vector <double> homeInvestment;

  std::vector<double> homeValues = HomeBuyingInfo();
  std::vector<double> rentValues = RentingInfo();
  double last_year_value = 0;

  double homeTransportation = homeValues.at(0);
  double homeValue = homeValues.at(1);
  double loanInterest = homeValues.at(2);
  double loanTerm = homeValues.at(3);
  double appreciation = homeValues.at(4);
  double propertyTax = homeValues.at(5);
  double loanAmount = homeValues.at(6);

  double rentYears = rentValues.at(0);
  double yearlyRent = rentValues.at(1);
  double rentTransportation = rentValues.at(2);
  double inflation = rentValues.at(3);
  double returnRate = rentValues.at(4);

//  values.push_back(years);
//  values.push_back(yearlyRent);
//  values.push_back(transportation);
//  values.push_back(inflationRate);
//  values.push_back(returnRate);

//  home.push_back(round(mortgage));
//  home.push_back(0); realTax
//  home.push_back(round(transportation));
//  home.push_back(round(maintenance));
//  home.push_back(0);totalCost
//  home.push_back(0); realHomeValue
//  home.push_back(0); currentYearTotal

//  rent.push_back(totalCost);
//  rent.push_back(transportation + yearlyRent);


  std::cout << "Year,Mortgage,Taxes(real),Home Transportation(real),Home Maintenance(real),Home Costs Total(real),Home Value(real), "
               "Rent(real), RentTransportation, RentCost"<<std::endl;


  for (int years = 1; years <= rentYears; years++) {

    home = HomeBuyingCalculations(homeTransportation, homeValue, loanInterest, loanTerm, appreciation,
                                  propertyTax, loanAmount, years);
    rent = RentingCalculations(years, yearlyRent, rentTransportation);
    homeInvestment = homeInvestmentCalc(rent.at(1), home.at(6), inflation, returnRate,years, last_year_value);
    std::cout << years <<", ";

    std::cout << "Home Values: ";
    for (int i = 0; i < 6; i++) {
      std::cout << home.at(i)<<", ";
    }
    std::cout << "Investment Values: ";
    std::cout << round(homeInvestment.at(0)) << ", ";

    std::cout << "Rent Values: ";
    std::cout << yearlyRent << ", ";
    std::cout << rentTransportation << ", ";

    std::cout << rent.at(0)<<", ";



    last_year_value = homeInvestment.at(0);


    std::cout << "\n";
  }
  outputFile.close();
}

std::vector<double> homeInvestmentCalc( double yearlyRentDifference, double yearlyHomeDifference, double inflation, double investmentRate, double years, double last_year_value){
  double diff;
  double contribution;
  double homeinvestPerMonth = 0;
  double homeinvest;
  double first_year;
  std::vector<double> investValues;
  std::vector<double> investment;
  yearlyRentDifference = 15840;

  if (yearlyRentDifference > yearlyHomeDifference) {
    diff = yearlyRentDifference - yearlyHomeDifference;

    contribution = diff / 12;
    for (int i = 1; i <= 12; i++) {
      homeinvestPerMonth += contribution;
      homeinvestPerMonth *= (1 + investmentRate / 12);
    }

  }
  //else {homeinvestPerMonth = 0;}


  for (int j = 1; j <= years; j++) {
    if (j==1){
      homeinvest = 1682.21;
      first_year = homeinvest;
    }

    if (j>1){

      homeinvest = (last_year_value*(pow(1+investmentRate/12,12))/(1+inflation)) ;


      first_year = homeinvest+homeinvestPerMonth;

    }

    investValues.push_back(first_year);

  }
  investment.push_back(first_year);
  return investment;

}
//std::vector<double> rentInvestmentCalc(double yearlyRent, double currentYearTotal, double inflation, double investmentRate, double years){
//    double diff;
//    double contribution;
//    double rentinvestPerMonth =0;
//    double rentinvest;
//
//    std::vector<double> investment;
//    yearlyRent = 15840;
//
//    if (currentYearTotal> yearlyRent) {
//        diff = currentYearTotal - yearlyRent ;
////        std::cout << "currentYearTotal:" << currentYearTotal << std::endl;
//        contribution = diff / 12;
//        for (int i = 1; i <= 12; i++) {
//            rentinvestPerMonth += contribution;
//            rentinvestPerMonth *= (1 + investmentRate / 12);
//        }


std::vector<double> RentingInfo() {
  double monthlyRent;
  double returnRate;
  double transportation;
  double yearlyRent;
  double inflationRate;
  double years;

  std::vector<double> values;

  std::cout << "Enter your monthly rent payment: ";
  std::cin >> monthlyRent;
  yearlyRent = (12 * monthlyRent);

  std::cout << "Enter your expected annual average rate of return on your investments: ";
  std::cin >> returnRate;

  transportation = round(CommuteFromApartment());

  std::cout << "Enter the expected average yearly inflation rate: ";
  std::cin >> inflationRate;

  std::cout << "Enter how many years in the future you want to look: ";
  std::cin >> years;

  values.push_back(years);
  values.push_back(yearlyRent);
  values.push_back(transportation);
  values.push_back(inflationRate);
  values.push_back(returnRate);

  return values;

}

std::vector<double> RentingCalculations(double years, double yearlyRent, double transportation){
  double totalCost = 0;
  std::vector<double> rent;
  //rent.push_back(yearlyRent);
  //rent.push_back(transportation);

  for(int i = 1; i <= years; i++) {
    totalCost = totalCost + transportation + yearlyRent;
  }
  rent.push_back(totalCost);
  rent.push_back(transportation + yearlyRent);
  //std::cout << totalCost << std::endl;

  return rent;
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

//int writingfile(){
//    std::ofstream outputFile;
//    outputFile.open("demofile.txt");
//
//    std::cout<<"Now writing data to the file. \n";
//
//    // Write four names to the file
//    outputFile<< "Bach\n" ;
//    outputFile<< "hey\n" ;
//    outputFile<< "sup\n" ;
//    outputFile<< "yo\n" ;
//
//    // Close the file
//    outputFile.close();
//    std::cout <<"Done.\n";
//    return 0;
//}