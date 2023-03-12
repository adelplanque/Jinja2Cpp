#include <arpa/inet.h>
#include <cstring>
#include <functional>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <boost/algorithm/string.hpp>

#include "function_base.h"
#include "jinja2cpp/value.h"
#include "string_functions.h"


namespace jinja2
{

    InternalValue string_split(const std::string& value, const CallParams& params, RenderContext&)
    {
        InternalValueList result;
        std::string delim;
        if (params.posParams.size() >= 1) {
            delim = AsString(params.posParams[0]);
        } else if (params.kwParams.count("delim")) {
            delim = AsString(params.kwParams.at("delim"));
        } else {
            delim = " ";
        }
        std::list<std::string> tokens;
        boost::split(tokens, value, boost::is_any_of(delim));
        for (auto& tok : tokens) {
            result.push_back(tok);
        }
        return ListAdapter::CreateAdapter(std::move(result));
    }

    InternalValue getip(const std::string& value, const CallParams& params, RenderContext&)
    {
        if (value == "127.0.0.1" || value == "localhost" || value == "localhost.localdomain") {
            return std::string("127.0.0.1");
        }
        if (value == "AUTO") {
            return std::string("AUTO");
        }

        struct addrinfo *info, *p;
        std::string res;
        if ((getaddrinfo(value.c_str(), NULL, NULL, &info)) == 0) {
            p = info;
            while (p != nullptr) {
                if (p->ai_addr != nullptr) {
                    struct sockaddr *sock = p->ai_addr;
                    struct sockaddr_in *sock_in = (struct sockaddr_in *) sock;
                    const char *tmp = inet_ntoa(sock_in->sin_addr);
                    if (tmp != nullptr) {
                        res = tmp;
                        if (strcmp(tmp, "127.0.0.1") != 0) {
                            break;
                        }
                    }
                }
                p = p->ai_next;
            }
            freeaddrinfo(info);
        }
        return res;
    };

    std::unordered_map<std::string, StringFunction> string_functions = {
        { "split", &string_split },
        { "ip", &getip },
    };

}
