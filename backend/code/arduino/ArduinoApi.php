<?php
namespace App\arduino;

/**
 * This class contains static functions which send requests to the Python flask server which interacts with the arduino.
 */
Class ArduinoApi
{
    /**
     * Sends GET requests to the flask server, typically used for single-lined
     * commands that do not require many parameters.
     */
    static public function _get(string $command): array
    {
        $ch = curl_init();

        $url = FLASK_SERVER_URL . '/send?' . $command;

        curl_setopt_array($ch, [
            CURLOPT_URL => $url,
            CURLOPT_RETURNTRANSFER => true,
            CURLOPT_TIMEOUT => 10
        ]);

        $response = curl_exec($ch);

        if ($response === false)
        {
            $error = curl_error($ch);
            return ['success' => false, 'error' => $error];
        }

        $responseCode = curl_getinfo($ch, CURLINFO_HTTP_CODE);

        if ($responseCode !== 200)
        {
            return ['success' => false, 'error' => 'Error with GET request: ' . $response];
        }

        return ['success' => true, 'content' => $response];
    }

    // TO-DO
    // CREATE FUNCTION TO VALIDATE FORMAT OF DATA SENT TO ARDUINO
    // FORMAT TO MATCH:
    // type=adjust&module=LED&method=power&state=1&silent=0

    static private function _validate_arduino_command(string $command)
    {

    }
}