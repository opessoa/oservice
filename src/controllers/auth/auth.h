#pragma once

#include <drogon/drogon.h>
#include <drogon/HttpController.h>
#include <src/utils/jwt/jwt.h>

using namespace drogon;
using namespace api::utils::jwt;
namespace api::v1 {
    class auth : public HttpController<auth> {
    public:
        METHOD_LIST_BEGIN
            METHOD_ADD(auth::getToken, "/login", Post, Options);
			METHOD_ADD(auth::verifyToken, "/verify", Get, Options, "api::v1::filters::jwtFilter");
        METHOD_LIST_END

        void getToken(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback);
		void verifyToken(const HttpRequestPtr &request, std::function<void(const HttpResponsePtr &)> &&callback);
    };
}