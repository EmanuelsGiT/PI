const inquiricao = require('../models/inquiricao')
var Inquiricao = require('../models/inquiricao')

module.exports.getInquiricoes = () => {
    return Inquiricao
            .find()
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}

module.exports.getInquiricoesPage = pageIndex => {
    return Inquiricao
            .find()
            .sort({Created:-1})
            .skip((pageIndex-1) * 10)
            .limit(10)
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}

module.exports.getInquiricoesLen = () => {
    return Inquiricao
            .find()
            .count()
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}

module.exports.getInquiricaoID = id => {
    return Inquiricao.findOne({_id:id})
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}

module.exports.getPesquisa = (type, searchn, pageIndex) => {
    if (type == "nome")
    {
        
        const countQuery = Inquiricao.find({ UnitTitle: { $regex: searchn, $options: 'i' } }).count();
        const searchQuery = Inquiricao
                            .find({ UnitTitle: { $regex: searchn, $options: 'i' } })
                            .sort({UnitTitle:-1})
                            .skip((pageIndex-1) * 10)
                            .limit(10);
        return Promise.all([countQuery, searchQuery])
                      .then(([count, resposta]) => {
                            return { list: resposta, len: count };
                        })
                        .catch(erro => {
                          return erro;
                        });
    }
    if (type == "lugar")
    {
        const countQuery = Inquiricao.find({ ScopeContent: { $regex: searchn, $options: 'i' } }).count();
        const searchQuery = Inquiricao
                            .find({ ScopeContent: { $regex: searchn, $options: 'i' } })
                            .sort({UnitTitle:-1})
                            .skip((pageIndex-1) * 10)
                            .limit(10);
        return Promise.all([countQuery, searchQuery])
                      .then(([count, resposta]) => {
                            return { list: resposta, len: count };
                        })
                        .catch(erro => {
                          return erro;
                        });
    }
    if (type == "data")
    {
        const countQuery = Inquiricao.find({ Created: { $regex: searchn, $options: 'i' } }).count();
        const searchQuery = Inquiricao
                            .find({ Created: { $regex: searchn, $options: 'i' } })
                            .sort({Created:-1})
                            .skip((pageIndex-1) * 10)
                            .limit(10);
        return Promise.all([countQuery, searchQuery])
                      .then(([count, resposta]) => {
                            return { list: resposta, len: count };
                        })
                        .catch(erro => {
                          return erro;
                        });
    }
}

module.exports.addInquiricao = l => {
    var d = new Date().toISOString().substring(0,19)
    l.Created = d;
    l.Filiacao = []

    return Inquiricao.findOne({}, { _id: 1 }, { sort: { _id: -1 } })
        .exec() 
        .then(resu => {
            const newId = parseInt(resu._id) + 1;
            console.log(newId)
            l._id = newId.toString();
            return Inquiricao.create(l);
        })
        .then(resposta => {
        return resposta;
        })
        .catch(erro => {
        return erro;
        });
}

module.exports.addFiliacao = (id, filiacao) => {

    console.log(typeof filiacao.Id.toString())
    var n = filiacao.Id.toString()
    const title = Inquiricao.findOne({_id: n}, { UnitTitle: 1 })
    const inq = Inquiricao.findOne({_id: id})
    
    return Promise.all([title, inq])
                .then(([t,i]) => {
                if (!i) {
                    console.log('Post not found');
                    return;
                }
                
                const newFiliacao = {
                    Id: n,
                    Title: t.UnitTitle,
                };
                console.log(newFiliacao)
                i.Filiacao.push(newFiliacao);
            
                return i.save();
                })
                .then(() => {
                console.log('Filiacao added successfully');
                })
                .catch((err) => {
                console.error(err);
                });
}

module.exports.updateInquiricao = (id, info) => {
    return Inquiricao.updateOne({_id:id}, info)
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}

module.exports.deleteInquiricao = id => {
    return Inquiricao.deleteOne({_id:id})
            .then(resposta => {
                return resposta
            })
            .catch(erro => {
                return erro
            })
}
