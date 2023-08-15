#include <oatpp/network/server/Server.hpp>
#include <oatpp/network/server/SimpleTCPConnectionProvider.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>

void run()
{
    /* Create Router for HTTP requests routing */
    auto router = oatpp::web::server::HttpRouter::createShared();

    /* Create HTTP connection handler with router */
    auto connectionHandler
      = oatpp::web::server::HttpConnectionHandler::createShared(router);

    /* Create TCP connection provider */
    auto connectionProvider
      = oatpp::network::server::SimpleTCPConnectionProvider::createShared(
        8000 /* port */);

    /* Create server which takes provided TCP connections and passes them to HTTP
     * connection handler */
    oatpp::network::server::Server server(connectionProvider, connectionHandler);

    /* Priny info about server port */
    OATPP_LOGI("MyApp", "Server running on port %s",
               connectionProvider->getProperty("port").getData());

    /* Run server */
    server.run();
}

int main()
{
    /* Init oatpp Environment */
    oatpp::base::Environment::init();

    /* Run App */
    run();

    /* Destroy oatpp Environment */
    oatpp::base::Environment::destroy();

    return 0;
}
