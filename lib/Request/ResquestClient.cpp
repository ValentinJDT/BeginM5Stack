#include <RequestClient.h>
#include <HTTPClient.h>

RequestClient::RequestClient(String host)
{
    this->host = host;
}

RequestClient::RequestClient()
{
    this->host = "http://localhost";
}

String RequestClient::send(RequestType type, String path, String data)
{
    HTTPClient http;

    http.begin(this->host + path);

        if (type == GET)
    {
        Serial.println("GET");
        http.GET();
        return http.getString();
    }
    else if (type == POST)
    {
        Serial.println("POST");
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        http.POST(data);
        return http.getString();
    }

    return "";
}

String RequestClient::sendAuth(RequestType type, String token, String path, String data)
{
    HTTPClient http;

    http.begin(this->host + path);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("DOLAPIKEY", token);

    if (type == GET)
    {
        Serial.println("GET");
        http.GET();
        return http.getString();
    }
    else if (type == POST)
    {
        Serial.println("POST");
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        http.POST(data);
        return http.getString();
    }

    return "";
}