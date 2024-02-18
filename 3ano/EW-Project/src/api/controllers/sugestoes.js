var Sugestao = require('../models/sugestoes')
const mongoose = require('mongoose')

module.exports.getSugestoes = () => {
    return Sugestao
            .find()
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}

module.exports.getSugestoesPage = pageIndex => {
    return Sugestao
            .find()
            .sort({data:-1})
            .skip((pageIndex-1) * 10)
            .limit(10)
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}

module.exports.getSugestoesLen = () => {
    return Sugestao
            .find()
            .count()
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}

module.exports.getSugestaoID = id => {
    return Sugestao.findOne({_id: new mongoose.Types.ObjectId(id)})
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}

module.exports.addSugestao = p => {
    p._id = new mongoose.Types.ObjectId()
    return Sugestao.create(p)
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}

module.exports.updateSugestao = p => {
    return Sugestao.updateOne({_id:p._id}, p)
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}

module.exports.deleteSugestao = id => {
    return Sugestao.deleteOne({_id:id})
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}
