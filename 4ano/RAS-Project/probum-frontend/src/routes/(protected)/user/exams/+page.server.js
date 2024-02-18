import {error, redirect} from '@sveltejs/kit';
import {EXAM_API_URL, USER_API_URL} from "$env/static/private";


const loadExams = async (auth, studentId) => {

	console.log(studentId)

	try {
		const response = await fetch(`${EXAM_API_URL}/exams/students/${studentId}`,
			{
				method: 'GET',
				headers: { 'Content-Type': 'application/json', 'Authorization': auth }
			});

		if (response.ok) return await response.json();

	} catch (err) { throw error(500, 'There was a problem on our side, try again later.'); }

}

export const load = async ({ locals }) => {

	if (!locals.user) {
		throw redirect(303, '/login');
	}

	const exams = await loadExams(locals.cookie, locals.user.user.UId);

	console.log(exams)

	return {
		user: locals.user.user,
		exams: exams
	}

};