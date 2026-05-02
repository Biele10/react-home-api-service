import config from './../config.json' assert { type: 'json' };

// Contains all functions that link to the 

async function get(module, method, params)
{
    const api_url = config.api_path;
    try
    {
        const response = await fetch(api_url);
        if (!response.ok)
        {
            throw new Error(`Response status: ${response.status}`);
        }

        const result = await response.json();
        console.log(result);
    }
    
    catch (error)
    {
        console.error(error.message);
    }

}