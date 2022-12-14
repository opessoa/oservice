/**
 *
 *  UserControler.cc
 *  This file is generated by drogon_ctl
 *
 */

#include "UserControler.h"
#include <string>


void UserControler::getOne(const HttpRequestPtr &req,
                           std::function<void(const HttpResponsePtr &)> &&callback,
                           User::PrimaryKeyType &&id)
{
    UserControlerBase::getOne(req, std::move(callback), std::move(id));
}


void UserControler::updateOne(const HttpRequestPtr &req,
                              std::function<void(const HttpResponsePtr &)> &&callback,
                              User::PrimaryKeyType &&id)
{
    UserControlerBase::updateOne(req, std::move(callback), std::move(id));
}


void UserControler::deleteOne(const HttpRequestPtr &req,
                              std::function<void(const HttpResponsePtr &)> &&callback,
                              User::PrimaryKeyType &&id)
{
    UserControlerBase::deleteOne(req, std::move(callback), std::move(id));
}

void UserControler::get(const HttpRequestPtr &req,
                        std::function<void(const HttpResponsePtr &)> &&callback)
{
    UserControlerBase::get(req, std::move(callback));
}

void UserControler::create(const HttpRequestPtr &req,
                           std::function<void(const HttpResponsePtr &)> &&callback)
{
    UserControlerBase::create(req, std::move(callback));
}

void UserControler::view(const HttpRequestPtr &req,
                           std::function<void(const HttpResponsePtr &)> &&callback)
{
    const auto& users = UserControlerBase::view(req, std::move(callback));
    HttpViewData data;
    data.insert("title","ListParameters");
    data.insert("users",users);
    auto resp=HttpResponse::newHttpViewResponse("views/listUsers.csp",data);
    callback(resp);
}