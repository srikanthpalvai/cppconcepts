#include "Model.h"
#include "View.h"

void Model::attach_view(std::shared_ptr<View> view) {
    observers_.push_back([view](int data) { view->update(data); });
}

void Model::set_data(int data) {
    data_ = data;
    notify();
}

void Model::notify() {
    for (auto& observer : observers_) {
        observer(data_);
    }
}
