var express = require('express');
var router = express.Router();
var jwt = require('jsonwebtoken')
var passport = require('passport')
var userModel = require('../models/user')
var auth = require('../auth/auth')
var User = require('../controllers/user')

router.get('/', auth.verificaAcesso, function(req, res){
  User.list()
    .then(dados => res.status(200).jsonp({dados: dados}))
    .catch(e => res.status(500).jsonp({error: e}))
})

router.get('/user/:id', auth.verificaAcesso, function(req, res){
  User.getUser(req.params.id)
    .then(dados => res.status(200).jsonp({dados: dados}))
    .catch(e => res.status(500).jsonp({error: e}))
})

router.get('/profile', auth.verificaAcesso, function(req, res){
  const token = req.query.token || req.body.token;
  jwt.verify(token, 'EngWeb2023', (err, decoded) => {
    if (err) {
      return res.status(401).json({ error: 'Invalid token' });
    }
    const userN = decoded.username; // Assuming the token contains the user ID
    User.getUserName(userN)
      .then(user => {
        if (!user) {
          return res.status(404).json({ error: 'User not found' });
        }
        res.status(200).json({ dados: user });
      })
      .catch(error => {
        res.status(500).json({ error: error.message });
      });
  });

});


router.post('/', auth.verificaAcesso, function(req, res){
  User.addUser(req.body)
    .then(dados => res.status(201).jsonp({dados: dados}))
    .catch(e => res.status(500).jsonp({error: e}))
})

router.post('/register', function(req, res) {
  var d = new Date().toISOString().substring(0,19)
  userModel.register(new userModel({ email: req.body.email,
                                     username: req.body.username, 
                                     name: req.body.name, 
                                     filiacao: req.body.filiacao,
                                     level: req.body.level, 
                                     active: true, 
                                     dateLastAccess: d,
                                     dateCreated: d
                                   }), 
                                  req.body.password, 
                                  function(err, user) {
                                    if (err) 
                                      res.jsonp({error: err, message: "Register error: " + err})
                                    else{
                                      passport.authenticate("local")(req,res,function(){
                                        jwt.sign({ username: req.user.username, level: req.user.level, 
                                          sub: 'aula de EngWeb2023'}, 
                                          "EngWeb2023",
                                          {expiresIn: 3600},
                                          function(e, token) {
                                            if(e) res.status(500).jsonp({error: "Erro na geração do token: " + e}) 
                                            else res.status(201).jsonp({token: token})
                                          });
                                      })
                                    }     
  })
})
  
router.post('/login', passport.authenticate('local'), function(req, res){
  var d = new Date().toISOString().substring(0,19)
  User.updateUserLastAccess(req.user._id, d)
  jwt.sign({ username: req.user.username, level: req.user.level, 
    sub: 'aula de EngWeb2023'}, 
    "EngWeb2023",
    {expiresIn: 3600},
    function(e, token) {
      if(e) res.status(500).jsonp({error: "Erro na geração do token: " + e}) 
      else res.status(201).jsonp({token: token})
  });
})

router.put('/:id', auth.verificaAcesso, function(req, res) {
  User.updateUser(req.params.id, req.body)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na alteração do utilizador"})
    })
})

router.put('/:id/desativar', auth.verificaAcesso, function(req, res) {
  User.updateUserStatus(req.params.id, false)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na alteração do utilizador"})
    })
})

router.put('/:id/ativar', auth.verificaAcesso, function(req, res) {
  User.updateUserStatus(req.params.id, true)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na alteração do utilizador"})
    })
})

router.put('/:id/password', auth.verificaAcesso, function(req, res) {
  User.updateUserPassword(req.params.id, req.body)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na alteração do utilizador"})
    })
})

router.delete('/:id', auth.verificaAcesso, function(req, res) {
  User.deleteUser(req.params.id)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na remoção do utilizador"})
    })
})

module.exports = router;