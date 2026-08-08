<?php

namespace App\routes\hardware\led;
use App\controllers\hardware\led\LedController;

$r->addRoute(
    'PUT',
    '/hardware/redLed/power',
    [LedController::class, 'power']
);