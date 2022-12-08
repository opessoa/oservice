#include "jwt.h"

using namespace api::utils::jwt;

JWT JWT::generateToken(const std::map<std::string, ::jwt::traits::nlohmann_json::value_type>& claims, const bool& extension) {
    const auto time = std::chrono::system_clock::now();

    // If remember is true, just add more 30 days, otherwise, just put valid only for 1 day. hours{(extension ? 30 : 1) * 24}
    const int64_t expiresAt = std::chrono::duration_cast<std::chrono::seconds>((time + std::chrono::minutes{5}).time_since_epoch()).count();

    auto jwtToken = ::jwt::create()
        .set_type("JWT")
        .set_issuer(app().getCustomConfig()["jwt"]["issuer"].asString())
        .set_audience(app().getCustomConfig()["jwt"]["audience"].asString())
        .set_issued_at(time)
        .set_not_before(time)
        .set_expires_at(std::chrono::system_clock::from_time_t(expiresAt));

    for (auto& claim : claims)
        jwtToken.set_payload_claim(claim.first, claim.second);

    return {
        jwtToken.sign(::jwt::algorithm::hs256{app().getCustomConfig()["jwt"]["private_key"].asString()}),
        expiresAt
    };
}

std::map<std::string, any> JWT::decodeToken(const std::string& encodedToken) {
    // Let's decode it, if isn't a valid token of JWT, catch will be called
    try {
        auto decodedToken = ::jwt::decode(encodedToken);

        if (verifyToken(decodedToken)) {
            std::map<std::string, any> attributes = {};

            // Save the claims on attributes
            for (auto& claim : decodedToken.get_payload_json())
                addClaimToAttributes(attributes, claim);

            return attributes;
        }

        std::cout << "verify error" << std::endl;
        return {};
    } catch (...) {
        std::cout << "verify catch" << std::endl;
        return {};
    }
}

bool JWT::verifyToken(const ::jwt::decoded_jwt<::jwt::traits::nlohmann_json>& jwt) {
    // Let's create a verifier
    auto jwtVerifier = ::jwt::verify()
        .with_issuer(app().getCustomConfig()["jwt"]["issuer"].asString())
        .with_audience(app().getCustomConfig()["jwt"]["audience"].asString())
        .allow_algorithm(::jwt::algorithm::hs256{app().getCustomConfig()["jwt"]["private_key"].asString()});

    // If some properties of token doesn't correspond same as like, issued, audience, etc..., catch will be called
    try {
        std::cout << "verify" << std::endl;
        jwtVerifier.verify(jwt);
        return true;
    } catch(...)  {
        return false;
    }
}

void JWT::addClaimToAttributes(std::map<std::string, any>& attributes, const std::pair<std::string, ::jwt::traits::nlohmann_json::value_type>& claim) {
    if (claim.second.is_boolean()) 
        attributes.insert(std::pair<std::string, bool>(claim.first, ::jwt::traits::nlohmann_json::as_boolean(claim.second)));
    else if (claim.second.is_number_integer())
        attributes.insert(std::pair<std::string, std::int64_t>(claim.first, ::jwt::traits::nlohmann_json::as_integer(claim.second)));
    else if (claim.second.is_number_float())
        attributes.insert(std::pair<std::string, double>(claim.first, ::jwt::traits::nlohmann_json::as_number(claim.second)));
    else if (claim.second.is_string())
        attributes.insert(std::pair<std::string, std::string>(claim.first, ::jwt::traits::nlohmann_json::as_string(claim.second)));
    else if (claim.second.is_array())
        attributes.insert(std::pair<std::string, any>(claim.first, ::jwt::traits::nlohmann_json::as_array(claim.second)));
    else if (claim.second.is_object())
        attributes.insert(std::pair<std::string, any>(claim.first, ::jwt::traits::nlohmann_json::as_object(claim.second)));
    else throw std::bad_cast();
}