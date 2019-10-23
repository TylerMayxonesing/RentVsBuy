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

  std::cout << "==== Home Buying Information ===="<<std::endl;
  std::cout << "Enter the purchase price of the home: ";
  std::cin >> homeValue;

  std::cout << "Enter your down payment: ";
  std::cin >> downPayment;

  loanAmount = homeValue - downPayment;

  //std::cout << "Enter the interest rate on your loan: ";
  //std::cin >> loanInterest;

  //std::cout << "Enter the term of your loan: ";
  //std::cin >> loanTerm;

  std::cout << "Enter the property tax rate of the home: ";
  std::cin >> propertyTax;

  std::cout << "Enter the rate at which you expect your home to appreciate each year: ";
  std::cin >> appreciation;

  transportation = CommuteFromHome();

  values.push_back(transportation);
  values.push_back(homeValue);
  values.push_back(0);
  values.push_back(0);
  values.push_back(appreciation);
  values.push_back(propertyTax);
  values.push_back(loanAmount);
  values.push_back(downPayment);

  return values;

}


std::vector<double> HomeBuyingCalculations(double transportation,double homeValue, double loanInterest,
                                           double loanTerm, double appreciation,double propertyTax, double loanAmount, int years, double downPayment) {

  std::vector<double> home;
  double taxes;
  double realTax;
  double totalCost = 0;
  double mortgage;
  double realHomeValue;
  double currentYearTotal;
  double difference;


  mortgage = 12. * (loanAmount * (loanInterest / 12.) * pow((1. + (loanInterest / 12.)), (12. * loanTerm)))
      / (pow((1. + (loanInterest / 12.)), (12. * loanTerm)) - 1.);

  taxes = propertyTax*homeValue;
  double maintenance = 0.01 * homeValue;
  double purchasePrice = homeValue;

  home.push_back(0);
  home.push_back(0);
  home.push_back(transportation);
  home.push_back(maintenance);
  home.push_back(0);
  home.push_back(0);
  home.push_back(0);

  for (int j = 1; j <= years; j++) {

    home.at(0) = mortgage;
    realTax = (taxes* pow (1 + (appreciation / 12) , 12 * (j - 1)))/ (pow(1+(0.035),j-1));
    for (int i = 1; i <= 12; i++) {
      loanAmount = loanAmount * (1. + (loanInterest / 12.));
      loanAmount = loanAmount - (mortgage / 12.);
      homeValue = homeValue * (1. + (appreciation / 12.));
    }
    home.at(1) = realTax;
    totalCost = totalCost + maintenance + transportation + realTax + (mortgage / (pow((1. + (loanInterest)), j - 1.)));
    currentYearTotal = maintenance + transportation + realTax + (mortgage / (pow((1. + (loanInterest)), j - 1.)));
    downPayment = downPayment - (mortgage/ (pow((1. + (loanInterest)), j - 1.)));
    if (downPayment <=0){
      mortgage = 0;
    }

    home.at(6) = currentYearTotal;
    double nominal = homeValue - loanAmount;
    realHomeValue = nominal / (pow(1+(0.035),j-1));
  }
  home.at(4) = totalCost;
  home.at(5) = realHomeValue;
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
  std::vector <double> rentInvestment;

  std::vector<double> homeValues = HomeBuyingInfo();
  std::vector<double> rentValues = RentingInfo();
  double last_year_value = 0;
  double last_year_value_rent = 0;
  double homeProfit;
  double homeGross;
  double rentGross;
  double difference;

  double homeTransportation = homeValues.at(0);
  double homeValue = homeValues.at(1);
  double loanInterest = homeValues.at(2);
  double loanTerm = homeValues.at(3);
  double appreciation = homeValues.at(4);
  double propertyTax = homeValues.at(5);
  double loanAmount = homeValues.at(6);
  double downPayment = homeValues.at(7);

  double rentYears = rentValues.at(0);
  double yearlyRent = rentValues.at(1);
  double rentTransportation = rentValues.at(2);
  double inflation = rentValues.at(3);
  double returnRate = rentValues.at(4);



  outputFile << "Year,Mortgage,Taxes(real),Home Transportation(real),Home Maintenance(real),Home Costs Total(real),Home Value(real),Home Investments Total(real),Home Profits(real),Home Gross(real),Rent(real),Rent Transportation, Rent Costs Total (real),Rent Investments Total(real),Rent Gross(real),Home Gross - Rent Gross(real),Better Option\n";


  for (int years = 1; years <= rentYears; years++) {

    home = HomeBuyingCalculations(homeTransportation, homeValue, inflation, rentYears, appreciation,
                                  propertyTax, loanAmount, years, downPayment);
    rent = RentingCalculations(years, yearlyRent, rentTransportation);

    homeInvestment = homeInvestmentCalc(rent.at(1), home.at(6), inflation, returnRate,years, last_year_value);
    rentInvestment = rentInvestmentCalc(rent.at(1), home.at(6), inflation, returnRate,years, last_year_value_rent, downPayment);
    last_year_value_rent = rentInvestment.at(0);

    outputFile << years <<",";

//    std::cout << "Home Values: ";
    for (int i = 0; i < 6; i++) {
      //std::cout << home.at(i)<<", ";
      outputFile << round(home.at(i))<<",";
    }

    //std::cout << round(homeInvestment.at(0)) << ", ";
    outputFile << round(homeInvestment.at(0)) << ",";

    homeProfit = homeInvestment.at(0) + home.at(5);
    //std::cout << round (homeProfit) << ", ";
    outputFile << round (homeProfit) << ",";

    homeGross = homeProfit - home.at(4);
    //std::cout << homeGross << ", ";
    outputFile<< round(homeGross) << ",";

    //std::cout << yearlyRent << ", ";
    outputFile << round(yearlyRent) <<",";
    //std::cout << rentTransportation << ", ";
    outputFile << round(rentTransportation) << ",";

    //std::cout << rent.at(0)<<", ";
    outputFile << round(rent.at(0)) << ",";
    //std::cout << rentInvestment.at(0)<< ", ";
    outputFile<< round(rentInvestment.at(0))<<",";

    rentGross = rentInvestment.at(0) - rent.at(0);
    //std::cout << round(rentGross)<< ",";
    outputFile << round(rentGross) << ",";

    difference = homeGross - rentGross;
    outputFile<<round(difference)<<",";
    if (difference > 0){
      //std::cout << "Owning";
      outputFile <<"Owning";
    }
    else {
      //std::cout << "Renting";
      outputFile <<"Renting";
    }
    last_year_value = homeInvestment.at(0);
    outputFile << "\n";
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

std::vector<double> rentInvestmentCalc( double yearlyRent, double currentYearTotal, double inflation, double investmentRate, double years, double last_year_value_home, double downPayment){
  double diff;
  double contribution;
  double rentinvestPerMonth =0;
  double rentinvest;
  double first_year;
  std::vector<double> investValuesRent;
  std::vector<double> investmentRent;


  if (currentYearTotal> yearlyRent ) {
    diff =  currentYearTotal - yearlyRent;
    contribution = diff / 12;
    for (int i = 1; i <= 12; i++) {
      rentinvestPerMonth += contribution;
      rentinvestPerMonth *= (1 + investmentRate / 12);
    }}
  if (yearlyRent>currentYearTotal){
    rentinvestPerMonth = 0;
  }

  for (int j = 1; j <= years; j++) {
    if (j==1){
      first_year = downPayment* (pow(1+investmentRate/12,12));
    }

    if (j>1){

      rentinvest = (last_year_value_home*(pow(1+investmentRate/12,12))/(1+inflation)) ;
      first_year = rentinvest+rentinvestPerMonth;

    }

    investValuesRent.push_back(first_year);

  }
  investmentRent.push_back(first_year);
  return investmentRent;

}


std::vector<double> RentingInfo() {
  double monthlyRent;
  double returnRate;
  double transportation;
  double yearlyRent;
  double inflationRate;
  double years;

  std::vector<double> values;

  std::cout <<"==== Renting Information ===="<<std::endl;
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

  std::cout <<"==== Commute from apartment ===="<<std::endl;
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