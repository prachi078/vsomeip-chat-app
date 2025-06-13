# 🗨️ vSomeIP Two-Person Chat App

This project implements a terminal-based bi-directional chat application using the [vSomeIP](https://github.com/COVESA/vsomeip) middleware. Two users (`User1` and `User2`) can send and receive messages in real-time over a service-oriented communication model.

---

## 📦 Features

- vSomeIP-based real-time chat  
- Clean, interactive terminal UI  
- Bi-directional communication  
- Graceful exit using `/exit` command  
- Timestamps for received messages  
- Configurable via JSON  

---

## ⚙️ Prerequisites

Before setting up this project, make sure you have:

- **Ubuntu/Linux OS**
- **vSomeIP 3.5.5** installed  
  👉 [Install Guide](https://github.com/COVESA/vsomeip#building-vsomeip)
- **CMake** (>= 3.13)
- **GCC/G++**
- **Boost Libraries**

Install Boost (if not installed):

```bash
sudo apt update
sudo apt install libboost-all-dev
```

---

## 🛠️ Setup

### 1. Clone or Download the Project

```bash
git clone https://github.com/your-username/vsomeip-chat-app.git
cd vsomeip-chat-app
```

### 2. Project Structure

```
vsomeip-chat-app/
├── CMakeLists.txt
├── user1/
│   └── chat_user1.cpp
├── user2/
│   └── chat_user2.cpp
├── config/
│   ├── user1_config.json
│   └── user2_config.json
```

### 3. Build the Project

```bash
mkdir build && cd build
cmake ..
make
```

---

## 🚀 How to Run

Use two terminal windows:

### 🔵 Terminal 1 – Run `chat_user1`

```bash
export VSOMEIP_APPLICATION_NAME=chat_user1
export VSOMEIP_CONFIGURATION=../config/user1_config.json
./chat_user1
```

### 🟢 Terminal 2 – Run `chat_user2`

```bash
export VSOMEIP_APPLICATION_NAME=chat_user2
export VSOMEIP_CONFIGURATION=../config/user2_config.json
./chat_user2
```

Now start chatting!

---

## 💬 Chat Commands

| Command  | Description           |
|----------|-----------------------|
| `/exit`  | Exit the chat cleanly |

---

## 🔧 Config Files

Edit `config/user1_config.json` and `config/user2_config.json` to control:

- Logging level
- Port number
- Service and Instance IDs

### Example (`user1_config.json`):

```json
{
  "unicast": "127.0.0.1",
  "logging": {
    "level": "none",
    "console": false
  },
  "applications": [{ "name": "chat_user1", "id": 1 }],
  "services": [
    {
      "service": "0x1111",
      "instance": "0x1000",
      "unreliable": { "port": "30511" }
    }
  ]
}
```

---

## 📌 Notes

- Both users act as service providers and clients.  
- Message method ID used: `0x8888`  
- Each user offers and requests different services.

---

## 🧼 Clean Exit

When you type `/exit`, the app:

- Breaks the input loop  
- Closes cleanly  
- Resets the terminal prompt  

---

## 📚 References

- [COVESA vSomeIP GitHub](https://github.com/COVESA/vsomeip)

---

## 🧑‍💻 Author

**Prachi Patil**  
Feel free to fork, improve, or submit PRs!

---

## 📃 License

MIT License
