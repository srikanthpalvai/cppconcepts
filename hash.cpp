#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

struct DeviceInfo{
    string name;
    int id;
    bool operator==(const DeviceInfo & other) const{
        return (name == other.name && id == other.id);
    }
};

// Define custom hash fucntion for DeviceInfo
struct DeviceInfoHash {

    size_t operator() (const DeviceInfo& device) const{
        //✅ << 1 helps reduce hash collisions by ensuring device.id contributes more meaningfully.
        return hash<string>{}(device.name) ^ (hash<int>{}(device.id) << 1);
    }   
};

// Defince custom equality comparator for the DeviceInfo
struct DeviceInfoEq {
    bool operator() (const DeviceInfo& lhs, const DeviceInfo& rhs) const {
        return lhs.name == rhs.name && lhs.id == rhs.id;
    }
};

using DeviceInfoRegistry  =  unordered_set<DeviceInfo, DeviceInfoHash, DeviceInfoEq>;

int main() {
    // Define a list of strings, including "apple" and "elppa" (reverse of apple)
    string arr[] = {"apple", "banana", "orange", "apple", "grape", "banana", "elppa"};

    // Create an unordered_set to store the unique hashes (size_t to hold hash values)
    unordered_set<size_t> hashSizeSet;

    // Loop through the array of strings
    for (const string& item : arr) {
        // Compute the hash value of the current string using std::hash
        size_t hashValue = hash<string>{}(item);

        // Check if this hash already exists in the set (duplicate detection)
        auto [it, inserted] = hashSizeSet.insert(hashValue); // structured binding (C++17)

        if (!inserted) {
            cout << " --> Collision detected (duplicate hash) for: " << item << endl;
        } else {
            cout << "Unique item: " << item << endl;
        }
    }


    unordered_set<std::string> hashStringSet;
    
    for(const string& item : arr) {
        // compute teh hash value of teh current string using the std::hash
        ssize_t hashValue = hash<string>{}(item);

        auto [it, inserted] = hashStringSet.insert(item);

        if(!inserted) {
            cout << " --> Collision detected (duplicate hash) for: " << item << endl;
        } else {
            cout << "Unique item: " << item << endl;
        }
    }

    {
        // Uniform Initialization
        DeviceInfoRegistry devices ={{"ESP32", 1}, {"STM32", 2}, {"Fibcom", 3}, {"nRF", 3}};
        cout << devices.size() << endl;
        devices.insert({"ESP32", 1});
        cout << devices.size() << endl;
    }

    {
        //✅ it and inserted come from std::pair<iterator, bool> returned by insert().
        //✅ Using auto simplifies structured bindings (C++17) instead of writing std::pair<> explicitly.

        DeviceInfoRegistry devices;
        if (auto [it, inserted] = devices.insert({"rPI", 123}); inserted ) {
            cout << "Successfully Inserted" << endl;
        } else {
            cout << "Already Exist" << endl;
        }

        // What if you dont use the structed binding
        std::pair<DeviceInfoRegistry::iterator, bool> result = devices.insert({"Tinker", 456}); 
        DeviceInfoRegistry::iterator it = result.first;
        cout << "Name: "<< it->name << endl;
        cout << "ID:" << it->id << endl;
        bool inserted = result.second;
        cout << "Inserted: " << inserted << endl;

        // If you want to remove the item 
        devices.erase(it);

        for (auto [name, id] : devices) {
            cout << "Name: " << name << endl;
            cout << "ID: " << id << endl;
        }

    }

    return 0;
}
