#include <vsomeip/vsomeip.hpp>
#include <iostream>

std::shared_ptr<vsomeip::application> app;

void on_message(const std::shared_ptr<vsomeip::message> &msg) {
    auto payload = msg->get_payload();
    std::string text(payload->get_data().begin(), payload->get_data().end());
    std::cout << "Received message: " << text << std::endl;
}

int main() {
    app = vsomeip::runtime::get()->create_application("chat_server");
    app->init();

    app->register_message_handler(0x1234, 0x5678, 0x7777, on_message);
    app->offer_service(0x1234, 0x5678);

    app->start();
    return 0;
}
