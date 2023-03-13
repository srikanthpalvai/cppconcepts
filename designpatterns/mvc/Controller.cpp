#include "Controller.h"

Controller::Controller(std::shared_ptr<Model> model, std::shared_ptr<View> view)
    : model_{model}, view_{view} {}

void Controller::handle_input() {
    int input;
    std::cout << "Enter a new integer value: ";
    std::cin >> input;
    model_->set_data(input);
}
