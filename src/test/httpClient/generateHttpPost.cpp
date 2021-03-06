#include <catch2/catch.hpp>

#include <httpClient.hpp>

TEST_CASE( "httpClient can make post", "[httpClient]" ) {

    GIVEN( "An httpClient" ) {
        httpClient client;

        WHEN( "a post is generated" ) {
            std::string host = "test.com";
            std::string path = "/path";
            std::string authorization = "";
            std::string data = "{\"test\": \"test\"}";
            std::string contentLength = std::to_string(data.length());
            std::string request = client.generateHttpPost(host, path, authorization, data);

            THEN( "it is a valid request" ) {
                std::string expected = "POST " + path + " HTTP/1.1\r\n" +
                        "Host: " + host + "\r\n" +
                        "Connection: close\r\n" +
                        "Content-Type: application/json\r\n" +
                        "Content-Length: " + contentLength + "\r\n" +
                        "\r\n" + data;
                REQUIRE( expected == request );
            }
        }

        WHEN( "a post is generated with authorization" ) {
            std::string host = "test.com";
            std::string path = "/path";
            std::string authorization = "secret key";
            std::string data = "{\"test\": \"test\"}";
            std::string contentLength = std::to_string(data.length());
            std::string request = client.generateHttpPost(host, path, authorization, data);

            THEN( "it is a valid request" ) {
                std::string expected = "POST " + path + " HTTP/1.1\r\n" +
                        "Host: " + host + "\r\n" +
                        "Connection: close\r\n" +
                        "Content-Type: application/json\r\n" +
                        "Content-Length: " + contentLength + "\r\n" +
                        "Authorization: " + authorization + "\r\n" +
                        "\r\n" + data;
                REQUIRE( expected == request );
            }
        }
    }
}
