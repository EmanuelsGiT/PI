const passport = require('passport');
var GoogleStrategy = require('passport-google-oauth20').Strategy;
const express = require('express');
const googleAuth = require('../models/google');
const router = express.Router();
require('dotenv').config();

let userProfile;
let tokeN;

passport.use(
  new GoogleStrategy(
    {
      clientID: process.env.GOOGLE_CLIENT_ID,
      clientSecret: process.env.GOOGLE_CLIENT_SECRET,
      callbackURL: process.env.GOOGLE_CALLBACK_URL,
    },
    function (request, accessToken, refreshToken, profile, done) {
      userProfile = profile;
      tokeN = accessToken;

      console.log(profile);
      return done(null, profile);
    }
  )
);

router.get('/google',
  passport.authenticate('google', { scope: ['profile', 'email'] }));

router.get('/google/callback', 
  passport.authenticate('google', { failureRedirect: '/login' }),
  function(req, res) {
    // Successful authentication, redirect home.
    res.redirect('/');
  });

//router.post(
//  '/auth/google',
//  passport.authenticate('google', { scope: ['profile', 'email'] })
//);
//
//// Define the Google callback route
//router.post(
//  '/auth/google/callback',
//  passport.authenticate('google', { failureRedirect: '/login' }),
//  (req, res) => {
//    // Redirect the user after successful authentication
//    res.redirect('/home');
//  }
//);

passport.serializeUser((user, done) => {
  // Implement your user serialization logic here.
  // This function is called to store the user's information in the session.
  // Typically, you would store the user's ID.
  done(null, user.id);
});

passport.deserializeUser((id, done) => {
  // Implement your user deserialization logic here.
  // This function is called to retrieve the user's information from the session.
  // Typically, you would retrieve the user's information based on the stored ID.
  done(null, { id });
});

module.exports = router;




/*
const app = express();

app.use(passport.initialize());
app.use(passport.session());

// request at /auth/google, when user click sign-up with google button transferring
// the request to google server, to show emails screen
app.get(
  '/auth/google',
  passport.authenticate('google', { scope: ['profile', 'email'] })
);

// URL Must be same as 'Authorized redirect URIs' field of OAuth client, i.e: /auth/google/callback
app.get(
  '/auth/google/callback',
  passport.authenticate('google', { failureRedirect: '/login' }),
  (req, res) => {
    // Redirect the user after successful authentication
    res.redirect('/dashboard');
  }
);

router.get('/success', async (req, res) => {
  const { failure, success } = await googleAuth.registerWithGoogle(userProfile);
  if (failure) console.log('Google user already exist in DB..');
  else console.log('Registering new Google user..');
  res.render('success', { user: userProfile });
});

router.get('/error', (req, res) => {
  console.log("Erro de merda")
  res.send('Error logging in via Google..')
});

router.get('/signout', (req, res) => {
  try {
    req.session.destroy(function (err) {
      console.log('session destroyed.');
    });
    res.render('auth');
  } catch (err) {
    res.status(400).send({ message: 'Failed to sign out user' });
  }
});
*/