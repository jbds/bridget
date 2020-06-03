[%%raw {|
let ws;

// make sure we can invoke a func in this module
function test() {
  alert('Online.test invoked!');
}

function showMessageInConsole(message) {
  console.log(message);
}

function doLogin(myLoginNameValue) {
  if(!myLoginNameValue) {
    alert('Please enter your name before you login');
    return;
  }
  fetch('/login', {
    method: 'POST',
    credentials: 'same-origin',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify({userName: myLoginNameValue})
  })
  .then(showMessageInConsole)
  .catch(function(err){
    showMessageInConsole(err.message);
  });
}


exports.test = test;
exports.doLogin = doLogin;


|}];