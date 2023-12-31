/**
 *
 *  api_rest.h
 *  This file is generated by drogon_ctl
 *
 */

#pragma once

#include <drogon/HttpController.h>
using namespace drogon;
namespace api 
{
/**
 * @brief this class is created by the drogon_ctl command (drogon_ctl create controller -r api::rest).
 * this class is a restful API controller.
 */
class rest: public drogon::HttpController<rest>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    METHOD_ADD(rest::getOne,"/{1}",Get,Options);
    METHOD_ADD(rest::get,"",Get,Options);
    METHOD_ADD(rest::create,"",Post,Options);
    METHOD_ADD(rest::updateOne,"/{1}",Put,Options);
    //METHOD_ADD(rest::update,"",Put,Options);
    METHOD_ADD(rest::deleteOne,"/{1}",Delete,Options);
    METHOD_LIST_END

    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                std::string &&id);
    void updateOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                std::string &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   std::string &&id);
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);

//    void update(const HttpRequestPtr &req,
//                std::function<void(const HttpResponsePtr &)> &&callback);

};
}
