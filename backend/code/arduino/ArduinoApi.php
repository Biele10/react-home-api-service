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
        $url = FLASK_SERVER_URL . '/send_command?command=' . urlencode($command);

        $options = [
        CURLOPT_URL => $url,
        CURLOPT_RETURNTRANSFER => true,
        CURLOPT_TIMEOUT => 10
        ];

        curl_setopt_array($ch, $options);

        $response = curl_exec($ch);
        
        if ($response === false)
        {
            $error = curl_error($ch);
            return ['success' => false, 'error' => $error];
        }

        $responseCode = curl_getinfo($ch, CURLINFO_HTTP_CODE);

        // response was incorrect
        if ($responseCode !== 200)
        {
            return ['success' => false, 'error' => 'Error with GET request: ' . $response];
        }

        return ['success' => true, 'content' => $response];
    }
}