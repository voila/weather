let forecast = (lat, lon) => {
  let apiUrl = {j|https://api.myjson.com/bins/ifx55|j};
  Js.log(apiUrl);
  Js.Promise.(Fetch.fetch(apiUrl) |> then_(Fetch.Response.text));
};

let mockForecast = (_lat, _lon) => {
  let json = {|
      [{"time":1520323200,"summary":"Mostly Cloudy","icon":"partly-cloudy-night",
      "precipIntensity":0,"precipProbability":0,"temperature":10.56,"windSpeed":2.2},

      {"time":1520326800,"summary":"Mostly Cloudy","icon":"partly-cloudy-night",
      "precipIntensity":0,"precipProbability":0,"temperature":9.99,"windSpeed":1.89}
      ]
      |};
  Js.Promise.resolve(json);
};