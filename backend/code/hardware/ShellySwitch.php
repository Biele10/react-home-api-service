<?php
namespace Samaritan\hardware;

/**
 * Class represents a shelly dimmer switch which
 * is used to control lights.
 */
Class ShellySwitch
{
    static public function _adjustLight(string $lightPercentage)
    {
        echo json_encode("WE HAVE OUR LIGHT VALUE " . $lightPercentage);exit;
        // TO-DO
        // WRITE CODE TO MAKE API REQUEST TO SHELLY DIMMER
    }
}