<?php

namespace App\pi;
use Throwable;

// This is the file used for scripts to interact directly with the Pi.

// used to determine which module to interact with
enum piFunctions: string
{
    case shutdown = 'shutdown';
    case shelly = 'shelly';
}

class Pi
{
    /**
     * Handles all functions in relation to the raspberry pi.
     * 
     * @param string $module - Defines the class the code will interact with
     * @param string $method - The method that will be executed within the class
     * @param array $params - The parameters passed in to interact with the Pi (module, method etc)
     * @return array{error: string, success: bool}
     */
    static public function _pi_command(string $module, string $method, array $params = [])
    {
        if (!$module)
        {
            return ['success' => false, 'error' => "Pi command was not set."];
        }

        $piCommand = piFunctions::tryFrom($module);

        if (!$piCommand)
        {
            return ['success' => false, 'error' => 'Pi command passed does not exist.'];
        }

        $result = match($piCommand)
        {
            // TO-DO
            // RESEARCH BEST WAY TO NAVIGATE TO MODULE METHODS
            piFunctions::shelly => \App\hardware\ShellySwitch::_adjustLight($params['light_percentage'])
        };

        if (!$result)
        {
            return ['success' => false, 'error' => 'Pi command did not link to any functions.'];
        }

        return ['success' => true, 'response' => $result];
    }

    // /**
    //  * Shuts down the Raspberry Pi, allows for it
    //  * to be safely unplugged.
    //  * @return array
    //  */
    // static private function _shutdown()
    // {
    //     exec('sudo /sbin/shutdown -h now', $output, $code);

    //     // kind of pointless, seeing as it shuts down the server... but whatever
    //     return [
    //         'success' => $code === 0,
    //         'output' => $output,
    //         'code' => $code
    //     ];
    // }
}