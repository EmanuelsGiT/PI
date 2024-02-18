var express = require('express');
var router = express.Router();
var Controller = require('../controllers/controllers');

/* GET home page. */
router.get('/', function(req, res){
  res.render('login')
})

router.get('/home/inquiricoes', function(req, res) {
  var data = new Date().toISOString().substring(0,19)
  var token = ""
  if(req.cookies && req.cookies.token)
    token = req.cookies.token
  
  const page = req.query.page
  if (page <= 0) res.render('error', {error: err})
  const currentPage = parseInt(page) || 1;
  const prevPage = currentPage > 1 ? currentPage - 1 : 1;
  
  Controller.getCurrentUser(token)
    .then(resp => {
      if(req.query.searchType && req.query.search) {
        Controller.getInquiricoesSearchPage(req.query.searchType, req.query.search, page, token)
          .then(response => {
            if (currentPage > response.numPages) res.render('error', {error: err})
            const nextPage = currentPage < response.numPages ? currentPage + 1 : currentPage;
            res.render('inquiricoesUser', { inquiricoes: response.inquiricoes, 
                                            prevIndex: prevPage, 
                                            nextIndex: nextPage,
                                            searcht: req.query.searchType,
                                            search: req.query.search,
                                            user: resp.dados });
          })
          .catch(err => {
            res.render('inquiricoesUser', {error: err,
                                           user: resp.dados})
          })
      } else {
        Controller.getInquiricoesPage(page, token)
          .then(response => {
            if (currentPage > response.numPages) res.render('error', {error: err})
            const nextPage = currentPage < response.numPages ? currentPage + 1 : currentPage;
            res.render('inquiricoesUser', { inquiricoes: response.inquiricoes, 
                                            prevIndex: prevPage, 
                                            nextIndex: nextPage,
                                            user: resp.dados });
          })
          .catch(err => {
            res.render('inquiricoesUser', {error: err,
                                          user: resp.dados})
          })
      }
    })
    .catch(err => {
      res.render('login') // pag erro login
    })
});

router.route('/home/inquiricoes/newInquiricao')
  .get(function(req, res) {
    res.render('newInquiricao')
  })
  .post(function(req, res) {
    var token = ""
    if(req.cookies && req.cookies.token)
      token = req.cookies.token
    console.log(req.body);
    Controller.newInquiricao(token, req.body)
    .then(response => {
      res.redirect('/home/inquiricoes')
    })
    .catch(err => {
      res.render('error', {error: err})
    })
})

router.get('/home/inquiricao/:id', function(req, res) {
  var data = new Date().toISOString().substring(0,19)
  var token = ""
  if(req.cookies && req.cookies.token)
    token = req.cookies.token
    Controller.getCurrentUser(token)
    .then(response => {
      Controller.getInquiricao(req.params.id, token)
        .then(response2 => {
          res.render('inquiricao', { inquiricao: response2, user: response.dados, d: data });
        })
        .catch(err => {
          res.render('error', {error: err}) 
        })
    })
    .catch(err => {
      res.render('login')  // pag erro login
    })
});


router.get('/home/inquiricao/delete/:id', function(req,res) {
  var token = ""
  if(req.cookies && req.cookies.token)
    token = req.cookies.token
  Controller.deleteInquiricao(req.params.id, token)
    .then(response => {
      res.redirect('/home/inquiricoes');
    })
    .catch(err => {
      res.render('error', {error: err})
    })
})

router.get('/home/admin', function(req, res) {
  var data = new Date().toISOString().substring(0,19)
  var token = ""
  if(req.cookies && req.cookies.token)
    token = req.cookies.token

  Controller.getUsers(token)
    .then(response => {
      res.render('admin', { users: response.dados, d: data });
    })
    .catch(err => {
      res.render('error', {error: err})
    })
});

router.get('/home/user/delete/:id', function(req,res) {
  var token = ""
  if(req.cookies && req.cookies.token)
    token = req.cookies.token
  Controller.deleteUser(req.params.id, token)
    .then(response => {
      res.redirect('/home/admin');
    })
    .catch(err => {
      res.render('error', {error: err})
    })
})

router.get('/home/user/update/:id', function(req,res) {
  var token = ""
  if(req.cookies && req.cookies.token)
    token = req.cookies.token
  Controller.updateUser(req.params.id, token)
    .then(response => {
      res.redirect('/home/admin');
    })
    .catch(err => {
      res.render('error', {error: err})
    })
})

router.route('/home/perfil')
  .get(function(req, res) {
    var data = new Date().toISOString().substring(0,19)
    var token = ""
    if(req.cookies && req.cookies.token)
      token = req.cookies.token
    Controller.getCurrentUser(token)
      .then(response => {
        res.render('perfil', { user: response.dados, d: data });
      })
      .catch(err => {
        res.render('login') // pag erro login
      })
  })
  .post(function(req, res) {
    var data = new Date().toISOString().substring(0,19)
    var token = ""
    if(req.cookies && req.cookies.token)
      token = req.cookies.token

    Controller.getCurrentUser(token)
      .then(response => {
        console.log("post homeperfil")
        Controller.updateUser(token, response.dados._id, req.body)
          .then(response => {
            res.redirect('back')
          })
          .catch(err => {
            res.render('error', {error: err})
          })
      })
      .catch(err => {
        res.render('login') // pag erro login
      })
    
})

router.post('/home/admin/user/:id', function(req, res) {
  var data = new Date().toISOString().substring(0,19)
  var token = ""
  if(req.cookies && req.cookies.token)
    token = req.cookies.token
  
  Controller.getUser(req.params.id, token)
    .then(response => {
      console.log(response.dados._id)
      Controller.updateUser(token, response.dados._id, req.body)
        .then(response => {
          res.redirect('back')
        })
        .catch(err => {
          res.render('error', {error: err})
        })
    })
    .catch(err => {
      res.redirect('/home/admin') // pag erro login
    })
  
})


router.get('/home', function(req, res) {
  
  var token = ""
  if(req.cookies && req.cookies.token)
    token = req.cookies.token
  
  Controller.getCurrentUser(token)
    .then(resp => {
      var data = new Date().toISOString().substring(0,19)
      
      const page = req.query.page
      if (page <= 0) res.render('error', {error: err})
      const currentPage = parseInt(page) || 1;
      const prevPage = currentPage > 1 ? currentPage - 1 : 1;

      if(req.query.searchType && req.query.search) {
        Controller.getPostsSearchPage(req.query.searchType, req.query.search, page, token)
          .then(response => {
            if (currentPage > response.numPages) res.render('error', {error: err})
            console.log(response.numPages)
            const nextPage = currentPage < response.numPages ? currentPage + 1 : currentPage;
            res.render('homeUser', { posts: response.posts,
                                            user: resp.dados,
                                            prevIndex: prevPage, 
                                            nextIndex: nextPage,
                                            searcht: req.query.searchType,
                                            search: req.query.search });
          })
          .catch(err => {
            res.render('homeUser', {error: err,
                                    user: resp.dados})
          })
      } else {
        Controller.getPostsPage(page, token)
          .then(response => { 
            if (currentPage > response.numPages) res.render('error', {error: err})
            const nextPage = currentPage < response.numPages ? currentPage + 1 : currentPage;
            res.render('homeUser', { posts: response.posts, 
                                    user: resp.dados, 
                                    prevIndex: prevPage, 
                                    nextIndex: nextPage });
          })
          .catch(err => {
            res.render('homeUser', {error: err,
                                    user: resp.dados})
          })
      }

    })
    .catch(err => {
      console.log(err)
      res.render('login') // pag erro login
    })
});

router.get('/home/post/:idPost/delete/:idComment', function(req, res) {
  var token = ""
  if(req.cookies && req.cookies.token)
    token = req.cookies.token
  Controller.deletePostComment(req.params.idPost, req.params.idComment, token)
    .then(response => {
      res.redirect('/home/post/' + req.params.idPost)
    })
    .catch(err => {
      res.render('error', {error: err})
    })
});


router.get('/home/post/delete/:id', function(req,res) {
  var token = ""
  if(req.cookies && req.cookies.token)
    token = req.cookies.token
  Controller.deletePost(req.params.id, token)
    .then(response => {
      res.redirect('/home');
    })
    .catch(err => {
      res.render('error', {error: err})
    })
})

router.route('/home/post/:id').get(function(req, res) {
  var data = new Date().toISOString().substring(0,19)
  var token = ""
  if(req.cookies && req.cookies.token)
    token = req.cookies.token
    Controller.getCurrentUser(token)
    .then(response => {
      Controller.getPost(req.params.id, token)
        .then(response2 => {
          res.render('post', { post: response2, user: response.dados, d: data });
        })
        .catch(err => {
          res.render('error', {error: err})
        })
    })
    .catch(err => {
      res.render('login') // pag erro login
    })
}).post(function(req, res) {
  var token = ""
  if(req.cookies && req.cookies.token)
    token = req.cookies.token
  Controller.newPostComment(req.params.id, token, req.body)
  .then(response => {
    res.redirect('/home/post/' + req.params.id)
  })
  .catch(err => {
    res.render('error', {error: err})
  })
})

router.route('/home/inquiricao/:id/newpost').get(function(req,res) {
  var date = new Date().toISOString().substring(0,19)
  var token = ""
  if(req.cookies && req.cookies.token)
    token = req.cookies.token
    Controller.getCurrentUser(token)
    .then(response => {
      Controller.getInquiricao(req.params.id, token)
        .then(response2 => {
          res.render('newPost', {inq: response2, d:date, user: response.dados});
        })
        .catch(err => {
          res.render('error', {error: err})
        })
    })
    .catch(err => {
      res.render('login') // pag erro login
    })
  }).post(function(req, res) {
  var token = ""
  if(req.cookies && req.cookies.token)
    token = req.cookies.token
  Controller.newPost(token, req.body)
  .then(response => {
    res.redirect('/home/inquiricao/' + req.params.id)
  })
  .catch(err => {
    res.render('error', {error: err})
  })
})

router.route('/home/inquiricao/:id/editInquiricao').get(function(req,res) {
  var date = new Date().toISOString().substring(0,19)
  var token = ""
  if(req.cookies && req.cookies.token)
    token = req.cookies.token
    Controller.getCurrentUser(token)
    .then(response => {
      Controller.getInquiricao(req.params.id, token)
        .then(response2 => {
          res.render('editInquiricao', {inq: response2, d:date, user: response.dados});
        })
        .catch(err => {
          res.render('error', {error: err})
        })
    })
    .catch(err => {
      res.render('login') // pag erro login
    })
  }).post(function(req, res) {
    var token = ""
    if(req.cookies && req.cookies.token)
      token = req.cookies.token
    Controller.editInquiricao(token, req.params.id, req.body)
    .then(response => {
      res.redirect('/home/inquiricao/' + req.params.id)
    })
    .catch(err => {
      res.render('error', {error: err})
    })
})

router.route('/home/inquiricao/:id/filiacao').post(function(req, res) {
  var token = ""
  if(req.cookies && req.cookies.token)
    token = req.cookies.token
  Controller.newFiliacao(token, req.params.id, req.body)
  .then(response => {
    res.redirect('/home/inquiricao/' + req.params.id)
  })
  .catch(err => {
    res.render('error', {error: err})
  })
})

router.route('/home/sugestoes').get(function(req, res) {
  var date = new Date().toISOString().substring(0,19)
  var token = ""
  if(req.cookies && req.cookies.token)
    token = req.cookies.token

    Controller.getCurrentUser(token)
    .then(resp => {
      var data = new Date().toISOString().substring(0,19)
      
      const page = req.query.page
      if (page <= 0) res.render('error', {error: err})
      const currentPage = parseInt(page) || 1;
      const prevPage = currentPage > 1 ? currentPage - 1 : 1;
        
      Controller.getSugestoesPage(page, token)
        .then(response => {
          console.log(response.numPages)
          //if (currentPage > response.numPages) res.render('error', {error: err})
          const nextPage = currentPage < response.numPages ? currentPage + 1 : currentPage;
          console.log(response)
          res.render('sugestoes', { sugestoes: response.Sugestoes, 
                                  user: resp.dados, 
                                  prevIndex: prevPage, 
                                  nextIndex: nextPage,
                                  current: currentPage });
        })
        .catch(err => {
          res.render('error', {error: err})
        })
      
    })
    .catch(err => {
      console.log(err)
      res.render('login') // pag erro login
    })
}).post(function(req, res) {
  var token = ""
  if(req.cookies && req.cookies.token)
    token = req.cookies.token
  Controller.newSugestao(token, req.body)
  .then(response => {
    res.redirect('/home/sugestoes')
  })
  .catch(err => {
    res.render('error', {error: err})
  })
})


router.get('/home/sugestoes/delete/:id', function(req, res) {
  var token = ""
  if(req.cookies && req.cookies.token)
    token = req.cookies.token
  Controller.deleteSugestao(req.params.id, token)
    .then(response => {
      res.redirect('/home/sugestoes')
    })
    .catch(err => {
      res.render('error', {error: err})
    })
});

//router.get('/retrieveList/:id', function(req, res) {
//  var data = new Date().toISOString().substring(0,19)
//  axios.get(env.apiAccessPoint+"/inquiricoes/" + req.params.id)
//    .then(response => {
//      res.render('inquiricao', { inquiricao: response, d: data });
//    })
//    .catch(err => {
//      res.render('error', {error: err})
//    })
//});
//
//router.get('/lista/:idLista/deleteProduto/:idProd', function(req, res) {
//  var data = new Date().toISOString().substring(0,19)
//  console.log(req.params.idProd)
//  axios.delete(env.apiAccessPoint+"/listas/"+ req.params.idLista +"/produtos/"+ req.params.idProd)
//    .then(response => {
//      res.redirect('/retrieveList/' + req.params.idLista)
//    })
//    .catch(err => {
//      res.render('error', {error: err})
//    })
//});

// Tratamento do Login
router.get('/login', function(req, res){
  res.render('login')
})

router.post('/login', function(req, res){
  Controller.login(req.body)
    .then(response => {
      res.cookie('token', response.token)
      res.redirect('/home')
    })
    .catch(e =>{
      res.render('login', {error: e})
    })
})

// Tratamento do Logout
//router.get('/logout', verificaToken, (req, res) => {
router.get('/home/logout', (req, res) => {
  //req.session.destroy()
  res.cookie('token', "revogado.revogado.revogado")
  res.redirect('/')
})

// Tratamento do Register
router.get('/home/admin/register', function(req, res){
  res.render('register')
})

router.post('/register', function(req, res){
  Controller.addUser(req.body)
    .then(response => {
      //res.cookie('token', response.token)
      res.redirect('/home/admin')
    })
    .catch(e =>{
      res.render('error', {error: e, message: "Credenciais inválidas"})
    })
})
/*
// facebook
router.get('/login/facebook', function(req, res){
  axios.get('http://localhost:8002/auth/facebook')
    .then(response => {
      res.cookie('token', response.token)
      console.log("Entraste crlh!!!!")
      res.redirect('/home')
    })
    .catch(e =>{
      res.render('error', {error: e, message: "Credenciais inválidas"})
    })
})

// google
router.get('/login/google', function(req, res){
  axios.get('http://localhost:8002/auth/google')
    .then(response => {
      res.cookie('token', response.token)
      console.log("interface index")
      res.redirect('/home')
    })
    .catch(e =>{
      res.render('error', {error: e, message: "Credenciais inválidas"})
    })
})
*/
module.exports = router;
