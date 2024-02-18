var createError = require('http-errors');
var express = require('express');
var logger = require('morgan');
const session = require('express-session');
var passport = require('passport')
var LocalStrategy = require('passport-local').Strategy
var mongoose = require('mongoose');
require('dotenv').config();

var mongoDB = 'mongodb://127.0.0.1/Project';
//process.env.MONGODB_URL
mongoose.connect(process.env.MONGODB_URL, 
      { useNewUrlParser: true,
        useUnifiedTopology: true,
        serverSelectionTimeoutMS: 5000});
  
const db = mongoose.connection;
db.on('error', console.error.bind(console, 'Erro de conexão ao MongoDB...'));
db.once('open', function() {
  console.log("Conexão ao MongoDB realizada com sucesso...")
});

// passport config
var User = require('./models/user');
passport.use(new LocalStrategy(User.authenticate()));
passport.serializeUser(User.serializeUser());
passport.deserializeUser(User.deserializeUser());

const usersRouter = require('./routes/user');
const authRouter = require('./routes/google_auth');
const facebookRouter = require('./routes/facebook_auth');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));

app.use(passport.initialize());
app.use(passport.session());

app.use('/users', usersRouter);
//app.use('/auth/', authRouter);
//app.use('/auth/facebook', facebookRouter);

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.jsonp({error: err});
});

module.exports = app;
