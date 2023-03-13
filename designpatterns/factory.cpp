/*The basic thumb rules of the Factory Design Pattern are:

Define an interface for creating an object, but let the subclasses decide which class to instantiate.
The Factory method lets a class defer instantiation to subclasses.
Encapsulate object creation in a separate component.
Use a Factory class to create objects.
Advantages of the Factory Design Pattern are:

Provides a way to create objects without exposing the creation logic to the client.
Allows the client code to be more modular and less coupled to the concrete classes.
Makes it easy to add new types of objects without changing the existing code.
Centralizes object creation code, making it easier to maintain and modify.
Disadvantages of the Factory Design Pattern are:

The creation of objects can be more complex than simply calling a constructor, which can lead to more code and complexity in the Factory classes.
The Factory classes can become a bottleneck if they are responsible for creating many different types of objects.
Introducing new types of objects may require modifying the Factory classes.
The Factory Design Pattern can increase the number of classes in a codebase, which can make it harder to understand and maintain the code.
*/
#include <iostream>
#include <memory>
#include <stdexcept>

// Enum for Transaction Types
enum class TransactionType { Sale, Void, Refund, Preauth, Settlement, Authorization };

// Abstract class for Transaction
class Transaction {
public:
    virtual ~Transaction() {}
    virtual TransactionType getType() const = 0;
    virtual void process() = 0;
};

// Concrete implementation of Transaction for Sale
class SaleTransaction : public Transaction {
public:
    SaleTransaction(int amount) : m_amount(amount) {}
    TransactionType getType() const { return TransactionType::Sale; }
    void process() { /* Process Sale transaction */ }
private:
    int m_amount;
};

// Concrete implementation of Transaction for Void
class VoidTransaction : public Transaction {
public:
    VoidTransaction(int transactionId) : m_transactionId(transactionId) {}
    TransactionType getType() const { return TransactionType::Void; }
    void process() { /* Process Void transaction */ }
private:
    int m_transactionId;
};

// Concrete implementation of Transaction for Refund
class RefundTransaction : public Transaction {
public:
    RefundTransaction(int transactionId, int amount) : m_transactionId(transactionId), m_amount(amount) {}
    TransactionType getType() const { return TransactionType::Refund; }
    void process() { /* Process Refund transaction */ }
private:
    int m_transactionId;
    int m_amount;
};

// Concrete implementation of Transaction for Preauth
class PreauthTransaction : public Transaction {
public:
    PreauthTransaction(int amount) : m_amount(amount) {}
    TransactionType getType() const { return TransactionType::Preauth; }
    void process() { /* Process Preauth transaction */ }
private:
    int m_amount;
};

// Concrete implementation of Transaction for Settlement
class SettlementTransaction : public Transaction {
public:
    SettlementTransaction() {}
    TransactionType getType() const { return TransactionType::Settlement; }
    void process() { /* Process Settlement transaction */ }
};


// Transaction factory
class TransactionFactory {
public:
    TransactionFactory() = default; // Default constructor
    TransactionFactory(const TransactionFactory& other) = default; // Copy constructor
    TransactionFactory& operator=(const TransactionFactory& other) = default; // Copy assignment operator
    TransactionFactory(TransactionFactory&& other) = default; // Move constructor
    TransactionFactory& operator=(TransactionFactory&& other) = default; // Move assignment operator
    ~TransactionFactory() = default; // Default destructor

    static std::unique_ptr<Transaction> createTransaction(TransactionType type, int transactionId = -1, int amount = -1) {
        switch (type) {
            case TransactionType::Sale:
                return std::make_unique<SaleTransaction>(amount);
            case TransactionType::Void:
                return std::make_unique<VoidTransaction>(transactionId);
            case TransactionType::Refund:
                if (transactionId == -1 || amount == -1) {
                    throw std::runtime_error("Invalid transaction parameters");
                }
                return std::make_unique<RefundTransaction>(transactionId, amount);
            case TransactionType::Preauth:
                return std::make_unique<PreauthTransaction>(amount);
            case TransactionType::Settlement:
                return std::make_unique<SettlementTransaction>();
			default:
				 throw std::invalid_argument("Invalid transaction type");
		}
	}
};

int main(){
	
	 try{
		std::unique_ptr<Transaction> txn = TransactionFactory::createTransaction(TransactionType::Sale, -1, 100);
		std::cout << static_cast<int>(txn->getType()) << std::endl;
	 }catch(std::exception &ex){
		 std::cerr << "Error: " << ex.what() << std::endl;
	 }
	 return 0;
}