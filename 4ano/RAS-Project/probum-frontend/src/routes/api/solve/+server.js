import { json } from "@sveltejs/kit";
import { EXAM_API_URL } from "$env/static/private";

export const POST = async ({ request, cookies }) => {

    const auth = cookies.get("AuthorizationToken");

    if (auth) {

        const body = await request.json();

        try {

            const response = await fetch(`${EXAM_API_URL}/responses`,
                {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json', 'Authorization': auth },
                    body: JSON.stringify(body)
                });

            const resp = await response.json()
            console.log(resp)

            if (response.ok) return json({}, { status: 201 });
            else return json({}, { status: response.status })

        } catch (err) { return json({error: err}, { status: 500 }) }

    }

}