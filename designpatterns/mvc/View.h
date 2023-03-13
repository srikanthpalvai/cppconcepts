#pragma once

#include <memory>

class Model;  // forward declaration

class View {
public:
    View(std::shared_ptr<Model> model);
    void update(int data);
private:
    std::shared_ptr<Model> model_;
};
