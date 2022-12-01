//#include <iostream>
//#include <cassert>
//using namespace std;
//
//// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
//// COMMENT AT THE END OF THE process FUNCTION
//
//int* process(int* first, int* last, int* numNegatives){
//    int maxValue = *first;
//    int* ptrToMax = first;
//    int negCount = 0;
//    for (int* ptr=first; ptr<last+1; ptr++){
//        if (*ptr >= maxValue){
//            maxValue = *ptr;
//            ptrToMax = ptr;
//        }
//        if (*ptr<0){
//            negCount++;
//        }
//    }
//    if (numNegatives != nullptr){
//        *numNegatives = negCount;
//    }
//    return ptrToMax;
//}
//
//// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
//// COMMENT AT THE START OF THE process FUNCTION
//
//int main()
//{
//    int a[9] = { 17, -5, 42, -12, -40, 27, 0, 42, 37 };
//    int negatives = 999;
//    assert(process(a, a+3, &negatives) == a+2  &&  negatives == 2);
//    assert(process(a+5, a+8, &negatives) == a+7  &&  negatives == 0);
//    negatives = 999;
//    assert(process(a, a+3, nullptr) == a+2  &&  negatives == 999);
//    assert(process(a, a+8, &negatives) == a+7  &&  negatives == 3);
//    assert(process(a+1, a+1, &negatives) == a+1  &&  negatives == 1);
//    assert(process(a, a, &negatives) == a  &&  negatives == 0);
//
//    cout << "All tests succeeded" << endl;
//}

//  Dispenser();
    // A Dispenser has a capacity of 130 gallons and has no water
    // in it when created.
//   int addWater(int num);
    // Attempt to add num gallons of water to the dispenser, but
    // don't fill the dispenser beyond its capacity.  The function
    // returns the number of gallons actually added, which will be
    // less than the requested number if adding that many gallons
    // would overfill the dispenser.
 // bool dispenseWater();
    // Attempt to dispense one gallon of water from the dispenser
    // (e.g., to dispense to a customer).  If the dispenser is
    // empty, simply returns false; otherwise, remove one gallon
    // of water from the dispenser and returns true.
  
#include <iostream>
#include <cassert>
using namespace std;

class Dispenser
{
  public:
    Dispenser();
    int addWater(int num);
    bool dispenseWater();
  private:
    int m_numGallons;
    int m_capacity;
};
    
Dispenser::Dispenser()
{
    m_numGallons = 0;
    m_capacity = 130;
}

int Dispenser::addWater(int num)
{
    if (num <= 0)
        return 0;
    if (m_numGallons + num > m_capacity)
        num = m_capacity - m_numGallons;
    m_numGallons += num;
    return num;
}
    
bool Dispenser::dispenseWater()
{
    if (m_numGallons == 0)
        return false;
    m_numGallons--;
    return true;
}

//The class you will implement is named VendingMachine and represents a vending machine. Every VendingMachine has a Dispenser. Every vending machine has a price that it charges per gallon of water. When a customer puts money into a vending machine, it dispenses as many whole gallons as that money can buy, and returns any change. (For example, if the price is 0.30 per gallon and you deposit 1.05, the vending machine will dispense 3 gallons and return 0.15 in change, keeping 0.90.) The VendingMachine class has the following interface:
//
//A constructor that takes two parameters: a double representing the price per gallon, and an int specifying the whole number of gallons that the vending machine is to start with in its dispenser. You may assume the price is guaranteed to be positive and the initial number of gallons is nonnegative and no more than 130 (i.e., you won’t have to check for this).
//An addWater member function that accepts the whole number of gallons to attempt to add to the vending machine’s dispenser. The function adds water to the dispenser and returns the number of gallons actually added, which will be less than the requested number if the dispenser becomes full to capacity. You may assume the parameter is guaranteed to be nonnegative (i.e., you won’t have to check for this).
//A purchase member function that accepts a parameter of type double representing the amount of money the customer puts into the machine. The function causes the VendingMachine’s dispenser to dispense the appropriate number of gallons of water and returns a double: the amount of change the customer should receive. If the money would buy more water than there is in the dispenser, the dispenser should deliver all of its water, and the customer should get the appropriate amount of change for the number of gallons delivered. You may assume the parameter is guaranteed to be nonnegative (i.e., you won’t have to check for this).
//A moneyRetained member function that takes no parameters and returns a double: the total amount of customers' money kept by the VendingMachine since it was created.

class VendingMachine
{
  public:
    VendingMachine(double price, int startAmount);
    int addWater(int num);
    double purchase(double amt);
    double moneyRetained() const;
  private:
    Dispenser m_dispenser;
    double    m_price;
    double    m_totalMoneyKept;
};

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE END OF THE VENDINGMACHINE MEMBER FUNCTIONS

VendingMachine::VendingMachine(double price, int startAmount){
    m_dispenser.addWater(startAmount);
    m_price = price;
    m_totalMoneyKept = 0;
}

int VendingMachine::addWater(int num){
    return m_dispenser.addWater(num);
}

double VendingMachine::purchase(double amt){
    int dispenseAmtGallons = amt/m_price;
    
    bool keepGoing = m_dispenser.dispenseWater();
    if (keepGoing == true){
        dispenseAmtGallons--;
        keepGoing = m_dispenser.dispenseWater();    //this is the line that u forgot! :(
    }
    while (keepGoing == true && dispenseAmtGallons != 0){
        keepGoing = m_dispenser.dispenseWater();
        dispenseAmtGallons--;
    }
    
    if (dispenseAmtGallons == 0){
        m_totalMoneyKept += amt;
        return fmod(amt, m_price);
    } else {
        m_totalMoneyKept += amt - (fmod(amt, m_price) + (dispenseAmtGallons * m_price));
        return fmod(amt, m_price) + (dispenseAmtGallons * m_price);
    }
}

double VendingMachine::moneyRetained() const{
    return m_totalMoneyKept;
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE START OF THE VENDINGMACHINE MEMBER FUNCTIONS


VendingMachine* createVM(){
    VendingMachine* ptr = new VendingMachine(.35, 130);
    ptr->purchase(14.00);
    return ptr;
}

int main()
{
    VendingMachine vm(0.50, 3);
    assert(vm.addWater(7) == 7);
    assert(vm.purchase(5.75) == 0.75);
    assert(vm.moneyRetained() == 5.00);

    cout << "All tests succeeded" << endl;
}
