#include <iostream>
#include <functional>
#include <vector>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <atomic>

class EventManager {
public:
    using CallbackID = size_t;  // Unique ID for each callback
    using Callback = std::function<void(const std::string&)>;

    // ✅ Register a callback and return its ID for later removal
    CallbackID registerCallback(Callback callback) {
        std::lock_guard<std::mutex> lock(mutex_);
        CallbackID id = ++lastID_;
        callbacks_[id] = std::move(callback);
        return id;
    }

    // ✅ Unregister a callback using its ID
    void unregisterCallback(CallbackID id) {
        std::lock_guard<std::mutex> lock(mutex_);
        callbacks_.erase(id);
    }

    // ✅ Notify all registered callbacks safely
    void notify(const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        for (const auto& [id, callback] : callbacks_) {
            if (callback) {
                callback(message);
            }
        }
    }

private:
    std::unordered_map<CallbackID, Callback> callbacks_;
    std::mutex mutex_;
    std::atomic<CallbackID> lastID_{0};  // Generate unique IDs
};

// ✅ UI Notification System
class UI {
public:
    void showNotification(const std::string& message) {
        std::cout << "[UI] Notification: " << message << std::endl;
    }
};

// ✅ Logger System
class Logger {
public:
    void logEvent(const std::string& message) {
        std::cout << "[Logger] Logged Event: " << message << std::endl;
    }
};

// ✅ SMS Alert System
class SMSNotifier {
public:
    void sendSMS(const std::string& message, const std::string& phoneNumber) {
        std::cout << "[SMS] Sending to " << phoneNumber << ": " << message << std::endl;
    }
};

int main() {
    EventManager eventManager;
    UI ui;
    Logger logger;
    SMSNotifier smsNotifier;

    // 🔗 Register UI notification callback
    auto uiCallbackID = eventManager.registerCallback(std::bind(&UI::showNotification, &ui));

    // 🔗 Register Logger callback
    auto loggerCallbackID = eventManager.registerCallback(std::bind(&Logger::logEvent, &logger));

    // 🔗 Register SMS alert with additional argument (phone number)
    auto smsCallbackID = eventManager.registerCallback(
        std::bind(&SMSNotifier::sendSMS, &smsNotifier, std::placeholders::_1, "+1234567890")
    );

    // 🔗 Register a Lambda function dynamically
    auto lambdaCallbackID = eventManager.registerCallback([](const std::string& msg) {
        std::cout << "[Lambda] Special Handling: " << msg << std::endl;
    });

    // 🚀 Fire an event (all callbacks execute)
    std::cout << "\n🔔 System Alert: 'Server Maintenance at 10 PM'\n";
    eventManager.notify("Server Maintenance at 10 PM");

    // ✅ Unregister Logger dynamically
    eventManager.unregisterCallback(loggerCallbackID);

    std::cout << "\n🚀 Logger Unregistered, Sending Another Event\n";
    eventManager.notify("New Security Patch Released");

    return 0;
}
