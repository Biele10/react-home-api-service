<?php

namespace Samaritan\routes\hardware\led;
use Samaritan\controllers\hardware\led\OnBoardLedController;

$r->addRoute(
    'PUT',
    '/hardware/onBoardLed/power',
    [OnBoardLedController::class, 'power']
);