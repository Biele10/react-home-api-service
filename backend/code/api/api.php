<?php
namespace App\api;

require __DIR__ . '/../../vendor/autoload.php';
require __DIR__ . '/../config/config.php';

use App\hardware\Led;
use App\hardware\Hardware;
use App\pi\Pi;
use App\errorHandler\ErrorHandler;

// This is the main entry point of the backend, all configs used throughout the program are set here.

set_exception_handler([ErrorHandler::class,'_handleError']);                // set default error handlers
register_shutdown_function([ErrorHandler::class, '_handleFatal']);

// This file handles the proper backend logic, the api in the frontend passes the information here
if (!empty($_GET['module']) && $_GET['module'] === 'led')
{
    Hardware::_powerOnBoardLed();
}

if (isset($_GET['method']))
{
    $ledObj = new Led(4);
    echo json_encode($ledObj->getPin());
    exit;
}