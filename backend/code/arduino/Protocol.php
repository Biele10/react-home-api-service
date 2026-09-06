<?php

namespace Samaritan\arduino;

Class Protocol
{
    public const int HEADER_BYTE = 0xAA;
    public const string U8INT_FORMAT = 'C';    // 0->255 FF = 255
    public const string U16INT_FORMAT = 'n';   // 0->65,536 FF FF = 65,535
    public const int U16INT_LIMIT = 65535;
    public const int PARAMETER_BYTE_SIZE = 2;   // defines the size of one parameter in a payload in bytes (of course, a parameter could be spread across a few bytes, but each 'part' is always just 2 bytes of hex)
    public const string UNIX_SOCKET_PATH = '/run/samaritan/samaritan.sock';
    }