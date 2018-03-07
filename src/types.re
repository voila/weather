type point = {
  time: float, /* unix timestamp */
  icon: string, /* one word description of the icon */
  summary: string, /* one sentence description of the weather */
  precInt: float, /* rain intensity (mm/h) */
  precProb: float, /* rain probability (%) */
  temp: float, /* temperature (Celsius) */
  wind: float /* wind speed (km/h) */
};

type points = list(point);

let decodeDataPoint: Json.Decode.decoder(point) =
  json =>
    Json.Decode.{
      time: field("time", Json.Decode.float, json),
      icon: field("icon", Json.Decode.string, json),
      summary: field("summary", Json.Decode.string, json),
      precInt: field("precipIntensity", Json.Decode.float, json),
      precProb: field("precipProbability", Json.Decode.float, json),
      temp: field("temperature", Json.Decode.float, json),
      wind: field("windSpeed", Json.Decode.float, json)
    };

let parseJson = (json: Js.Json.t) : points =>
  json |> Json.Decode.list(decodeDataPoint);