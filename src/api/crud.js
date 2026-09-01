import config from './../config.json' with { type: 'json' };

async function request(path, method = "GET", body = null, params = null)
{
    let api_url = config.api_path + path;

    if (params !== null)
    {
        const query = new URLSearchParams(params);
        api_url += '?' + query.toString();
    }

    const options = {
        method,
        headers: {
            "Content-Type": "application/json"
        }
    };

    if (body !== null)
    {
        options.body = JSON.stringify(body);
    }

    try
    {
        const response = await fetch(api_url, options);
        if (!response.ok)
        {
            throw new Error(`Response status: ${response.status}`);
        }

        return await response.json();
    }
    catch(error)
    {
        console.error(error.message);
        throw error;
    }
}

function get(path, params = null)
{
    return request(path, "GET", null, params);
}

function post(path, body = null)
{
    return request(path, "POST", body);
}

function put(path, body = null)
{
    return request(path, "PUT", body);
}

function del(path, body = null)
{
    return request(path, "DELETE", body);
}

export { get, post, put, del };