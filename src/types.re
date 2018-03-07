type point = {
  time: float,
  icon: string,
  press: float,
  desc: string,
  rain: option(float),
  temp: float,
  wind: float
};

type points = array(point);

exception No_weather;
exception Api_error;
let decodePoint: Json.Decode.decoder(point) =
  json => {
    open Json.Decode;
    let time = field("dt", float, json);
    let press = field("main", json => field("pressure", float, json), json);
    let rain = field("rain", optional(json => field("3h", float, json)), json);
    let temp = field("main", json => field("temp", float, json), json);
    let wind = field("wind", json => field("speed", float, json), json);
    let desc_icon = json => (
      field("description", string, json),
      field("icon", string, json)
    );
    let (desc, icon) = {
      let weather = field("weather", json => array(desc_icon, json), json);
      switch weather {
      | [|(_, _) as p|] => p
      | _ => raise(No_weather)
      };
    };
    {time, icon, press, desc, rain, temp, wind};
  };
/* 
let decodePoints = (json: string) : array(point) =>
  json
  |> Json.parseOrRaise
  |> Json.Decode.(field("list", json => array(decodePoint, json))); */

let decodePoints = (json: string) : array(point) =>
  json
  |> Json.parseOrRaise
  |> (
    json =>
      switch Json.Decode.(json |> field("cod", string)) {
      | "200" => Json.Decode.(field("list", json => array(decodePoint, json), json))
      | _ => raise(Api_error)
      }
  );
