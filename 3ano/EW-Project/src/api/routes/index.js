var express = require('express');
var router = express.Router();
var Inquiricoes = require('../controllers/inquiricao')
var Posts = require('../controllers/posts')
var Sugestoes = require('../controllers/sugestoes')

// GET: os vários pedidos Inquiricoes
router.get('/api/inquiricoes', function(req, res, next) {
  if(req.query.searchType && req.query.search){
    Inquiricoes.getPesquisa(req.query.searchType, req.query.search, parseInt(req.query.page)) 
      .then(response=>{
        const numPages_ = Math.ceil(response.len / 10);
        res.jsonp({ inquiricoes: response.list, numPages: numPages_ })
      })
      .catch(erro=>{
        res.jsonp({error:erro, message:"Erro na obtencao do contrato"})
    })
  } else {
    Inquiricoes.getInquiricoesPage(parseInt(req.query.page))
    .then(response => {
      Inquiricoes.getInquiricoesLen()
        .then(len => {
          const numPages_ = Math.ceil(len / 10);
          res.jsonp({ inquiricoes: response, numPages: numPages_ })
        })
        .catch(erro => {
          res.render('error', {error: erro, message: "Erro na obtenção da len das inquiricoes"})
        })
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na obtenção das inquiricoes"})
    })
  }
});

// GET: inquiricao
router.get('/api/inquiricoes/:id', function(req, res) {
  Inquiricoes.getInquiricaoID(req.params.id)
    .then(inquiricao => {
      res.jsonp(inquiricao)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na obtenção da inquiricao"})
    })
});

// Update Inquiricao
router.put('/api/inquiricoes/:id', function(req, res) {
  Inquiricoes.updateInquiricao(req.params.id, req.body)
    .then(inquiricao => {
      res.jsonp(inquiricao)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na obtenção da inquiricao"})
    })
});

router.delete('/api/inquiricoes/:idInq', function(req, res) {
  Inquiricoes.deleteInquiricao(req.params.idInq)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro no delete da inquiricao"})
    })
})

// POST: de uma inquiricao
router.post('/api/inquiricoes', function(req, res) {
  Inquiricoes.addInquiricao(req.body)
    .then(inquiricao => {
      res.jsonp(inquiricao)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na inserção da inquiricao"})
    })
})

router.post('/api/inquiricoes/:id', function(req, res) {
  Inquiricoes.addFiliacao(req.params.id, req.body)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na inserção da filiacao "})
    })
})

// POST : de um comentario
router.post('/api/posts/:id', function(req, res) {
  Posts.addComment(req.params.id, req.body)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro no comment"})
    })

})

// GET: os vários pedidos Inquiricoes
router.get('/api/posts', function(req, res, next) {
  if(req.query.searchType && req.query.search){
    Posts.getPostPesquisa(req.query.searchType, req.query.search, parseInt(req.query.page)) 
      .then(response=>{
        const numPages_ = Math.ceil(response.len / 10);
        res.jsonp({ posts: response.list, numPages: numPages_ })
      })
      .catch(erro=>{
        res.jsonp({error:erro, message:"Erro na obtencao do contrato"})
    })
  } else {
    Posts.getPostsPage(parseInt(req.query.page))
      .then(posts_ => {
        Posts.getPostsLen()
          .then(len => {
            const numPages_ = Math.ceil(len / 10);
            res.jsonp({ posts: posts_, numPages: numPages_ })
          })
          .catch(erro => {
            res.render('error', {error: erro, message: "Erro na obtenção da len dos posts"})
          })
      })
      .catch(erro => {
        res.render('error', {error: erro, message: "Erro na obtenção dos posts"})
      })
  }
});

router.get('/api/posts/:id', function(req, res) {
  Posts.getPostID(req.params.id)
    .then(post => {
      res.jsonp(post)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na obtenção do post"})
    })
});

router.post('/api/posts/', function(req, res) {
  Posts.addPost(req.body)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na inserção de um post"})
    })
})

router.delete('/api/posts/:idPost/comments/:idComment', function(req, res) {
  Posts.deleteComment(req.params.idPost, req.params.idComment)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro no delete de um comment"})
    })
})

router.delete('/api/posts/:idPost', function(req, res) {
  Posts.deletePost(req.params.idPost)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro no delete de um post"})
    })
})

// GET: sugestao
router.get('/api/sugestoes/:id', function(req, res) {
  Sugestoes.getSugestaoID(req.params.id)
    .then(sugestao => {
      res.jsonp(sugestao)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na obtenção da sugestao"})
    })
});

router.get('/api/sugestoes', function(req, res, next) {
  Sugestoes.getSugestoesPage(parseInt(req.query.page))
    .then(response => {
      Sugestoes.getSugestoesLen()
        .then(len => {
          const numPages_ = Math.ceil(len / 10);
          res.jsonp({ Sugestoes: response, numPages: numPages_ })
        })
        .catch(erro => {
          res.render('error', {error: erro, message: "Erro na obtenção da len das sugestoes"})
        })
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na obtenção das sugestoes"})
    })
})

router.delete('/api/sugestoes/:idSugestao', function(req, res) {
  Sugestoes.deleteSugestao(req.params.idSugestao)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro no delete de uma sugestao"})
    })
})

router.post('/api/sugestoes/', function(req, res) {
  Sugestoes.addSugestao(req.body)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na inserção de uma sugestao"})
    })
})

module.exports = router;
