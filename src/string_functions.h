#ifndef JINJA2CPP_SRC_STRING_FUNCTIONS_H
#define JINJA2CPP_SRC_STRING_FUNCTIONS_H

namespace jinja2
{
    typedef InternalValue(*StringFunction)(const std::string&, const CallParams&, RenderContext&);
    extern std::unordered_map<std::string, StringFunction> string_functions;
}

#endif
