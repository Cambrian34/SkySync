const http = require('http');
const url = require('url');
const fs = require('fs');

const server = http.createServer((req, res) => {
  const query = url.parse(req.url, true).query;
  const authorizationCode = query.code;

  if (authorizationCode) {
    console.log('Authorization Code:', authorizationCode);

    // Write the authorization code to a named pipe
    const pipePath = '/Users/alistairchambers/Documents/SkySync/temp/tmp/auth_pipe.txt'; 
    fs.writeFileSync(pipePath, authorizationCode);

    res.end('Authorization successful. You can close this tab.');
    // Add logic to close the server or navigate to a new page
  } else {
    res.end('Invalid request.');
  }
});


const PORT = 8080;
server.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}/`);
});
