import config from './../config.json' with { type: 'json' };

// Contains all functions that link to the 

async function get(request_type, command=null)
{
    const query = new URLSearchParams({
    request_type,
    command,
    });

    const api_url = config.api_path + '?' + query.toString();

    try
    {
        const response = await fetch(api_url);
        if (!response.ok)
        {
            throw new Error(`Response status: ${response.status}`);
        }

        const result = await response.json();
        alert(result);
    }
    
    catch (error)
    {
        console.error(error.message);
    }

}

export default get;