#include <WString.h>
class RequestClient{
public:

    enum RequestType {
        GET,
        POST
    };

    String host;

    RequestClient();

    RequestClient(String host);

    String send(RequestType type, String path, String data);
    String sendAuth(RequestType type, String token, String path, String data);
};