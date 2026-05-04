<?php

namespace App\pi;
use Throwable;

// This is the file used for scripts to interact directly with the Pi.

class Pi
{
    /**
     * Shuts down the Raspberry Pi, allows for it
     * to be safely unplugged.
     * @return void
     */
    static public function _shutdown()
    {
        try
        {
            shell_exec("sudo " . PI_SCRIPTS_PATH . "shutdown.sh");
        } 

        catch (Throwable $th)
        {
            throw($th);
        }
    }
}