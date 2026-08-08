<?php

require __DIR__ . '/../backend/vendor/autoload.php';
require __DIR__ . '/../backend/code/config/config.php';

$dispatcher = FastRoute\simpleDispatcher(function($r){
    require __DIR__ . '/../backend/code/routes/Api.php';
});

$path = parse_url($_SERVER['REQUEST_URI'], PHP_URL_PATH);

$path = preg_replace('#^/api#', '', $path);

$routeInfo = $dispatcher->dispatch(
    $_SERVER['REQUEST_METHOD'],
    $path
);

switch ($routeInfo[0]) {
    case FastRoute\Dispatcher::NOT_FOUND:
        $response = new \App\resources\Response('0', 404, ['error' => 'Route not found']);
        break;

    case FastRoute\Dispatcher::METHOD_NOT_ALLOWED:
        $response = new \App\resources\Response('0', 405, ['error' => 'Method not allowed']);
        break;

    case FastRoute\Dispatcher::FOUND:
        [$controller, $method] = $routeInfo[1];

        $object = new $controller();
try
{


        /** @var \App\resources\Response $response */
        $response = $object->$method();
}
catch (Throwable $e)
{
    echo json_encode($e->getMessage());exit;
}
        break;
}

$response->send();