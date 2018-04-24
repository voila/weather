type point = {
  time: float,
  icon: string,
  press: float,
  desc: string,
  rain: option(float),
  temp: float,
  wind: float,
};

type points = array(point);

exception No_weather;

exception Api_error;

let decodePoint: Json.Decode.decoder(point) =
  json => {
    open Json.Decode;
    let time = field("dt", float, json);
    let press = field("main", json => field("pressure", float, json), json);
    let rain =
      field("rain", optional(json => field("3h", float, json)), json);
    let temp = field("main", json => field("temp", float, json), json);
    let wind = field("wind", json => field("speed", float, json), json);
    let desc_icon = json => (
      field("description", string, json),
      field("icon", string, json),
    );
    let (desc, icon) = {
      let weather = field("weather", json => array(desc_icon, json), json);
      switch (weather) {
      | [|(_, _) as p|] => p
      | _ => raise(No_weather)
      };
    };
    [%debugger];
    {time, icon, press, desc, rain, temp, wind};
  };

let decodePoints = (json: string) : array(point) =>
  json
  |> Json.parseOrRaise
  |> (
    json =>
      switch (Json.Decode.(json |> field("cod", string))) {
      | "200" =>
        Json.Decode.(field("list", json => array(decodePoint, json), json))
      | _ => raise(Api_error)
      }
  );

let openWeatherMap = (lat, lon) => {
  let apiUrl =
    "http://api.openweathermap.org/data/2.5/forecast?"
    ++ {j|lat=$lat&lon=$lon|j}
    ++ "&mode=json&units=metric&appid=cba0e822fd9d16d74c7ae1bfb1d497f3";
  Fetch.fetch(apiUrl) |> Js.Promise.then_(Fetch.Response.text);
};

let mock = (_lat, _lon) =>
  Js.Promise.resolve(
    {|{
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
  }|},
  );

let decodeResolve = (cb, p) : unit =>
  Js.Promise.(
    p
    |> then_(json => {
         let () = json |> decodePoints |> cb;
         resolve();
       })
    |> ignore
  );

let forecast = (lat, lon, cb) =>
  openWeatherMap(lat, lon) |> decodeResolve(cb);

let forecastMock = (lat, lon, cb) => mock(lat, lon) |> decodeResolve(cb);