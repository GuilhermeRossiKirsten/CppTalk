#include "crow.h"
#include <nlohmann/json.hpp>
#include "include/dbpool.h"

using json = nlohmann::json;

int main() {
    crow::SimpleApp app;

    std::string conn_str = "host=127.0.0.1 port=5432 dbname=database user=user password=password";
    DbPool pool(conn_str, 5); // Pool com 5 conexões

    // GET /users
    CROW_ROUTE(app, "/users").methods("GET"_method)
    ([&pool](){
        try {
            auto conn = pool.acquire();
            pqxx::work W(*conn);
            pqxx::result R = W.exec("SELECT id, name, email FROM users;");

            json j;
            for (auto row : R) {
                j.push_back({
                    {"id", row["id"].as<int>()},
                    {"name", row["name"].c_str()},
                    {"email", row["email"].c_str()}
                });
            }

            pool.release(conn);
            return crow::response(j.dump());
        } catch (const std::exception& e) {
            return crow::response(500, std::string("Erro ao acessar o banco: ") + e.what());
        }
    });

    // POST /users
    CROW_ROUTE(app, "/users").methods("POST"_method)
    ([&pool](const crow::request& req){
        auto conn = pool.acquire();

        auto body = json::parse(req.body);
        std::string name = body["name"];
        std::string email = body["email"];

        pqxx::work W(*conn);
        W.exec_params("INSERT INTO users (name, email) VALUES ($1, $2);", name, email);
        W.commit();

        pool.release(conn);

        return crow::response(201, "User created");
    });

    app.port(18080).multithreaded().run();
}
