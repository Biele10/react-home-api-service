<?php

namespace Samaritan\errorHandler;
use Throwable;

Class ErrorHandler
{
    /**
     * Error handler that returns errors back to users
     * in a set format.
     * @param Throwable $th
     * @return never
     */
    static public function _handleError(Throwable $th)
    {
        echo json_encode($th->getMessage());
        exit;
    }

    static public function _handleFatal()
    {
        $error = error_get_last();
        if ($error) {
            echo "Fatal: " . $error['message'];
        }
    }
}