const mongoose = require('mongoose')

var commentSchema = new mongoose.Schema({
    _id: {
        type: mongoose.Types.ObjectId,
    },
    username: String,
    descricao: String
});

var postSchema = new mongoose.Schema({
    _id: {
        type: mongoose.Types.ObjectId,
    },
    nome: String,
    descricao: String,
    data: String,
    registo: String,
    coments: [commentSchema]
});

module.exports = mongoose.model('post', postSchema)