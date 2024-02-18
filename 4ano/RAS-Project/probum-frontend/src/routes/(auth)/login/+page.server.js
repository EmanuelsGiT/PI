import { fail, redirect } from '@sveltejs/kit';

import { USER_API_URL } from '$env/static/private';
import { loginSchema } from "$lib/schemas.js";

import { superValidate } from 'sveltekit-superforms/server';

export const load = async(event) => {

	if (event.locals.user) {
		throw redirect(301, '/');
	}

	const form = await superValidate(event, loginSchema);
	return { form };
};

export const actions = {

	default: async (event) => {

		const form = await superValidate(event, loginSchema);

		// validate form inputs according to zod schema
		if (!form.valid) {
			fail(400, { form });
			return { form };
		}

		let response;
		try {
			// login request to the backend api
			response = await fetch(
				`${USER_API_URL}/user/login/`,
				{
					method: 'POST',
					headers: { 'Content-Type': 'application/json' },
					body: JSON.stringify(form.data)
				}
			);
		} catch (err) {
			// handle server errors
			console.log(err);
			form.errors["password"] = ["There was a problem on our side, please try again later."];
			return {form};
		}

		// handle successful response, store access tokens in secure cookie
		if (response.ok) {

			const responseData = await response.json();

			let expires_in = 60 * 60 * 24 * 7;
			if (form.data.remember) expires_in = 2628000; // if remember me is set to true, token lasts 1 month

			// setting authorization jwt token
			event.cookies.set('AuthorizationToken', `Bearer ${responseData.token}`, {
				httpOnly: true,
				path: '/',
				secure: true,
				sameSite: 'strict',
				maxAge: expires_in
			});

		} else {
			// handle sign in errors
			form.errors["general"] = ["Invalid username or password, try again."];
			return {form};
		}

		/* If everything went well, put the user on the homepage. */
		throw redirect(301, '/');
	}
};