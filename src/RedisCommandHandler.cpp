#include<include/RedisCommandHandler.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>


//RESP PRASER
std::vector<std::string>praseRespCommand(const std::string& input) {
    std::vector<std::string> tokens;
    if (input.empty()) {
        return tokens;
    }
    if (input[0] != '*') {
        std::istringstream iss(input);
        std::string token;
        while(iss >> token){
            tokens.push_back(token);
        }
        return tokens;
    }

    size_t pos = 0;
    //Except '*' at the beginning
    if(input[pos] != '*') return tokens;
    pos++;


    //crlf=carriage return(\r),line feed(\n)
    size_t crlf=input.find("\r\n", pos);
    if(crlf == std::string::npos) return tokens;
    int numElements = std::stoi(input.substr(pos, crlf - pos));
    pos = crlf + 2; // Move past the CRLF


    for(int i=0;i<numElements;i++) {
        if(pos >= input.size() || input[pos] != '$')return tokens; // Invalid format
        pos++; // Skip the '$'
        crlf = input.find("\r\n", pos);

        if(crlf == std::string::npos) break;
        int len= std::stoi(input.substr(pos, crlf - pos));
        pos = crlf + 2; // Move past the CRLF

        if(pos + len > input.size()) break; // Invalid length
        std::string token = input.substr(pos, len);
        tokens.push_back(token);
        pos += len; // Move past the token

    }
    return tokens;
}

RedisCommandHandler::RedisCommandHandler() {
    // Constructor implementation if needed
}

std::string RedisCommandHandler::handleCommand(const std::string& commandLine) {
    auto tokens = praseRespCommand(commandLine);
    if(tokens.empty()) {
        return "-ERR Empty command format\r\n";
    }

    std::string command = tokens[0];
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    std::ostringstream response;

    return response.str();

}