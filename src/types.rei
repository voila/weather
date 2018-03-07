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

let parseJson: Js.Json.t => points;