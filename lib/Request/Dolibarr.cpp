#include <DolibarrClient.h>
#include <HTTPClient.cpp>
#include <ArduinoJson.h>


Dolibarr::Dolibarr(String host)
{
    RequestClient client(host);
    this->client = client;
}


String Dolibarr::connect(String username, String password)
{
    String data = "login=" + username + "&password=" + password;
    String response = this->client.send(RequestClient::POST, "/api/index.php/login", data);
    
    JsonDocument doc;
    deserializeJson(doc, response);

    const char *sensor = doc["success"]["token"];
    this->token = sensor;
    return sensor;
}

JsonDocument Dolibarr::getProduct(String id)
{
    String response = this->client.sendAuth(RequestClient::GET, this->token, "/api/index.php/products/" + id, "");
    JsonDocument doc;
    deserializeJson(doc, response);
    return doc;
}

String Dolibarr::getProductWarehouse(String id)
{
    String response = this->client.sendAuth(RequestClient::GET, this->token, "/api/index.php/products/" + id, "");
    JsonDocument doc;
    deserializeJson(doc, response);
    return doc["fk_default_warehouse"];
}