#pragma once
#include <Arduino.h>
#include "config/config.hpp"
class Result
{
    public:
        bool success;
        String message;
        String data;

        ErrorCode::Code errorCode;
        String error;

        Result(bool success, const String& message = "", const String& data = "", ErrorCode::Code errorCode = 0, 
        const String& error = "") : success(success), message(message), data(data), errorCode(errorCode), error(error) {};

         static Result Ok(const String& data = "")
        {
            return Result(true, "", data);
        }

        static Result Error(ErrorCode::Code code, const String& errorMsg)
        {
            return Result(false, "", "", code, errorMsg);
        }
};