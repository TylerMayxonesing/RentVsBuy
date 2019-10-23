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
    RunRentVsBuy();
    PrintFile(std::cout, "RentVsBuy.csv");
    return 0;
}
