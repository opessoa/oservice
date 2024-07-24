#include <drogon/drogon.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/DbClient.h>
#include <iostream>
#include <cstring>
#include <fstream>

using namespace drogon;
using namespace drogon::orm;

namespace {
    void createConfigFile(const std::string &filename) {
        std::ofstream configFile(filename);
        if (!configFile) {
            std::cerr << "Error creating config file: " << filename << std::endl;
            return;
        }

        // Define the default configuration content
        std::string configContent = R"(
        {
            "listeners": [
                {
                    "address": "0.0.0.0",
                    "port": 80
                }
            ],
            "custom_config": {
                "jwt": {
                    "private_key": "drogon_jwt_filter_example_cool_private_key",
                    "issuer": "auth.domain.pt",
                    "audience": "domain.pt"
                }
            },
            "db_clients":[
                {
                    "name":"default",
                    "rdbms": "sqlite3",
                    "is_fast": false,
                    "connection_number": 1,
                    "filename": "db.sqlite3"
                }
            ]
        })";

        configFile << configContent;
        configFile.close();
        std::cout << "Configuration file created successfully: " << filename << std::endl;
    }

    int createDatabase() {
        try {
            // Create a database client (example uses SQLite, adjust for your database)
            auto dbClient = DbClient::newSqlite3Client("db.sqlite3",11);

            // Define the SQL statement for creating a table
            std::string createTableSQL = R"(
                CREATE TABLE IF NOT EXISTS user (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    name VARCHAR(20) NOT NULL,
                    password TEXT
                );
            )";

            // Execute the SQL statement to create the table
            dbClient->execSqlSync(createTableSQL);

            std::cout << "Database table created successfully." << std::endl;
            return 0;
        } catch (const std::exception &e) {
            std::cerr << "Error creating database table: " << e.what() << std::endl;
            return 1;
        }
    }
} // anonymous namespace

int main(int argc, char* argv[]) {
    bool installMode = false;
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--install") == 0) {
            installMode = true;
            break;
        } else if (std::strcmp(argv[i], "--help") == 0) {
            std::cout << "Usage: " << argv[0] << " [--install]" << std::endl;
            std::cout << "Options:" << std::endl;
            std::cout << "  --install    Run installation procedures" << std::endl;
            return 0;
        }
    }

    if (installMode) {
        std::cout << "Install option selected. Performing installation steps..." << std::endl;
        std::cout << "Creating configuration file" << std::endl;
        createConfigFile("config.json");
        std::cout << "Creating database" << std::endl;
        int dbResult = createDatabase();
        if (dbResult != 0) {
            std::cerr << "Installation failed. Check the error messages above." << std::endl;
            return dbResult;
        }
        std::cout << "Installation complete" << std::endl;
        return 0;
    }
    // Load config file
    app().loadConfigFile("./config.json");

    // CORS Policy - Allow connections from anywhere
    app().registerPostHandlingAdvice([](const HttpRequestPtr &req, const HttpResponsePtr &resp) {
        resp->addHeader("Access-Control-Allow-Origin", "*");
        resp->addHeader("Authorization",req->getHeader("Authorization"));
    });

    // Run HTTP framework,the method will block in the internal event loop
    app().run();

    return 0;
}