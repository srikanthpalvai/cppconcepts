#include "View.h"
#include "Model.h"
#include <iostream>

View::View(std::shared_ptr<Model> model)
    : model_{model}
{
}

void View::update(int data) {
    std::cout << "View: received update with data " << data << std::endl;
}
