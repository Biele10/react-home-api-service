import config from './../config.json' with { type: 'json' };

// Contains all functions that link to the 

async function get(request_type, module, method, params = null)
{
    const query = new URLSearchParams({
        request_type,
        module,
        method
    });

    if (params !== null)
    {
        for (const [key, value] of Object.entries(params))
        {
            query.append(key, value);
        }
    }

    const queryString = query.toString();
    const api_url = config.api_path + '?' + queryString;

    try
    {
        const response = await fetch(api_url);
        if (!response.ok)
        {
            throw new Error(`Response status: ${response.status}`);
        }

        const result = await response.json();
        return result;
    }
    
    catch (error)
    {
        console.error(error.message);
    }

}

export default get;