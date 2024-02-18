var axios = require('axios')
var env = require('../config/env')

module.exports.login = body => {
    return axios.post(env.authAccessPoint+'/login', body)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })  
}

module.exports.getUsers = token => {
    return axios.get(env.authAccessPoint+'/' + "?token=" + token)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })
}

module.exports.getUser = (id,token)=> {
    return axios.get(env.authAccessPoint+'/user/' + id + "?token=" + token)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })
}

module.exports.getCurrentUser = token => {
    return axios.get(env.authAccessPoint+'/profile' + "?token=" + token)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })
}

module.exports.addUser = body => {
    return axios.post(env.authAccessPoint+'/register', body)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })
}

module.exports.updateUser = (token, id, body) => {
    return axios.put(env.authAccessPoint+'/' + id + "?token=" + token, body)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })
}

module.exports.deleteUser = (id, token) => {
    return axios.delete(env.authAccessPoint+'/' + id + "?token=" + token)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })
}


module.exports.getInquiricoesPage = (page, token) => {
    return axios.get(env.apiAccessPoint+"/inquiricoes?page="+ page +"&token=" + token)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })
}

module.exports.getInquiricoesSearchPage = (searchType, search, page, token) => {
    return axios.get(env.apiAccessPoint+"/inquiricoes?searchType=" + searchType + "&search=" + search + "&page="+ page +"&token=" + token)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })
}

module.exports.newInquiricao = (token, body) => {
    return axios.post(env.apiAccessPoint+"/inquiricoes/" + "?token=" + token, body)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })   
}

module.exports.editInquiricao = (token, id, body) => {
    return axios.put(env.apiAccessPoint+'/inquiricoes/' + id + "?token=" + token, body)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })
}

module.exports.newFiliacao = (token, id, body) => {
    return axios.post(env.apiAccessPoint + "/inquiricoes/" + id + "?token=" + token, body)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })   
}

module.exports.getInquiricao = (id, token) => {
    return axios.get(env.apiAccessPoint+"/inquiricoes/" + id +"?token=" + token)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })  
}

module.exports.deleteInquiricao = (id, token) => {
    return axios.delete(env.apiAccessPoint + "/inquiricoes/" + id + "?token=" + token)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })  
}

module.exports.getPostsPage = (page, token) => {
    return axios.get(env.apiAccessPoint+"/posts?page=" + page + "&token=" + token)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })     
}

module.exports.getPostsSearchPage = (searchType, search, page, token) => {
    return axios.get(env.apiAccessPoint+"/posts?searchType=" + searchType + "&search=" + search + "&page="+ page +"&token=" + token)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })     
}

module.exports.newPost = (token, body) => {
    return axios.post(env.apiAccessPoint + "/posts/" + "?token=" + token, body)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })   
}

module.exports.getPost = (id, token) => {
    return axios.get(env.apiAccessPoint + "/posts/" + id + "?token=" + token)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })   
}

module.exports.deletePost = (id, token) => {
    return axios.delete(env.apiAccessPoint + "/posts/" + id + "?token=" + token)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })   
}

module.exports.newPostComment = (id, token, body) => {
    return axios.post(env.apiAccessPoint+"/posts/" + id + "?token=" + token, body)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })    
}

module.exports.deletePostComment = (idP, idC, token) => {
    return axios.delete(env.apiAccessPoint + "/posts/" + idP + "/comments/" + idC + "?token=" + token)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })    
}

module.exports.getSugestoesPage = (page, token) => {
    return axios.get(env.apiAccessPoint+"/sugestoes?page=" + page + "&token=" + token)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })     
}

module.exports.newSugestao = (token, body) => {
    return axios.post(env.apiAccessPoint + "/sugestoes/" + "?token=" + token, body)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })   
}

module.exports.deleteSugestao = (id, token) => {
    return axios.delete(env.apiAccessPoint + "/sugestoes/" + id + "?token=" + token)
            .then(resposta => {
                return resposta.data
            })
            .catch(erro => {
                return erro
            })   
}
