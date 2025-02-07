#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <functional>
using namespace std;

// Observer Pattern: Interface for Interest Rate Observers
class InterestRateObserver {
public:
    virtual void onInterestRateChanged(double newRate) = 0;
};

// Strategy Pattern: Interest Rate Strategy
class InterestRateStrategy {
public:
    virtual double calculateInterestRate() = 0;
    virtual ~InterestRateStrategy() = default;
};

class FixedRateStrategy : public InterestRateStrategy {
    double fixedRate;
public:
    FixedRateStrategy(double rate) : fixedRate(rate) {}
    double calculateInterestRate() override { return fixedRate; }
};

// Base Loan Class (Virtual Inheritance to Avoid Diamond Problem)
class Loan {
protected:
    string loanType;
    double interestRate;
    vector<InterestRateObserver*> observers;
    unique_ptr<InterestRateStrategy> rateStrategy;
public:
    Loan(string type, unique_ptr<InterestRateStrategy> strategy)
        : loanType(type), rateStrategy(move(strategy)) {
        interestRate = rateStrategy->calculateInterestRate();
    }

    virtual double getInterestRate() { return interestRate; }
    string getLoanType() { return loanType; }

    virtual void setInterestRate(double newRate) {
        interestRate = newRate;
        notifyObservers();
    }

    void addObserver(InterestRateObserver* observer) {
        observers.push_back(observer);
    }

    void notifyObservers() {
        for (auto observer : observers) {
            observer->onInterestRateChanged(interestRate);
        }
    }

    virtual ~Loan() = default;
};

// Bank Class (Observer Pattern)
class Bank : public InterestRateObserver {
private:
    string bankName;
public:
    Bank(string name) : bankName(name) {}

    void onInterestRateChanged(double newRate) override {
        cout << bankName << " Notified: Interest Rate Changed to " << newRate << "%" << endl;
    }

    string getBankName() { return bankName; }
};

// **Singleton Pattern: Bank Registry**
class BankRegistry {
private:
    BankRegistry() {}
    map<string, unique_ptr<Bank>> banks;

public:
    static BankRegistry& getInstance() {
        static BankRegistry instance;
        return instance;
    }

    void registerBank(string name) {
        if (banks.find(name) == banks.end())
            banks[name] = make_unique<Bank>(name);
    }

    Bank* getBank(string name) {
        return banks[name].get();
    }
};

// Factory Pattern: Bank Factory
class BankFactory {
public:
    static Bank* createBank(const string& bankName) {
        BankRegistry::getInstance().registerBank(bankName);
        return BankRegistry::getInstance().getBank(bankName);
    }
};

// Loan Types (Virtual Inheritance for Hybrid Inheritance)
class BusinessLoan : virtual public Loan {
public:
    BusinessLoan(unique_ptr<InterestRateStrategy> strategy)
        : Loan("Business Loan", move(strategy)) {}
};

class PersonalLoan : virtual public Loan {
public:
    PersonalLoan(unique_ptr<InterestRateStrategy> strategy)
        : Loan("Personal Loan", move(strategy)) {}
};

class AgricultureLoan : virtual public Loan {
public:
    AgricultureLoan(unique_ptr<InterestRateStrategy> strategy)
        : Loan("Agriculture Loan", move(strategy)) {}
};

// MultiLoan (Hybrid Inheritance)
class MultiLoan : public BusinessLoan, public PersonalLoan {
public:
    MultiLoan(unique_ptr<InterestRateStrategy> strategy)
        : Loan("MultiLoan", move(strategy)), BusinessLoan(move(strategy)), PersonalLoan(move(strategy)) {}

    void displayLoanDetails() {
        cout << "Loan Type: " << getLoanType() << " | Interest Rate: " << getInterestRate() << "%" << endl;
    }
};

// **Factory Pattern: Loan Factory**
class LoanFactory {
public:
    static unique_ptr<Loan> createLoan(string type, double rate) {
        static map<string, function<unique_ptr<Loan>(double)>> loanCreators = {
            {"Business", [](double r) { return make_unique<BusinessLoan>(make_unique<FixedRateStrategy>(r)); }},
            {"Personal", [](double r) { return make_unique<PersonalLoan>(make_unique<FixedRateStrategy>(r)); }},
            {"Agriculture", [](double r) { return make_unique<AgricultureLoan>(make_unique<FixedRateStrategy>(r)); }},
            {"MultiLoan", [](double r) { return make_unique<MultiLoan>(make_unique<FixedRateStrategy>(r)); }}
        };
        return (loanCreators.count(type)) ? loanCreators[type](rate) : nullptr;
    }
};

// **Command Pattern for Interest Rate Changes**
class ChangeInterestRateCommand {
private:
    Loan* loan;
    double newRate;
public:
    ChangeInterestRateCommand(Loan* loan, double rate) : loan(loan), newRate(rate) {}

    void execute() {
        loan->setInterestRate(newRate);
    }
};

// Main Function
int main() {
    // **Creating Banks using BankFactory**
    Bank* icici = BankFactory::createBank("ICICI Bank");
    Bank* hdfc = BankFactory::createBank("HDFC Bank");
    Bank* sbi = BankFactory::createBank("SBI Bank");

    // **Creating Loans using LoanFactory**
    auto businessLoan = LoanFactory::createLoan("Business", 9.5);
    auto personalLoan = LoanFactory::createLoan("Personal", 7.5);
    auto agricultureLoan = LoanFactory::createLoan("Agriculture", 6.0);

    // **Banks Observing Loan Interest Changes**
    businessLoan->addObserver(icici);
    businessLoan->addObserver(hdfc);
    agricultureLoan->addObserver(sbi);

    // **Display Initial Loan Details**
    cout << "Initial Loan Rates:\n";
    cout << businessLoan->getLoanType() << " - " << businessLoan->getInterestRate() << "%\n";
    cout << personalLoan->getLoanType() << " - " << personalLoan->getInterestRate() << "%\n";
    cout << agricultureLoan->getLoanType() << " - " << agricultureLoan->getInterestRate() << "%\n";

    // **Updating Interest Rate (Triggers Observer Notification)**
    cout << "\nUpdating Interest Rate...\n";
    ChangeInterestRateCommand command(businessLoan.get(), 10.0);
    command.execute();

    return 0;
}
