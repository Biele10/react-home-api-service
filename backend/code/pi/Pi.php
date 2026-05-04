<?php

namespace App\pi;
use Throwable;

// This is the file used for scripts to interact directly with the Pi.

// used to determine which function to 
enum piFunctions: string
{
    case shutdown = 'shutdown';
}

class Pi
{
    /**
     * Handles all functions in relation to the raspberry pi, to
     * ensure safety, no parameters are passed through to tell the pi what to do,
     * rather this function executes pre-determined instructions.
     * 
     * @param mixed $piCommand
     * @return array{error: string, success: bool}
     */
    static public function _pi_command($piCommand)
    {
        if (!$piCommand)
        {
            return ['success' => false, 'error' => "Pi command was not set."];
        }

        $piCommand = piFunctions::tryFrom($piCommand);

        if (!$piCommand)
        {
            return ['success' => false, 'error' => 'Pi command passed does not exist.'];
        }

        $result = match($piCommand)
        {
            piFunctions::shutdown => self::_shutdown()
        };

        if (!$result)
        {
            return ['success' => false, 'error' => 'Pi command did not link to any functions.'];
        }

        return ['success' => true, 'response' => $result];
    }

    /**
     * Shuts down the Raspberry Pi, allows for it
     * to be safely unplugged.
     * @return array
     */
    static private function _shutdown()
    {
        exec('sudo /sbin/shutdown -h now', $output, $code);

        // kind of pointless, seeing as it shuts down the server... but whatever
        return [
            'success' => $code === 0,
            'output' => $output,
            'code' => $code
        ];
    }
}