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

if (empty($_GET['request_type']))
{
    echo json_encode(["success" => false, "error" => "Request type was empty."]);
    exit;
}

// handling a simple command to send to the arduino
if (!empty($_GET['request_type']) && $_GET['request_type'] === 'command')
{
    $params = $_GET;
    unset($params['request_type']);

    $queryString = http_build_query($params);
    $result = Hardware::_command($queryString);
    echo json_encode($result);
    exit;
}

// handles requests that are intended to interact with the raspberry pi
if ($_GET['request_type'] === 'pi_command')
{
    if (empty($_GET['command']))
    {
        echo json_encode(['success' => false, 'error' => 'No command was attached to send.']);
    }
    
    $piCommand = $_GET['command'];

    $result = Pi::_pi_command($piCommand);
    echo json_encode($result);
    exit;
}

if (isset($_GET['method']))
{
    $ledObj = new Led(4);
    echo json_encode($ledObj->getPin());
    exit;
}