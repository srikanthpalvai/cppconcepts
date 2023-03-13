#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <iostream>
#include "Model.h"
#include "View.h"

class Controller {
public:
    Controller(std::shared_ptr<Model> model, std::shared_ptr<View> view);
    void handle_input();
private:
    std::shared_ptr<Model> model_;
    std::shared_ptr<View> view_;
};

#endif // CONTROLLER_H
