#pragma once

#include <drogon/drogon.h>
#include <jwt-cpp/traits/nlohmann-json/defaults.h>
#include <jwt-cpp/jwt.h>

namespace api::utils::jwt {
    using namespace drogon;

    class JWT {
    public:
        JWT(const std::string& token, const std::int64_t& expiration) {
            this->token = token;
            this->expiration = expiration;
        }

        std::string getToken() const {
            return this->token;
        }

        std::int64_t getExpiration() const {
            return this->expiration;
        }

        static JWT generateToken(const std::map<std::string, ::jwt::traits::nlohmann_json::value_type>& claims = {}, const bool& extension = false);
        static std::map<std::string, any> decodeToken(const std::string& encodedToken);

    private:
        std::string token;
        std::int64_t expiration;

        static bool verifyToken(const ::jwt::decoded_jwt<::jwt::traits::nlohmann_json>& jwt);
        static void addClaimToAttributes(std::map<std::string, any>& attributes, const std::pair<std::string, ::jwt::traits::nlohmann_json::value_type>& claim);
    };
}