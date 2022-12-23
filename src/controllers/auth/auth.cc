#include "auth.h"
using namespace api::v1;

void auth::getToken(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback) {
    
    Json::Value resultJson;
    if(!request || !request->getJsonObject())
    {
        resultJson["error"] = "Invalid Json.";
		resultJson["status"] = 0;

        return callback(HttpResponse::newHttpJsonResponse(resultJson));   
    }
    Json::Value responseJson = *request->getJsonObject();

    // Verify if there's a missing values on body of request
    if (!responseJson.isMember("email") || !responseJson.isMember("password")) {
        resultJson["error"] = "Missing email or password.";
		resultJson["status"] = 0;

        return callback(HttpResponse::newHttpJsonResponse(resultJson));
    }
    auto jwtGenerated = JWT::generateToken({{"email",responseJson["email"].asString()}}/*,
        responseJson.isMember("remember") && responseJson["remember"].asBool()*/
    );
    Json::Value::Int64 jwtExpiration = jwtGenerated.getExpiration();

    resultJson["token"] = jwtGenerated.getToken();
    resultJson["expiresIn"] = jwtExpiration - std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    resultJson["expiresAt"] = jwtExpiration;
    resultJson["status"] = 1;

    return callback(HttpResponse::newHttpJsonResponse(resultJson));
}

void auth::verifyToken(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback) {
    Json::Value resultJson;

    resultJson["aud"] = request->getAttributes()->get<std::string>("jwt_aud");
    resultJson["exp"] = request->getAttributes()->get<Json::Value::Int64>("jwt_exp");
    resultJson["iat"] = request->getAttributes()->get<Json::Value::Int64>("jwt_iat");
    resultJson["iss"] = request->getAttributes()->get<std::string>("jwt_iss");
    resultJson["nbf"] = request->getAttributes()->get<Json::Value::Int64>("jwt_nbf");
    resultJson["email"] = request->getAttributes()->get<std::string>("jwt_email");
    resultJson["jwt_debugger"] = "https://jwt.io/#debugger-io?token=" + request->getHeader("Authorization").substr(7);
    resultJson["status"] = 1;

    return callback(HttpResponse::newHttpJsonResponse(resultJson));
}