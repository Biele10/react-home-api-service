<?php

namespace Samaritan\routes\hardware\led;
use Samaritan\controllers\hardware\led\LedController;

$r->addRoute(
    'PUT',
    '/hardware/redLed/power',
    [LedController::class, 'power']
);