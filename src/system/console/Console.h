#pragma once
#include <vector>
#include <string>

class Console
{
public:
    static void Info(const std::string& message, const std::vector<std::string>& messages = {});
    static void Warn(const std::string& message, const std::vector<std::string>& messages = {});
    static void Error(const std::string& message, const std::vector<std::string>& messages = {});

};
