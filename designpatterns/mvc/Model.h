#pragma once

#include <vector>
#include <functional>
#include <memory>

class View;  // forward declaration

class Model {
public:
    void attach_view(std::shared_ptr<View> view);
    void set_data(int data);
private:
    std::vector<std::function<void(int)>> observers_;
    int data_{};
    void notify();
};
