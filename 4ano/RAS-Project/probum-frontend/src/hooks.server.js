import { USER_API_URL } from '$env/static/private';

export const handle = async ({ event, resolve }) => {

	const authCookie = event.cookies.get('AuthorizationToken');

	if (authCookie) {

		event.locals.cookie = authCookie;

		try {

			const userResponse = await fetch(`${USER_API_URL}/user`,
				{
					method: 'GET',
					headers: { 'Content-Type': 'application/json', 'Authorization': authCookie }
				});

			if (userResponse.ok) event.locals.user = await userResponse.json();
			else console.log(userResponse.status);

		} catch (err) { console.error(err, err.stack); }

	}

	return await resolve(event);
};