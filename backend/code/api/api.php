<?php
namespace App\api;

require __DIR__ . '/../../vendor/autoload.php';
require __DIR__ . '/../config/config.php';

use App\hardware\HardwareHandler;
use App\hardware\Led;
use App\hardware\Hardware;
use App\pi\Pi;
use App\errorHandler\ErrorHandler;

// This is the main entry point of the backend, all configs used throughout the program are set here.

set_exception_handler([ErrorHandler::class,'_handleError']);                // set default error handlers
register_shutdown_function([ErrorHandler::class, '_handleFatal']);
header('CORS: Allow-Origin');

// This file handles the proper backend logic, the api in the frontend passes the information here

if (empty($_GET['request_type']))
{
    echo json_encode(["success" => false, "error" => "Request type was empty."]);
    exit;
}

// handling a simple command to send to the arduino
if ($_GET['request_type'] === 'command')
{
    $params = $_GET;
    unset($params['request_type']);

    if (empty($params))
    {
        echo json_encode(['success' => false, 'error' => 'No command was attached to send.']);
        exit;
    }

    $queryString = http_build_query($params);
    $result = HardwareHandler::_command($queryString);

    echo json_encode($result);
    exit;
}

// handles requests that are intended to interact with the raspberry pi
if ($_GET['request_type'] === 'pi_command')
{   
    $module = $_GET['module'];
    $method = $_GET['method'];

    unset($_GET['request_type']);
    unset($_GET['module']);
    unset($_GET['method']);

    $params = (!empty($_GET)) ? $_GET : []; 

    if (empty($module) || empty($method))
    {
        echo json_encode(['success' => false, 'error' => 'Module and method must be attached.']);
        exit;
    }

    $result = Pi::_pi_command($module, $method, $params);
    echo json_encode($result);
    exit;
}

if (isset($_GET['method']))
{
    $ledObj = new Led(4);
    echo json_encode($ledObj->getPin());
    exit;
}