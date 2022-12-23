#include "LoginController.h"

void LoginController::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto resp=HttpResponse::newHttpViewResponse("views::login");
    resp->setStatusCode(k200OK);
    callback(resp);
}
