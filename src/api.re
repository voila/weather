let forecast = (lat, lon) => {
  let apiUrl =
    "http://api.openweathermap.org/data/2.5/forecast?"
    ++ "lat="
    ++ lat
    ++ "&lon="
    ++ lon
    ++ "&mode=json&units=metric&appid=cba0e822fd9d16d74c7ae1bfb1d497f3";
  Js.log(apiUrl);
  Js.Promise.(Fetch.fetch(apiUrl) |> then_(Fetch.Response.text));
};

let mockForecast = (_lat, _lon) => {
  let json = {|
    {
      "cod": "200",
      "message": 0.0045,
      "cnt": 37,
      "list": [
        {
          "dt": 1520413200,
          "main": {
            "temp": 34.28,
            "temp_min": 284.277,
            "temp_max": 284.28,
            "pressure": 992.31,
            "sea_level": 1032.32,
            "grnd_level": 992.31,
            "humidity": 95,
            "temp_kf": 0
          },
          "weather": [
            {
              "id": 500,
              "main": "Rain",
              "description": "light rain",
              "icon": "10n"
            }
          ],
          "clouds": {
            "all": 64
          },
          "wind": {
            "speed": 1.83,
            "deg": 193
          },
          "rain": {
            "3h": 0.085
          },
          "sys": {
            "pod": "n"
          },
          "dt_txt": "2018-03-07 09:00:00"
        }
      ]
    }
      |};
  Js.Promise.resolve(json);
};