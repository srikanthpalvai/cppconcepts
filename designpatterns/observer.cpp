#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <algorithm>

// Define the observer interface
class Observer {
public:
    virtual void notify(const std::string& stockSymbol, double price) = 0;
};

// Define the observable
class StockMarket {
public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }

    void setStockPrice(const std::string& stockSymbol, double price) {
        // Update the stock price and notify all observers
        stockPrices[stockSymbol] = price;
        for (Observer* observer : observers) {
            observer->notify(stockSymbol, price);
        }
    }

private:
    std::vector<Observer*> observers;
    std::unordered_map<std::string, double> stockPrices;
};

// Define the trader observer
class Trader : public Observer {
public:
    Trader(const std::string& name) : name(name) {}

    void notify(const std::string& stockSymbol, double price) override {
        // Print a message when the stock price changes
        std::cout << name << ": The price of " << stockSymbol << " has changed to " << price << std::endl;
    }

private:
    std::string name;
};

// Define the main function to demonstrate the Observer pattern with event-driven programming
int main() {
    // Create a stock market observable and add traders as observers
    StockMarket stockMarket;
    Trader trader1("Trader 1");
    Trader trader2("Trader 2");
    stockMarket.addObserver(&trader1);
    stockMarket.addObserver(&trader2);

    // Set the initial stock prices and simulate changes in stock prices
    stockMarket.setStockPrice("AAPL", 135.73);
    stockMarket.setStockPrice("MSFT", 231.60);
    stockMarket.setStockPrice("GOOGL", 2041.33);
    int i = 0;
    while (i < 5) {
        stockMarket.setStockPrice("AAPL", 135.74 + i);
        stockMarket.setStockPrice("MSFT", 231.61 + i);
        stockMarket.setStockPrice("GOOGL", 2041.34 + i);
        i++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Remove a trader observer and simulate more changes in stock prices
    stockMarket.removeObserver(&trader1);
    i = 0;
    while (i < 5) {
        stockMarket.setStockPrice("AAPL", 135.79 + i);
        stockMarket.setStockPrice("MSFT", 231.66 + i);
        stockMarket.setStockPrice("GOOGL", 2041.39 + i);
        i++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
