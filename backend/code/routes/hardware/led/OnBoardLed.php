<?php

namespace App\routes\hardware\led;
use App\controllers\hardware\led\OnBoardLedController;

$r->addRoute(
    'PUT',
    '/hardware/onBoardLed/power',
    [OnBoardLedController::class, 'power']
);