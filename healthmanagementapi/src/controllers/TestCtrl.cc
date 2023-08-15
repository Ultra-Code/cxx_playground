#include "TestCtrl.h"
void
TestCtrl::asyncHandleHttpRequest(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback)
{
  // write your application logic here
  auto resp = HttpResponse::newHttpResponse();
  resp->setStatusCode(drogon::k200OK);
  resp->setContentTypeCode(drogon::CT_TEXT_HTML);
  resp->setBody("Hello World!");
  callback(resp);
}
