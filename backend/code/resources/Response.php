<?php

namespace App\resources;

Class Response
{
    private int $responseCode;
    private array $finalResponse;

    public function __construct(bool $success, int $responseCode, array $data=[])
    {
        $this->responseCode = $responseCode;

        $this->finalResponse = [
            "success" => $success,
            "data" => $data
        ];
    }

    public function send() : void
    {
        header('Content-Type: application/json');
        http_response_code($this->responseCode);
        echo json_encode($this->finalResponse);
    }
}