#include <memory>
#include "Model.h"
#include "View.h"
#include "Controller.h"

int main() {
    std::shared_ptr<Model> model = std::make_shared<Model>();
    std::shared_ptr<View> view = std::make_shared<View>(model);
    std::shared_ptr<Controller> controller = std::make_shared<Controller>(model, view);

    controller->handle_input();

	/* without controller 
    auto model = std::make_shared<Model>();
    auto view = std::make_shared<View>(model);
    model->attach_view(view);
    model->set_data(42);
	*/
    return 0;
}
