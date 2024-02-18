const mongoose = require('mongoose')

var sugestaoSchema = new mongoose.Schema({
    _id: {
        type: mongoose.Types.ObjectId,
    },
    nome: String,
    descricao: String,
    data: String,
});

module.exports = mongoose.model('sugestoes', sugestaoSchema)