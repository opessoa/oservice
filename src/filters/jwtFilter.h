#pragma once

#include <drogon/drogon.h>
#include <src/utils/jwt/jwt.h>

using namespace drogon;
using namespace api::utils::jwt;
namespace api::v1::filters {
    class jwtFilter : public HttpFilter<jwtFilter> {
    public:
        jwtFilter() = default;

        virtual void doFilter(const HttpRequestPtr &request, FilterCallback &&fcb, FilterChainCallback &&fccb) override;
    };
}