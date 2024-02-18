import {error, redirect} from "@sveltejs/kit";

export const load = async ({ locals }) => {

    if (!locals.user) {
        throw redirect(303, '/login');
    }

    if (locals.user.role in ["teacher", "admin", "tech"]) {
        throw error(401, "Only teachers are allowed to access this route.")
    }

    return {
        user: locals.user.user,
        "ucs": ["Sistemas Operativos", "Sistemas Distribuídos", "Cálculo de Programas"]
    };

};