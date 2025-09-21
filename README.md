# CppTalk

Atualizar e baixar o conteúdo dos submódulos

```bash
    git clone https://github.com/GuilhermeRossiKirsten/CppTalk.git
    git submodule update --init --recursive

    ou

    git clone --recurse-submodules https://github.com/GuilhermeRossiKirsten/CppTalk.git

    sudo apt install build-essential
    sudo apt install pkg-config postgresql libpq-dev

    
```



git submodule add --force https://github.com/CrowCpp/crow.git chat-server/external/crow
git submodule add --force https://github.com/SqliteModernCpp/sqlite_modern_cpp.git chat-server/external/sqlite_modern_cpp
git submodule add --force https://github.com/nlohmann/json.git chat-server/external/json
git submodule add --force https://github.com/chriskohlhoff/asio.git chat-server/external/asio
git submodule add --force https://github.com/jtv/libpqxx.git chat-server/external/libpqxx
