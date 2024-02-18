import { writable } from 'svelte/store';


const initialExam = {
    version: 1,
    reservation: "the-reservation-id",
    duration: 120,
    max_score: 20,
    exam_type: "EXAM",
    description: "",
    subject: "Subject",
    questions: [
        {
            question_type: "MULTIPLE_CHOICE",
            points: 20,
            image_path: "No source",
            description: "Is this an example question ?",
            answer: {
                "Well, I don't think so..": false,
                "I don't know!": false,
                "Looks like one!": true
            }
        }
    ]
}

export const examStore = writable(initialExam);
