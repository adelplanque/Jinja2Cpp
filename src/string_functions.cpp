#include <functional>

#include <boost/algorithm/string.hpp>

#include "function_base.h"
#include "jinja2cpp/value.h"
#include "string_functions.h"


namespace jinja2
{

    InternalValue string_split(const std::string& value, const CallParams& params, RenderContext&)
    {
        std::cerr << __PRETTY_FUNCTION__ << std::endl;
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


    std::unordered_map<std::string, StringFunction> string_functions = {
        { "split", &string_split },
    };

}
