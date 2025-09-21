#include <pqxx/pqxx>
#include <queue>
#include <mutex>
#include <memory>
#include <string>
#include <iostream>

class DbPool {
private:
    std::queue<std::shared_ptr<pqxx::connection>> connections;
    std::mutex mtx;
    std::string conn_str;
    int pool_size;

    std::shared_ptr<pqxx::connection> createConnection() {
        auto conn = std::make_shared<pqxx::connection>(conn_str);
        if (!conn->is_open()) {
            throw std::runtime_error("Falha ao abrir conexão com PostgreSQL");
        }
        return conn;
    }

public:
    DbPool(const std::string& conn_str_, int size) : conn_str(conn_str_), pool_size(size) {
        for (int i = 0; i < pool_size; ++i) {
            connections.push(createConnection());
        }
    }

    std::shared_ptr<pqxx::connection> acquire() {
        std::lock_guard<std::mutex> lock(mtx);
        if (connections.empty()) {
            return createConnection(); // cria nova conexão se todas estiverem em uso
        }
        auto conn = connections.front();
        connections.pop();
        if (!conn->is_open()) { // verifica se a conexão ainda está válida
            std::cerr << "Conexão caiu. Criando nova..." << std::endl;
            conn = createConnection();
        }
        return conn;
    }

    void release(std::shared_ptr<pqxx::connection> conn) {
        std::lock_guard<std::mutex> lock(mtx);
        if (conn->is_open()) {
            connections.push(conn);
        } else {
            std::cerr << "Conexão inválida descartada." << std::endl;
        }
    }
};
