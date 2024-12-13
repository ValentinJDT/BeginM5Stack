#include <WString.h>
#include <RequestClient.h>
#include <ArduinoJson.h>

class Dolibarr {
    public:
        RequestClient client;
        String token;

        Dolibarr(String host);

        String connect(String username, String password);

        JsonDocument getProduct(String id);

        String getProductWarehouse(String id);

        String addProductToWarehouse(String id, String warehouse, int quantity = 1);
};