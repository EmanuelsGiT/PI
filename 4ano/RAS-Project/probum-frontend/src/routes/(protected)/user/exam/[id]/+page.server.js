import {error, redirect} from "@sveltejs/kit";
import {EXAM_API_URL} from "$env/static/private";

const loadExam = async (auth, examId, studentId) => {

    try {

        const response = await fetch(`${EXAM_API_URL}/exams/${examId}/students/${studentId}/status`,
            {
                method: 'GET',
                headers: { 'Content-Type': 'application/json', 'Authorization': auth }
            });

        if (response.ok) return await response.json();

    } catch (err) { throw error(500, 'There was a problem on our side, try again later.'); }

    // return {
    // 	"id": 0,
    // 	"version": 1,
    // 	"reservation": "Reserva2",
    // 	"duration": 90,
    // 	"max_score": 100,
    // 	"exam_type": "EXAM",
    // 	"description": "Trying to create a Exam Example",
    // 	"subject": "Sistemas Operativos",
    // 	"questions": [
    // 		{
    // 			"id": 0,
    // 			"question_type": "MULTIPLE_CHOICE",
    // 			"points": 25.0,
    // 			"image_path": "http://www.g20brasil.com.br/wp-content/uploads/2017/08/G20Brasil_como_instalar_o_interruptor_paralelo_3_way_02.jpg",
    // 			"description": "Qual dos YouTubers OG's é melhor ? Selecione apenas uma resposta!\n A imagem não tem nada a ver.",
    // 			"answer": {
    // 				"O Fer0m0nas e o melhor deles todos! Ninguem diz o contrario!": true,
    // 				"O VenomExtreme fell off...": false,
    // 				"O J4rvas e a sua gameplay de Team Fortress 2": true,
    // 				"O Tiagovksi? Nem devia estar aqui!": false
    // 			}
    // 		},
    // 		{
    // 			"id": 1,
    // 			"question_type": "MULTIPLE_CHOICE",
    // 			"points": 25.0,
    // 			"image_path": "No source",
    // 			"description": "Este é uma questão de escolha múltipla 1",
    // 			"answer": {
    // 				"0": true,
    // 				"1": false,
    // 				"2": true,
    // 				"3": false
    // 			}
    // 		},
    // 		{
    // 			"id": 2,
    // 			"question_type": "MULTIPLE_CHOICE",
    // 			"points": 25.0,
    // 			"image_path": "https://getwallpapers.com/wallpaper/full/f/8/d/1284031-large-wallpapers-1920x1140-ipad.jpg",
    // 			"description": "Este é uma questão de escolha múltipla 2",
    // 			"answer": {
    // 				"0": true,
    // 				"1": false,
    // 				"2": true,
    // 				"3": false
    // 			}
    // 		},
    // 		{
    // 			"id": 3,
    // 			"question_type": "MULTIPLE_CHOICE",
    // 			"points": 25.0,
    // 			"image_path": "No source",
    // 			"description": "Este é uma questão de escolha múltipla 3",
    // 			"answer": {
    // 				"0": true,
    // 				"1": false,
    // 				"2": true,
    // 				"3": false
    // 			}
    // 		}
    // 	]
    // };

}

export const load = async ({ locals, params }) => {

    if (!locals.user) {
        throw redirect(303, '/login');
    }

    const exam = await loadExam(locals.cookie, params.id, locals.user.user.UId);

    console.log(exam);

    return exam;

    // return {
    //     exam: {
    //         version: 1,
    //         reservation: "the-reservation-id",
    //         duration: 120,
    //         max_score: 20,
    //         exam_type: "EXAM",
    //         description: "Isto é um exame que foi realizado há duas semanas!",
    //         subject: "Sistemas Distribuidos",
    //         questions: [
    //             {
    //                 id: 0,
    //                 question_type: "MULTIPLE_CHOICE",
    //                 points: 20,
    //                 image_path: "No source",
    //                 description: "Is this an example question ?",
    //                 answer: {
    //                     "Well, I don't think so..": false,
    //                     "I don't know!": false,
    //                     "Looks like one!": true
    //                 }
    //             },
    //         ]
    //     },
    //     status: {
    //         exam_score: 10,
    //         question_score: {0: 10},
    //         answers: [
    //             {
    //                 question_id: 0,
    //                 response_data:{
    //                     "Well, I don't think so..": false,
    //                     "I don't know!": false,
    //                     "Looks like one!": true
    //                 }
    //             }
    //         ]
    //     }
    // };

};