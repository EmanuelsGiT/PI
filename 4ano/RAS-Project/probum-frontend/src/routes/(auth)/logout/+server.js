import { redirect } from "@sveltejs/kit"

export const POST = async ({ cookies }) => {
	cookies.delete("AuthorizationToken", { "path": "/" });
	throw redirect(303, "http://localhost:5173/api/logout");
}