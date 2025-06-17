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


// cd ~/Documents/chat_app/build-arm64
//     rm -rf *
//     cmake ..   -DCMAKE_TOOLCHAIN_FILE=../toolchain-arm64.cmake   -DCMAKE_PREFIX_PATH=$HOME/vscode/vsomeip-arm64/install   -DCMAKE_FIND_ROOT_PATH=$HOME/vscode/vsomeip-arm64/install   -DCMAKE_SKIP_RPATH=ON   -DBOOST_ROOT=$HOME/vscode/boost/boost-arm64   -DBoost_NO_SYSTEM_PATHS=ON
//     make -j$(nproc)
//     make
//     file chat_user1


//  1. Clone vSomeIP (with submodules)

// cd ~/vscode
// git clone --recurse-submodules https://github.com/COVESA/vsomeip.git vsomeip-arm64

//  2. Build Boost for ARM64 (if not already built)

// (optional but recommended if Boost not installed for ARM64)

// cd ~/vscode/boost/boost_1_76_0

// ./bootstrap.sh

// echo "using gcc : arm : aarch64-linux-gnu-g++ ;" > user-config.jam

// ./b2 \
//   toolset=gcc-arm \
//   target-os=linux \
//   architecture=arm \
//   address-model=64 \
//   --prefix=../boost-arm64 \
//   --with-system --with-thread --with-filesystem \
//   --user-config=./user-config.jam \
//   install

//  3. Build vSomeIP for ARM64

// cd ~/vscode/vsomeip-arm64
// mkdir build-arm64 && cd build-arm64

// cmake .. \
//   -DCMAKE_TOOLCHAIN_FILE=../toolchain-arm64.cmake \
//   -DCMAKE_INSTALL_PREFIX=~/vscode/vsomeip-arm64/install \
//   -DBOOST_ROOT=~/vscode/boost/boost-arm64 \
//   -DBoost_NO_SYSTEM_PATHS=ON

// make -j$(nproc)
// make install

//  4. Build Your Chat App for ARM64

// cd ~/Documents/chat_app
// mkdir build-arm64 && cd build-arm64

// cmake .. \
//   -DCMAKE_TOOLCHAIN_FILE=../toolchain-arm64.cmake \
//   -DCMAKE_PREFIX_PATH=~/vscode/vsomeip-arm64/install \
//   -DBOOST_ROOT=~/vscode/boost/boost-arm64 \
//   -DBoost_NO_SYSTEM_PATHS=ON


// make -j$(nproc)
// make install

//  4. Build Your Chat App for ARM64

// cd ~/Documents/chat_app
// mkdir build-arm64 && cd build-arm64

// cmake .. \
//   -DCMAKE_TOOLCHAIN_FILE=../toolchain-arm64.cmake \
//   -DCMAKE_PREFIX_PATH=~/vscode/vsomeip-arm64/install \
//   -DBOOST_ROOT=~/vscode/boost/boost-arm64 \
//   -DBoost_NO_SYSTEM_PATHS=ON

// make -j$(nproc)
