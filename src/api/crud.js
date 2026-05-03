import config from './../config.json' with { type: 'json' };

// Contains all functions that link to the 

async function get(module, method, params)
{
    const query = new URLSearchParams({
    module,
    method,
    params: JSON.stringify(params),
    });

    const api_url = config.api_path + '?' + query.toString();
    console.log(api_url);
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

export default get;