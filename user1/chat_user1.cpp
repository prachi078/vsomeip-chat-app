#include <vsomeip/vsomeip.hpp>
#include <iostream>
#include <thread>
#include <iomanip>
#include <chrono>

std::shared_ptr<vsomeip::application> app;

void on_message_from_user2(const std::shared_ptr<vsomeip::message> &msg) {
    auto pl = msg->get_payload();
    std::string text(reinterpret_cast<const char*>(pl->get_data()), pl->get_length());

    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "\r[" << std::put_time(std::localtime(&now), "%H:%M:%S") << "] ";
    std::cout << "[User2]: " << text << "\n> " << std::flush;
}

void send_message(const std::string &text) {
    auto request = vsomeip::runtime::get()->create_request();
    request->set_service(0x2222);
    request->set_instance(0x2000);
    request->set_method(0x8888);

    auto payload = vsomeip::runtime::get()->create_payload();
    std::vector<vsomeip::byte_t> data(text.begin(), text.end());
    payload->set_data(data);
    request->set_payload(payload);

    app->send(request);
}

int main() {
    app = vsomeip::runtime::get()->create_application("chat_user1");
    app->init();

    app->register_state_handler([](vsomeip::state_type_e state) {
        if (state == vsomeip::state_type_e::ST_REGISTERED) {
            app->offer_service(0x1111, 0x1000);
            app->request_service(0x2222, 0x2000);
        }
    });

    app->register_message_handler(0x1111, 0x1000, 0x8888, on_message_from_user2);

    std::thread app_thread([] { app->start(); });

    std::cout << "\n🔵 ChatApp - Connected as User1" << std::endl;
    std::cout << "Type your message below. Type /exit to quit." << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "> ";

    std::string input;
    while (true) {
        std::getline(std::cin, input);
        if (input == "/exit") {
            std::cout << "👋 Exiting chat..." << std::endl;
            break;
        }
        if (!input.empty()) send_message(input);
        std::cout << "> ";
    }

    app_thread.join();
    return 0;
}