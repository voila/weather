# weather

Uses DarkSky's API (https://darksky.net/dev) to retrieve a 48 hours weather forecast for a given location, and return a subset of that data to its clients.

 Change the API key in `env.re` and replace `Api.forecastMock` with `Api.forecast` in `page.re`.

See https://github.com/voila/reason-client-server-example for more information


Run this project:

```
npm install
npm start
# in another tab
npm run webpack
```

After you see the webpack compilation succeed (the `npm run webpack` step), open up the nested html files in `src/*` (**no server needed!**). Then modify whichever file in `src` and refresh the page to see the changes.

**For more elaborate ReasonReact examples**, please see https://github.com/reasonml-community/reason-react-example
