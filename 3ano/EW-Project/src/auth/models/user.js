const mongoose = require('mongoose')
var passportLocalMongoose = require('passport-local-mongoose');

var userSchema = new mongoose.Schema({
    username: String,
    password: String,
    accountId: String,
    name: String,
    provider: String,
    email: String,
    filiacao: String,
    level: String,
    active: Boolean,
    dateCreated: String,
    dateLastAccess: String
  });

userSchema.plugin(passportLocalMongoose);

module.exports = mongoose.model('user', userSchema)