#include <vsomeip/vsomeip.hpp>
#include <iostream>

std::shared_ptr<vsomeip::application> app;

void send_chat(const std::string &text) {
    std::shared_ptr<vsomeip::message> msg = app->create_request();
    msg->set_service(0x1234);
    msg->set_instance(0x5678);
    msg->set_method(0x7777);

    std::shared_ptr<vsomeip::payload> pl = app->create_payload();
    std::vector<vsomeip::byte_t> data(text.begin(), text.end());
    pl->set_data(data);

    msg->set_payload(pl);
    app->send(msg);
}

int main() {
    app = vsomeip::runtime::get()->create_application("chat_client");
    app->init();
    app->request_service(0x1234, 0x5678);
    app->start_offer_service();

    app->start();

    std::string input;
    while (true) {
        std::getline(std::cin, input);
        send_chat(input);
    }

    return 0;
}
