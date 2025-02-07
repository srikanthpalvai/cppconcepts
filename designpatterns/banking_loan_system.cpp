#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>

using namespace std;

// Forward Declarations
class Loan;
class Observer;

// Observer Pattern (Tracking Interest Rate Changes)
class Observer {
public:
    virtual void update(string loanType, double newRate) = 0;
};

class Loan {
protected:
    string loanType;
    double interestRate;
    vector<Observer*> observers;
public:
    Loan(string type, double rate) : loanType(type), interestRate(rate) {}
    virtual double getInterestRate() { return interestRate; }
    string getLoanType() { return loanType; }
    void addObserver(Observer* obs) { observers.push_back(obs); }
    void notifyObservers() {
        for (auto obs : observers) {
            obs->update(loanType, interestRate);
        }
    }
    void setInterestRate(double rate) {
        interestRate = rate;
        notifyObservers();
    }
};

// Concrete Loan Types
class HomeLoan : public Loan { public: HomeLoan(double rate) : Loan("Home Loan", rate) {} };
class PersonalLoan : public Loan { public: PersonalLoan(double rate) : Loan("Personal Loan", rate) {} };
class CarLoan : public Loan { public: CarLoan(double rate) : Loan("Car Loan", rate) {} };

// Factory Method for Loan Creation
class LoanFactory {
public:
    static unique_ptr<Loan> createLoan(string type, double rate) {
        if (type == "Home") return make_unique<HomeLoan>(rate);
        if (type == "Personal") return make_unique<PersonalLoan>(rate);
        if (type == "Car") return make_unique<CarLoan>(rate);
        return nullptr;
    }
};

// Singleton for Bank Registry
class BankRegistry {
private:
    static BankRegistry* instance;
    map<string, vector<unique_ptr<Loan>>> banks;
    BankRegistry() {}
public:
    static BankRegistry* getInstance() {
        if (!instance) instance = new BankRegistry();
        return instance;
    }
    void addBank(string bankName, unique_ptr<Loan> loan) {
        banks[bankName].push_back(move(loan));
    }
    void showBanks() {
        for (auto& bank : banks) {
            cout << "Bank: " << bank.first << endl;
            for (auto& loan : bank.second) {
                cout << "  " << loan->getLoanType() << " - " << loan->getInterestRate() << "% " << endl;
            }
        }
    }
    Loan* getLoan(string bankName, int index) {
        return banks[bankName][index].get();
    }
};
BankRegistry* BankRegistry::instance = nullptr;

// Strategy Pattern (Different Interest Rate Calculations)
class InterestRateStrategy {
public:
    virtual double calculateRate(double baseRate) = 0;
};

class FixedRateStrategy : public InterestRateStrategy {
public:
    double calculateRate(double baseRate) override { return baseRate; }
};

class FloatingRateStrategy : public InterestRateStrategy {
public:
    double calculateRate(double baseRate) override { return baseRate + 0.5; }
};

class HybridRateStrategy : public InterestRateStrategy {
public:
    double calculateRate(double baseRate) override { return baseRate + 0.25; }
};

// Decorator Pattern (Adding Discounts and Extra Charges)
class LoanDecorator : public Loan {
protected:
    unique_ptr<Loan> baseLoan;
public:
    LoanDecorator(unique_ptr<Loan> loan) : Loan(loan->getLoanType(), loan->getInterestRate()), baseLoan(move(loan)) {}
    virtual double getInterestRate() override { return baseLoan->getInterestRate(); }
};

class DiscountDecorator : public LoanDecorator {
public:
    DiscountDecorator(unique_ptr<Loan> loan) : LoanDecorator(move(loan)) {}
    double getInterestRate() override { return baseLoan->getInterestRate() - 0.5; }
};

class ExtraChargeDecorator : public LoanDecorator {
public:
    ExtraChargeDecorator(unique_ptr<Loan> loan) : LoanDecorator(move(loan)) {}
    double getInterestRate() override { return baseLoan->getInterestRate() + 0.75; }
};

// Observer Implementation
class InterestRateTracker : public Observer {
public:
    void update(string loanType, double newRate) override {
        cout << "[ALERT] " << loanType << " interest rate changed to " << newRate << "%\n";
    }
};

// Command Pattern (Undo/Redo Interest Rate Changes)
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class ChangeInterestRateCommand : public Command {
private:
    Loan* loan;
    double oldRate, newRate;
public:
    ChangeInterestRateCommand(Loan* l, double newRate) : loan(l), newRate(newRate) {
        oldRate = l->getInterestRate();
    }
    void execute() override { loan->setInterestRate(newRate); }
    void undo() override { loan->setInterestRate(oldRate); }
};

int main() {
    BankRegistry* registry = BankRegistry::getInstance();
    InterestRateTracker tracker;
    
    auto iciciHomeLoan = LoanFactory::createLoan("Home", 8.75);
    iciciHomeLoan->addObserver(&tracker);
    
    auto hdfcPersonalLoan = LoanFactory::createLoan("Personal", 10.85);
    hdfcPersonalLoan->addObserver(&tracker);
    
    registry->addBank("ICICI", move(iciciHomeLoan));
    registry->addBank("HDFC", move(hdfcPersonalLoan));
    registry->showBanks();
    
    // Change Interest Rate using Command Pattern
    auto command = make_unique<ChangeInterestRateCommand>(registry->getLoan("ICICI", 0), 9.0);
    command->execute(); // Update rate
    command->undo(); // Undo change
    
    return 0;
}
