#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <chrono>

// Define the Contact structure
struct Contact {
    std::string name;
    std::string phoneNumber;
    std::string email;
    std::string city;

    // Comparison operator for sorting in std::map
    bool operator<(const Contact& other) const {
        return name < other.name; // Sort alphabetically by name
    }
};

// Custom hash function for Contact
struct ContactHash {
    std::size_t operator()(const Contact& contact) const {
        return std::hash<std::string>()(contact.name) ^ 
               std::hash<std::string>()(contact.phoneNumber);
    }
};

// Custom equality function for Contact
struct ContactEqual {
    bool operator()(const Contact& lhs, const Contact& rhs) const {
        return lhs.name == rhs.name && lhs.phoneNumber == rhs.phoneNumber;
    }
};

int main() {
    // ✅ Basic std::map operations
    std::map<std::string, Contact> contactList;

    contactList["Alice"] = {"Alice", "123-456-7890", "alice@example.com", "New York"};
    contactList["Bob"] = {"Bob", "987-654-3210", "bob@example.com", "Los Angeles"};
    contactList["Charlie"] = {"Charlie", "555-555-5555", "charlie@example.com", "Chicago"};
    contactList["David"] = {"David", "111-222-3333", "david@example.com", "New York"};

    std::cout << "Basic map operations:\n";
    for (const auto& [name, contact] : contactList) {
        std::cout << name << ": " << contact.phoneNumber << ", " << contact.city << "\n";
    }

    // ✅ Using lower_bound and upper_bound
    std::cout << "\nUsing lower_bound and upper_bound:\n";
    auto lower = contactList.lower_bound("Bob");
    auto upper = contactList.upper_bound("Charlie");
    
    std::cout << "Contacts from 'Bob' to 'Charlie':\n";
    for (auto it = lower; it != upper; ++it) {
        std::cout << it->first << ": " << it->second.phoneNumber << "\n";
    }

    // ✅ Range-based erase in map
    contactList.erase(contactList.find("Bob"), contactList.find("David"));
    std::cout << "\nAfter range-based erase (Bob to David):\n";
    for (const auto& [name, contact] : contactList) {
        std::cout << name << ": " << contact.phoneNumber << "\n";
    }

    // ✅ Using custom struct as key in unordered_map with custom hash function
    std::unordered_map<Contact, std::string, ContactHash, ContactEqual> contactCities;
    
    contactCities[{"Alice", "123-456-7890", "alice@example.com", "New York"}] = "New York";
    contactCities[{"Bob", "987-654-3210", "bob@example.com", "Los Angeles"}] = "Los Angeles";

    std::cout << "\nCustom struct as key in unordered_map:\n";
    for (const auto& [contact, city] : contactCities) {
        std::cout << contact.name << ": " << city << "\n";
    }

    // ✅ Bucket information in unordered_map
    std::cout << "\nBucket information:\n";
    std::cout << "Bucket count: " << contactCities.bucket_count() << "\n";
    std::cout << "Bucket of Alice: " << 
        contactCities.bucket({"Alice", "123-456-7890", "alice@example.com", "New York"}) << "\n";

    // ✅ Comparing iteration order of map vs unordered_map
    std::map<std::string, std::string> orderedCities;
    std::unordered_map<std::string, std::string> unorderedCities;

    orderedCities["Charlie"] = "Chicago";
    orderedCities["Alice"] = "New York";
    orderedCities["Bob"] = "Los Angeles";

    unorderedCities["Charlie"] = "Chicago";
    unorderedCities["Alice"] = "New York";
    unorderedCities["Bob"] = "Los Angeles";

    std::cout << "\nOrdered map iteration:\n";
    for (const auto& [name, city] : orderedCities) {
        std::cout << name << ": " << city << "\n";
    }

    std::cout << "\nUnordered map iteration:\n";
    for (const auto& [name, city] : unorderedCities) {
        std::cout << name << ": " << city << "\n";
    }

    // ✅ Comparing performance of map vs unordered_map
    const int N = 100000;
    std::map<std::string, Contact> perfMap;
    std::unordered_map<std::string, Contact> perfUnorderedMap;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        perfMap[std::to_string(i)] = {"Contact" + std::to_string(i), "123-456-7890", "email@example.com", "City"};
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "\nTime to insert " << N << " elements in map: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        perfUnorderedMap[std::to_string(i)] = {"Contact" + std::to_string(i), "123-456-7890", "email@example.com", "City"};
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time to insert " << N << " elements in unordered_map: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms\n";

    return 0;
}
