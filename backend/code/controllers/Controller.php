<?php

namespace Samaritan\controllers;

// This is the base class that all controllers will inherit from, this will be used for specific permission handling etc
abstract Class Controller
{
    protected array $data;
    protected int $responseCode; 

    /**
     * This is the final call a controller will make to return back to 
     * index.php and echo output to the user when a function was successful.
     * @return \Samaritan\resources\Response
     */
    final protected function Success() : \Samaritan\resources\Response
    {
        $responseData = (!empty($this->data)) ? $this->data : [];
        return new \Samaritan\resources\Response(true, 200, $responseData);
    }

    /**
     * This is the final call a controller will make to return back to 
     * index.php and echo output to the user when there was an error.
     * @return \Samaritan\resources\Response
     */
    final protected function Error() : \Samaritan\resources\Response
    {
        $responseData = (!empty($this->data)) ? $this->data : [];
        return new \Samaritan\resources\Response(false, $this->responseCode, $responseData);
    }
}